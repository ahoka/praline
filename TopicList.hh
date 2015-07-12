#ifndef TOPICLIST_HH
#define TOPICLIST_HH

#include "Topic.hh"

#include <map>
#include <utility>

namespace Praline
{
class TopicList
{
public:
   TopicList();
   ~TopicList();

   bool insert(Topic topic);
   std::pair<bool, Topic> find(std::string name);
   bool remove(Topic topic);

private:
   using TopicMap = std::map<std::string, Topic>;

   TopicMap topicMapM;
};
}

#endif
