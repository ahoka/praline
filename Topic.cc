#include "Topic.hh"

using namespace praline;

Topic::Topic(std::string name)
   : nameM(name),
     writerM(std::make_shared<TopicWriter>(name))
{
}

Topic::Topic(const Topic& other)
   : nameM(other.nameM),
     writerM(other.writerM)
{
}

Topic::~Topic()
{
}

Topic&
Topic::operator=(const Topic& other)
{
   nameM = other.nameM;
   writerM = other.writerM;

   return *this;
}

std::string
Topic::name() const
{
   return nameM;
}

bool
Topic::open()
{
   return writerM->open();
}

bool
Topic::write(std::istream& data)
{
   return writerM->write(data);
}
