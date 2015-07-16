#ifndef REQUESTHANDLER_HH
#define REQUESTHANDLER_HH

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include "TopicList.hh"

class RequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
   RequestHandler(praline::TopicList&);

private:
   using Request = Poco::Net::HTTPServerRequest;
   using Response = Poco::Net::HTTPServerResponse;

   void handleRequest(Request& request, Response& response);

   praline::TopicList& topicListM;
};

#endif
