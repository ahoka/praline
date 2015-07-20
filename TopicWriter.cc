#include "TopicWriter.hh"

#include <fcntl.h>
#include <cassert>
#include <cstdio>
#include <unistd.h>
#include <errno.h>

using namespace praline;

TopicWriter::TopicWriter(const std::string& topicName, Poco::Logger& logger)
   : fileNameM(topicName + ".data"),
     logM(logger)
{
}

TopicWriter::~TopicWriter()
{
   if (streamM.is_open())
   {
      logM.information("Closing file");
      streamM.close();
      if (streamM.fail())
      {
         logM.information("Closing file failed!");
      }
   }
}

TopicWriter::TopicWriter(const TopicWriter& other)
   : fileNameM(other.fileNameM),
     logM(other.logM)
{
}

TopicWriter&
TopicWriter::operator=(const TopicWriter& other)
{
   return *this;
}

bool
TopicWriter::open()
{
   logM.information("Opening file %s", fileNameM);

   streamM.open(fileNameM);
   if (streamM.fail())
   {
      logM.error("Open failed!");
      return false;
   }

   logM.information("Opened successful");

   return true;
}

bool
TopicWriter::write(std::istream& data)
{
   return false;
}
