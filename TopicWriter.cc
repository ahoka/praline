#include "TopicWriter.hh"

#include <fcntl.h>
#include <cassert>
#include <cstdio>
#include <unistd.h>
#include <errno.h>

using namespace praline;

TopicWriter::TopicWriter(const std::string& topicName, Poco::Logger& logger)
   : fdM(-1),
     logM(logger)
{
   char filename[256];

   auto res = ::snprintf(filename, sizeof(filename), "%s.data", topicName.c_str());
   assert(res > 0 && (size_t)res < sizeof(filename));

   fileNameM = std::string(filename);
}

TopicWriter::~TopicWriter()
{
   if (fdM > -1)
   {
      ::close(fdM);
      logM.information("Closing file");
   }
}

TopicWriter::TopicWriter(const TopicWriter& other)
   : fileNameM(other.fileNameM),
     fdM(other.fdM),
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
   fdM = ::open(fileNameM.c_str(), O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
   if (fdM < 0)
   {
      logM.error("Open failed: %s", std::string(strerror(errno)));
      return false;
   }

   logM.information("Ok");

   return true;
}
