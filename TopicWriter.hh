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

   TopicWriter(const TopicWriter&) = delete;
   TopicWriter& operator=(const TopicWriter&) = delete;
   TopicWriter(const TopicWriter&&) = delete;
   TopicWriter& operator=(const TopicWriter&&) = delete;
   
   bool write(std::istream& data);
   bool open();

private:
   std::string dataFileM;
   std::ofstream dataStreamM;

   std::string metaFileM;
   std::fstream metaStreamM;

   Poco::Logger& logM;
};

}

#endif
