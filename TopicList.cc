#include "TopicList.hh"

#include <Poco/DirectoryIterator.h>
#include <cstdio>

using namespace praline;

TopicList::TopicList(const std::string& path, Poco::Logger& logger)
   : pathM(path),
     logM(logger)
{
   logM.information("Using directory '%s'", path);
   
  // populate from the current directory
  for (Poco::DirectoryIterator di = pathM; di != Poco::DirectoryIterator(); ++di)
  {
     Poco::Path file = di.name();
     if (file.getExtension() == "meta")
     {
        auto topicName = file.getBaseName();
        logM.information("Opening topic '%s'", topicName);
        insert(Topic(topicName));
     }
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
