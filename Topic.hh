#ifndef TOPIC_HH
#define TOPIC_HH

#include <string>

class Topic
{
public:
   explicit Topic(std::string name);
   Topic(const Topic&);
   Topic& operator=(const Topic&);
   ~Topic();

   std::string name() const;

private:
   std::string nameM;
};

#endif
