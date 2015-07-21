#include "TopicWriter.hh"

#include <Poco/NumberFormatter.h>

#include <fcntl.h>
#include <cassert>
#include <cstdio>
#include <unistd.h>
#include <errno.h>

using namespace praline;

struct MessagePointer
{
   MessagePointer(uint64_t seqno, uint64_t offset, uint32_t size)
      : sequenceNumber(seqno),
        fileOffset(offset),
        messageSize(size)
   {
   }
   
   uint64_t sequenceNumber;
   uint64_t fileOffset;
   uint32_t messageSize;
};

std::ostream&
operator<<(std::ostream& s, MessagePointer&& message)
{
   return s.write((const char*)&message.sequenceNumber, sizeof(message.sequenceNumber))
      .write((const char*)&message.fileOffset, sizeof(message.fileOffset))
      .write((const char*)&message.messageSize, sizeof(message.messageSize));
}

TopicWriter::TopicWriter(const std::string& topicName, Poco::Logger& logger)
   : nextSequenceNumber(0),
     dataFileM(topicName + ".data"),
     metaFileM(topicName + ".meta"),
     logM(logger)
{
}

TopicWriter::~TopicWriter()
{
   if (dataStreamM.is_open())
   {
      logM.information("Closing file");
      dataStreamM.close();
      if (dataStreamM.fail())
      {
         logM.information("Closing file failed!");
      }
   }
}

uint64_t
TopicWriter::getNextSequenceNumber()
{
   return nextSequenceNumber++;
}

// Writes:
//  - Open data file for append
//  - Open meta file for append
//  - Read meta file into memory
//  - All meta write goes both to memory and file
//
// Reads:
//  - Find sequence number of message in memory (binary search)
//  - Seek to offset in data file
//  - Stream message to consumer
//

bool
TopicWriter::open()
{
   logM.information("Opening files '%s' and '%s'", dataFileM, metaFileM);

   dataStreamM.open(dataFileM, std::ios_base::out | std::ios_base::binary | std::ios_base::app);
   if (dataStreamM.fail())
   {
      logM.error("Opening '%s' failed!", dataFileM);
      return false;
   }

   metaStreamM.open(metaFileM, std::ios_base::out | std::ios_base::binary | std::ios_base::app);
   if (metaStreamM.fail())
   {
      logM.error("Opening '%s' failed!", metaFileM);
      return false;
   }

   logM.information("Opening topic files successful", metaFileM);

   return true;
}

bool
TopicWriter::write(std::istream& data)
{
   logM.information("Writing to file '%s'", dataFileM);

   dataStreamM.clear();

   auto startPosition = dataStreamM.tellp();
   
   dataStreamM << data.rdbuf();
   dataStreamM.flush();

   auto endPosition = dataStreamM.tellp();

   if (dataStreamM.bad())
   {
      logM.error("Writing to file '%s' set badbit!", dataFileM);
   }

   if (dataStreamM.fail())
   {
      logM.error("Writing to file '%s' set failbit!", dataFileM);
   }
   
   if (!dataStreamM.good())
   {
      logM.error("Writing to file '%s' failed!", dataFileM);
      return false;
   }
   else
   {
      auto messageSize = endPosition - startPosition;
      if (messageSize <= 0)
      {
         logM.error("Invalid write length!");
         return false;
      }
      else
      {
         // write meta-data
         auto sequenceNumber = getNextSequenceNumber();
         metaStreamM << MessagePointer(sequenceNumber,
                                       startPosition, messageSize);
         metaStreamM.flush();

         if (!metaStreamM.good())
         {
            logM.error("Writing to file '%s' failed!", metaFileM);
            return false;
         }
         else
         {
            logM.information("Message recorded: s:%lu o:%lu s:%lu",
                             (unsigned long)sequenceNumber,
                             (unsigned long)startPosition,
                             (unsigned long)messageSize);
            return true;
         }
      }
   }
}
