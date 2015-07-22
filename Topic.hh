#ifndef TOPIC_HH
#define TOPIC_HH

#include "TopicWriter.hh"
#include <memory>
#include <string>

namespace praline
{

class Topic
{
public:
   explicit Topic(std::string name);
   Topic(const Topic&);
   Topic& operator=(const Topic&);
   ~Topic();

   bool open();
   bool write(std::istream& data);
   bool lookup(uint64_t sequenceNumber, MessagePointer& message);
   bool read(std::ostream& stream, const MessagePointer& message);

   std::string name() const;

private:
   std::string nameM;
   std::shared_ptr<TopicWriter> writerM;
};

}

#endif
