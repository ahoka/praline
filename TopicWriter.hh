#ifndef TOPICWRITER_HH
#define TOPICWRITER_HH

#include "Topic.hh"

namespace Praline
{

class TopicWriter
{
public:
   explicit TopicWriter(Topic topic);
   TopicWriter(const TopicWriter&);
   ~TopicWriter();
   TopicWriter& operator=(const TopicWriter&);
   void write(char* data, size_t size);
};

}

#endif
