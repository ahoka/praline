#ifndef TOPIC_HH
#define TOPIC_HH

#include "TopicWriter.hh"
#include <memory>
#include <string>

namespace Praline
{

class Topic
{
public:
   explicit Topic(std::string name);
   Topic(const Topic&);
   Topic& operator=(const Topic&);
   ~Topic();

   bool open();
   std::string name() const;

private:
   std::string nameM;
   std::shared_ptr<TopicWriter> writerM;
};

}

#endif
