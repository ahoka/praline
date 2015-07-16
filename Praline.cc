#include "Praline.hh"
#include "HttpSubsystem.hh"

#include <Poco/Logger.h>
#include <Poco/PatternFormatter.h>
#include <Poco/AsyncChannel.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/FormattingChannel.h>

#include <Poco/SharedPtr.h>
#include <Poco/AutoPtr.h>

namespace
{
//   Poco::Logger& logger = Poco::Logger::get("Praline");
}

using Poco::AutoPtr;

using namespace praline;

Praline::Praline::Praline(Poco::Logger& logger)
   : logM(logger)
{
   AutoPtr<Poco::ColorConsoleChannel> consoleChannel(new Poco::ColorConsoleChannel);
   AutoPtr<Poco::PatternFormatter> patternFormatter(new Poco::PatternFormatter);
   patternFormatter->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: %t");
   AutoPtr<Poco::FormattingChannel> formattingChannel(new Poco::FormattingChannel(patternFormatter, consoleChannel));
   AutoPtr<Poco::AsyncChannel> asyncChannel(new Poco::AsyncChannel(formattingChannel)); 
   
   Poco::Logger::root().setChannel(asyncChannel);

   logM.setChannel(asyncChannel);
   logM.information("starting up");

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
