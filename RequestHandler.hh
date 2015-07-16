#ifndef REQUESTHANDLER_HH
#define REQUESTHANDLER_HH

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Logger.h>

#include "TopicList.hh"

namespace praline
{

class RequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
   RequestHandler(TopicList&, Poco::Logger& logger = Poco::Logger::get("RequestHandler"));

private:
   using Request = Poco::Net::HTTPServerRequest;
   using Response = Poco::Net::HTTPServerResponse;

   void handleRequest(Request& request, Response& response);

   TopicList& topicListM;
   Poco::Logger& logM;
};

}

#endif
