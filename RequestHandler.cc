#include "RequestHandler.hh"

#include <Poco/Logger.h>
#include <Poco/URI.h>
#include <vector>

//
// /<topic> POST -> create topic
// /<topic> DELETE -> delete topic
// /<topic>/messages POST -> push message
// /<topic>/messages GET -> get message
// /<topic>/messages HEAD -> header
//
// HTTP/1.1 200 OK
// Date: Tue, 07 Jul 2015 15:58:56 GMT
// Connection: Keep-Alive
// Content-Length: 0
// X-Praline-First: 1234
// X-Praline-Last: 1400
//

using Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK;
using Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST;
using Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED;
using Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR;
using Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND;

namespace
{
   void internalError(Poco::Net::HTTPServerResponse& response)
   {
      response.setStatusAndReason(HTTP_INTERNAL_SERVER_ERROR);
      response.setContentLength(0);
      response.send().flush();
   }
}

using namespace praline;

RequestHandler::RequestHandler(praline::TopicList& topicList, Poco::Logger& logger)
   : topicListM(topicList),
     logM(logger)
{
}

void
RequestHandler::handleTopicPost(Request& request, Response& response, const std::string& topicName)
{
   logM.information("posting message to topic '%s'", topicName);
   
   auto res = topicListM.find(topicName);
   if (!res.first)
   {
      logM.information("topic '%s' is not existing or open", topicName);
      response.setStatusAndReason(HTTP_NOT_FOUND);
      response.setContentLength(0);
      response.send().flush();
   }
   else
   {
      auto topic = res.second;
      if (!topic.write(request.stream()))
      {
         logM.information("error writing to topic '%s'", topicName);
         internalError(response);
      }
      else
      {
         // or ACCEPTED when we go async?
         response.setStatusAndReason(HTTP_OK);
         response.setContentLength(0);
         response.send().flush();
      }
   }
}

void
RequestHandler::handleTopicGet(Request& request, Response& response, const std::string& topicName)
{
   logM.information("getting message from topic '%s'", topicName);
   
   response.setStatusAndReason(HTTP_BAD_REQUEST);
   response.setContentLength(0);
   response.send().flush();
}

void
RequestHandler::handleTopicPut(Request& request, Response& response, const std::string& topicName)
{
   logM.information("creating topic '%s'", topicName);

   auto topic = praline::Topic(topicName);
   bool success = topicListM.insert(topic);
   if (success)
   {
      if (!topic.open())
      {
         internalError(response);
         return;
      }
      response.setStatusAndReason(HTTP_CREATED);
      response.setContentLength(0);
      response.send().flush();
   }
   else
   {
      response.setStatusAndReason(HTTP_OK);
      response.setContentLength(0);
      response.send().flush();
   }
}

void
RequestHandler::handleTopicDelete(Request& request, Response& response, const std::string& topicName)
{
   logM.information("deleting topic '%s'", topicName);

   auto topic = praline::Topic(topicName);
   bool success = topicListM.remove(topic);
   if (success)
   {
      response.setStatusAndReason(HTTP_OK);
      response.setContentLength(0);
      response.send().flush();
   }
   else
   {
      response.setStatusAndReason(HTTP_NOT_FOUND);
      response.setContentLength(0);
      response.send().flush();
   }
}

void
RequestHandler::handleRequest(Request& request, Response& response)
{
   logM.information("URL: %s", request.getURI());
   logM.information("Method: %s", request.getMethod());

   std::vector<std::string> path;
   Poco::URI(request.getURI()).getPathSegments(path);
   if (path.size() == 1)
   {
      if (request.getMethod() == "PUT")
      {
         handleTopicPut(request, response, path[0]);
      }
      else if (request.getMethod() == "DELETE")
      {
         handleTopicDelete(request, response, path[0]);
      }
      else if (request.getMethod() == "POST")
      {
         handleTopicPost(request, response, path[0]);
      }
      else if (request.getMethod() == "GET")
      {
         handleTopicGet(request, response, path[0]);
      }
   }
   else
   {
      logM.information("dropping invalid request");
      response.setStatusAndReason(HTTP_BAD_REQUEST);
      response.setContentLength(0);
      response.send().flush();
   }
}
