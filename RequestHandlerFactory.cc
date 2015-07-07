#include "RequestHandlerFactory.hh"

#include <Poco/Logger.h>

namespace
{
   Poco::Logger& logger = Poco::Logger::get("RequestHandler");
}

void RequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
   logger.information(Poco::Logger::format("URL: $0", request.getURI()));
}

Poco::Net::HTTPRequestHandler *RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
   logger.information("craeteRequestHandler");
   return new RequestHandler;
}
