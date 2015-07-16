#include "RequestHandlerFactory.hh"
#include "RequestHandler.hh"

#include <Poco/Logger.h>

namespace
{
   Poco::Logger& logger = Poco::Logger::get("RequestHandlerFactory");
}

using namespace praline;

RequestHandlerFactory::RequestHandlerFactory(praline::TopicList& topicList)
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
