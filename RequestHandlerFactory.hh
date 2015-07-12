#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>

namespace Praline
{
   class TopicList;
}

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
   RequestHandlerFactory(Praline::TopicList&);
   ~RequestHandlerFactory();

private:
   Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
   Praline::TopicList& topicListM;
};
