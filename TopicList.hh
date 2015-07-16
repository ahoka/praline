#ifndef TOPICLIST_HH
#define TOPICLIST_HH

#include "Topic.hh"

#include <map>
#include <utility>

namespace praline
{
class TopicList
{
public:
   TopicList();
   virtual ~TopicList();

   virtual bool insert(Topic topic);
   virtual std::pair<bool, Topic> find(std::string name);
   virtual bool remove(Topic topic);

private:
   using TopicMap = std::map<std::string, Topic>;

   TopicMap topicMapM;
};
}

#endif
