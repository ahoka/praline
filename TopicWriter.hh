#ifndef TOPICWRITER_HH
#define TOPICWRITER_HH

#include "Topic.hh"

namespace Praline
{

class TopicWriter
{
public:
   explicit TopicWriter(Topic topic);
   ~TopicWriter();
   void write(char* data, size_t size);

private:
   TopicWriter(const TopicWriter&);
   TopicWriter& operator=(const TopicWriter&);

   int fdM;
};

}

#endif
