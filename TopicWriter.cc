#include "TopicWriter.hh"

#include <fcntl.h>
#include <cassert>
#include <cstdio>
#include <unistd.h>

using namespace Praline;

TopicWriter::TopicWriter(Topic topic)
{
   char filename[256];

   auto res = snprintf(filename, sizeof(filename), "%s.data", topic.name().c_str());
   assert(res > 0 && (size_t)res < sizeof(filename));

   fdM = open(filename, O_CREAT | O_APPEND);
}

TopicWriter::~TopicWriter()
{
   close(fdM);
}

TopicWriter::TopicWriter(const TopicWriter& other)
{
}

TopicWriter&
TopicWriter::operator=(const TopicWriter& other)
{
   return *this;
}
