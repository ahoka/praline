#include "HttpSubsystem.hh"
#include "RequestHandlerFactory.hh"

#include <Poco/Net/HTTPServer.h>
#include <Poco/Logger.h>

using namespace praline;

HttpSubsystem::HttpSubsystem(Poco::Logger& logger)
   : logM(logger)
{
}

HttpSubsystem::~HttpSubsystem()
{
}

const char*
HttpSubsystem::name() const
{
   return "Http";
}

void
HttpSubsystem::initialize(Poco::Util::Application& app)
{
   logM.information("initialize");
   app.loadConfiguration();

   auto logdir = app.config().getString("logdir", ".");
   if (chdir(logdir.c_str()) == -1)
   {
      logM.error("Can't change to logdir '%s'", logdir);
   }

   int port = app.config().getInt("port", 8080);
   logM.information("listening on port %d", port);
   auto topicList = new TopicList(logdir); // XXX shared_ptr
   serverM = new Poco::Net::HTTPServer(new RequestHandlerFactory(*topicList), port);
   serverM->start();
   logM.information("server running");
}

void
HttpSubsystem::reinitialize(Poco::Util::Application& app)
{
   logM.information("reinitalize");
}

void
HttpSubsystem::uninitialize()
{
   logM.information("waiting for request termination");
   serverM->stopAll();
   logM.information("uninitalize");
   delete serverM;
}
