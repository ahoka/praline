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
        serverM = new Poco::Net::HTTPServer(new RequestHandlerFactory, 8080);
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
