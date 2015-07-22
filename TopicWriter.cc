#include "TopicWriter.hh"

#include <Poco/NumberFormatter.h>

#include <fcntl.h>
#include <cassert>
#include <cstdio>
#include <unistd.h>
#include <errno.h>

#include <algorithm>
#include <iterator>

using namespace praline;

std::ostream&
operator<<(std::ostream& s, const MessagePointer&& message)
{
   return s.write((const char*)&message.sequenceNumber, sizeof(message.sequenceNumber))
      .write((const char*)&message.fileOffset, sizeof(message.fileOffset))
      .write((const char*)&message.messageSize, sizeof(message.messageSize));
}

std::istream&
operator>>(std::istream& s, MessagePointer& message)
{
   return s.read((char*)&message.sequenceNumber, sizeof(message.sequenceNumber))
      .read((char*)&message.fileOffset, sizeof(message.fileOffset))
      .read((char*)&message.messageSize, sizeof(message.messageSize));
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

   dataStreamM.open(dataFileM, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::app);
   if (dataStreamM.fail())
   {
      logM.error("Opening '%s' failed!", dataFileM);
      return false;
   }

   metaStreamM.open(metaFileM, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::app);
   if (metaStreamM.fail())
   {
      logM.error("Opening '%s' failed!", metaFileM);
      return false;
   }

   logM.information("Opening topic files successful", metaFileM);

   // UGLY!
   for (;;)
   {
      MessagePointer mp;
      metaStreamM >> mp;

      if (metaStreamM.eof())
      {
         break;
      }

      logM.information("Adding entry to index: s:%lu o:%lu s:%lu",
                       (unsigned long)mp.sequenceNumber,
                       (unsigned long)mp.fileOffset,
                       (unsigned long)mp.messageSize);

//      indexLockM.writeLock();
      indexM.push_back(mp);
//      indexLockM.unlock();
   }

   if (indexM.size() > 0)
   {
      nextSequenceNumber = (indexM.end() - 1)->sequenceNumber + 1;
      logM.information("Next logical sequence number is %lu", (unsigned long)nextSequenceNumber);
   }

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
         metaStreamM.clear();
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
            indexLockM.writeLock();
            indexM.emplace_back(sequenceNumber, startPosition, messageSize);
            indexLockM.unlock();
            
            logM.information("Message recorded: s:%lu o:%lu s:%lu",
                             (unsigned long)sequenceNumber,
                             (unsigned long)startPosition,
                             (unsigned long)messageSize);
            return true;
         }
      }
   }
}

bool
TopicWriter::lookup(uint64_t sequenceNumber, MessagePointer& message)
{
   // XXX search reverse to optimize for accessing later items?
   indexLockM.readLock();
   auto m = std::lower_bound(indexM.begin(), indexM.end(), sequenceNumber);
   indexLockM.unlock();
   if (m == indexM.end())
   {
      logM.warning("message %lu not exising in topic '%s'",
                   (unsigned long)sequenceNumber, dataFileM);
      return false;
   }
   else
   {
      message = *m;
      return true;
   }
}

bool
TopicWriter::read(std::ostream& stream, const MessagePointer& message)
{
   std::ifstream reader(dataFileM);
   if (!reader.is_open())
   {
      logM.error("Can't open '%s'", dataFileM);
      return false;
   }

   reader.seekg(message.fileOffset);
   if (!reader.good())
   {
      logM.error("Can't seek to %lu in '%s'", (unsigned long)message.fileOffset, dataFileM);
      return false;
   }

   std::copy_n(std::istream_iterator<char>(reader), message.messageSize,
               std::ostream_iterator<char>(stream));

   return true;
}
