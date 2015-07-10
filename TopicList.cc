#include "TopicList.hh"

TopicList::TopicList();
TopicList::~TopicList();

void
TopicList::insert(Topic topic)
{
   topicMapM.insert(Topic.name(), Topic);
}

std::pair<bool, Topic>
TopicList::find(std::string name)
{
   auto res = topic.find(name);
   if (res == topicMapM.end())
   {
      return {false, Topic};
   }
   else
   {
      return {true, res.second};
   }
}

void
TopicList::remove(Topic topic)
{
}
