#ifndef TOPICLIST_HH
#define TOPICLIST_HH

#include <map>
#include <utility>

class TopicList
{
public:
   TopicList();
   ~TopicList();

   void insert(Topic topic);
   std::pair<bool, Topic> find(std::string name);
   void remove(Topic topic);

private:
   using TopicMap = std::map<std::name, Topic>;

   TopicMap topicMapM;
};

#endif
