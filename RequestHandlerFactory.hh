#ifndef REQUESTHANDLERFACTORY_HH
#define REQUESTHANDLERFACTORY_HH

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>

#include <Poco/Logger.h>

namespace praline
{
   
class TopicList;

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
   RequestHandlerFactory(praline::TopicList& topicList,
                         Poco::Logger& logger = Poco::Logger::get("RequestHandlerFactory"));
   ~RequestHandlerFactory();

private:
   Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
   praline::TopicList& topicListM;
   Poco::Logger& logM;
};

}

#endif
