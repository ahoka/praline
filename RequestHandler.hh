#ifndef REQUESTHANDLER_HH
#define REQUESTHANDLER_HH

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Logger.h>

#include "TopicList.hh"

#include <cstdint>

namespace praline
{

class RequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
   using Request = Poco::Net::HTTPServerRequest;
   using Response = Poco::Net::HTTPServerResponse;

   RequestHandler(TopicList&, Poco::Logger& logger = Poco::Logger::get("RequestHandler"));
   void handleRequest(Request& request, Response& response);

private:
   void handleTopicGet(Request&, Response&, const std::string&);
   void handleTopicPost(Request&, Response&, const std::string&);
   void handleTopicPut(Request&, Response&, const std::string&);
   void handleTopicDelete(Request&, Response&, const std::string&);
   void handleSubscribe(Request&, Response&, const std::string&, uint64_t);

   TopicList& topicListM;
   Poco::Logger& logM;
};

}

#endif
