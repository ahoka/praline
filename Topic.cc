#include "Topic.hh"

Topic::Topic(std::string name)
   : nameM(name)
{
}

Topic::~Topic()
{
}

std::string
Topic::name() const
{
   return nameM;
}
