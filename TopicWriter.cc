#include "TopicWriter.hh"

#include <fcntl.h>
#include <cassert>
#include <cstdio>
#include <unistd.h>
#include <errno.h>

using namespace praline;

struct MessagePointer
{
   uint64_t sequenceNumber;
   uint64_t fileOffset;
};

TopicWriter::TopicWriter(const std::string& topicName, Poco::Logger& logger)
   : dataFileM(topicName + ".data"),
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
   dataStreamM << data.rdbuf();
   dataStreamM.flush();

   if (dataStreamM.bad())
   {
      logM.information("Writing to file '%s' set badbit!", dataFileM);
   }

   if (dataStreamM.fail())
   {
      logM.information("Writing to file '%s' set failbit!", dataFileM);
   }
   
   return dataStreamM.good();
}
