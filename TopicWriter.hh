#ifndef TOPICWRITER_HH
#define TOPICWRITER_HH

#include <Poco/Logger.h>

#include <string>
#include <fstream>

namespace praline
{

class TopicWriter
{
public:
   explicit TopicWriter(const std::string& topicName, Poco::Logger& logger = Poco::Logger::get("TopicWriter"));
   ~TopicWriter();
   bool write(std::istream& data);
   bool open();

private:
   TopicWriter(const TopicWriter&);
   TopicWriter& operator=(const TopicWriter&);

   std::string fileNameM;
   std::ofstream streamM;

   Poco::Logger& logM;
};

}

#endif
