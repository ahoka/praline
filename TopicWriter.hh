#ifndef TOPICWRITER_HH
#define TOPICWRITER_HH

#include <Poco/Logger.h>

#include <string>

namespace praline
{

class TopicWriter
{
public:
   explicit TopicWriter(const std::string& topicName, Poco::Logger& logger = Poco::Logger::get("TopicWriter"));
   ~TopicWriter();
   void write(char* data, size_t size);
   bool open();

private:
   TopicWriter(const TopicWriter&);
   TopicWriter& operator=(const TopicWriter&);

   std::string fileNameM;
   int fdM;
   Poco::Logger& logM;
};

}

#endif
