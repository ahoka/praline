#include "TopicList.hh"

TopicList::TopicList()
{
}

TopicList::~TopicList()
{
}

bool
TopicList::insert(Topic topic)
{
   auto res = topicMapM.insert({topic.name(), topic});
   return res.second;
}

std::pair<bool, Topic>
TopicList::find(std::string name)
{
   auto res = topicMapM.find(name);
   if (res == topicMapM.end())
   {
      return {false, Topic("<invalid>")};
   }
   else
   {
      return {true, res->second};
   }
}

bool
TopicList::remove(Topic topic)
{
   return topicMapM.erase(topic.name()) == 1;
}
