#include "HttpSubsystem.hh"
#include "RequestHandlerFactory.hh"

#include <Poco/Net/HTTPServer.h>
#include <Poco/Logger.h>

namespace
{
    Poco::Logger& logger = Poco::Logger::get("Http");
}

const char*
HttpSubsystem::name() const
{
	return "Http";
}

void
HttpSubsystem::initialize(Poco::Util::Application& app)
{
	logger.information("initialize");
        app.loadConfiguration();

        int port = app.config().getInt("port", 8080);
        logger.information("listening on port %d", port);
        serverM = new Poco::Net::HTTPServer(new RequestHandlerFactory(topicListM), port);
        serverM->start();
	logger.information("server running");
}

void
HttpSubsystem::reinitialize(Poco::Util::Application& app)
{
	logger.information("reinitalize");
}

void
HttpSubsystem::uninitialize()
{
	logger.information("waiting for request termination");
        serverM->stopAll();
	logger.information("uninitalize");
        delete serverM;
}
