#ifndef TOPICREQUESTHANDLER_HH
#define TOPICREQUESTHANDLER_HH

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include "TopicList.hh"

class TopicRequestHandler : public Poco::Net::HTTPTopicRequestHandler
{
public:
   TopicRequestHandler(Praline::TopicList&);

private:
   using Request = Poco::Net::HTTPServerRequest;
   using Response = Poco::Net::HTTPServerResponse;

   void handleRequest(Request& request, Response& response);

   Praline::TopicList& topicListM;
};

#endif
