#include "TopicList.hh"

#include <Poco/DirectoryIterator.h>

using namespace praline;

TopicList::TopicList(const std::string& path)
  : pathM(path)
{
  // populate from the current directory
  for (Poco::DirectoryIterator dir = pathM; dir != Poco::DirectoryIterator(); ++dir)
  {
     // XXX dir.name();
  }
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
