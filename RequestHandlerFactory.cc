#include "RequestHandlerFactory.hh"
#include "RequestHandler.hh"

#include <Poco/Logger.h>

namespace
{
   Poco::Logger& logger = Poco::Logger::get("RequestHandlerFactory");
}

RequestHandlerFactory::RequestHandlerFactory(Praline::TopicList& topicList)
   : topicListM(topicList)
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

Poco::Net::HTTPRequestHandler *RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
   logger.information("craeteRequestHandler");
   return new RequestHandler(topicListM);
}
