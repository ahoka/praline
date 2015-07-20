#include "RequestHandlerFactory.hh"
#include "RequestHandler.hh"

using namespace praline;

RequestHandlerFactory::RequestHandlerFactory(praline::TopicList& topicList,
                                             Poco::Logger& logger)
   : topicListM(topicList),
     logM(logger)
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

Poco::Net::HTTPRequestHandler *RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest&)
{
   logM.information("Creating request handler");
   return new RequestHandler(topicListM);
}
