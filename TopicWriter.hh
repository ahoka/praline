#ifndef TOPICWRITER_HH
#define TOPICWRITER_HH

#include <Poco/Logger.h>

#include <string>
#include <fstream>
#include <cstdint>

namespace praline
{
 
struct MessagePointer
{
   MessagePointer()
      : sequenceNumber(0),
        fileOffset(0),
        messageSize(0)
   {
   }
   
   MessagePointer(uint64_t seqno, uint64_t offset, uint32_t size)
      : sequenceNumber(seqno),
        fileOffset(offset),
        messageSize(size)
   {
   }

   bool operator<(uint64_t seqNo)
   {
      return sequenceNumber < seqNo;
   }
   
   uint64_t sequenceNumber;
   uint64_t fileOffset;
   uint32_t messageSize;
};

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
   bool read(std::ostream& stream, uint64_t& sequenceNumber);
   bool open();

private:
   uint64_t getNextSequenceNumber();

   uint64_t nextSequenceNumber;
   
   std::string dataFileM;
   std::fstream dataStreamM;

   std::string metaFileM;
   std::fstream metaStreamM;

   std::vector<MessagePointer> indexM;

   Poco::Logger& logM;
};

}

#endif
