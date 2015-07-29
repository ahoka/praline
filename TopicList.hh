#ifndef TOPICLIST_HH
#define TOPICLIST_HH

#include "Topic.hh"

#include <string>
#include <map>
#include <utility>

namespace praline
{
class TopicList
{
public:
   explicit TopicList(const std::string&);
   virtual ~TopicList();

   virtual bool insert(Topic topic);
   virtual std::pair<bool, Topic> find(std::string name);
   virtual bool remove(Topic topic);

private:
   using TopicMap = std::map<std::string, Topic>;

   std::string pathM;
   TopicMap topicMapM;
};
}

#endif
