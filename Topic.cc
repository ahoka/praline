#include "Topic.hh"

using namespace Praline;

Topic::Topic(std::string name)
   : nameM(name)
{
}

Topic::Topic(const Topic& other)
   : nameM(other.nameM)
{
}

Topic::~Topic()
{
}

Topic&
Topic::operator=(const Topic& other)
{
   nameM = other.nameM;

   return *this;
}

std::string
Topic::name() const
{
   return nameM;
}
