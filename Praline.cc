#include "Praline.hh"
#include "HttpSubsystem.hh"

#include <Poco/Logger.h>
#include <Poco/SharedPtr.h>

namespace
{
   Poco::Logger& logger = Poco::Logger::get("Praline");
}

Praline::Praline::Praline()
{
//   addSubsystem(Poco::SharedPtr<HttpSubsystem>(new HttpSubsystem));
   addSubsystem(new HttpSubsystem);
}

Praline::Praline::~Praline()
{
}

int
Praline::Praline::main(const std::vector<std::string>& args)
{
   waitForTerminationRequest();
   return 0;
}
