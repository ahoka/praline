#include "TopicWriter.hh"

#include <fcntl.h>
#include <cassert>
#include <cstdio>
#include <unistd.h>

#include <Poco/Logger.h>

namespace
{
   Poco::Logger& logger = Poco::Logger::get("TopicWriter");
}

using namespace Praline;

TopicWriter::TopicWriter(const std::string& topicName)
{
   char filename[256];

   auto res = ::snprintf(filename, sizeof(filename), "%s.data", topicName.c_str());
   assert(res > 0 && (size_t)res < sizeof(filename));

   fileNameM = std::string(filename);
}

TopicWriter::~TopicWriter()
{
   ::close(fdM);
   logger.information("Closing file");
}

TopicWriter::TopicWriter(const TopicWriter& other)
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
   logger.information("Opening file %s", fileNameM);
   fdM = ::open(fileNameM.c_str(), O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
   assert(fdM > 0);
   logger.information("Ok");
}
