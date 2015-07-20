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
RequestHandler::handleTopicPut(Request& request, Response& response, const std::string& topicName)
{
   logM.information("creating topic %s", topicName);

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
   logM.information("deleting topic %s", topicName);

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
   logM.information("Path len: %z", path.size());

   if (path.size() == 1)
   {
      if (request.getMethod() == "PUT")
      {
         handleTopicPut(request, response, path[0]);
         return;
      }
      else if (request.getMethod() == "DELETE")
      {
         handleTopicDelete(request, response, path[0]);
         return;
      }
   }

   if (path.size() != 2)
   {
      logM.information("dropping request");
      response.setStatusAndReason(HTTP_BAD_REQUEST);
      response.setContentLength(0);
      response.send().flush();
      return;
   }

   logM.information("request valid");
//   path[0]

//   response.setContentLength(0);
   response.setChunkedTransferEncoding(true);
   response.setStatusAndReason(HTTP_OK);

   auto& stream = response.send();

   stream << "H";
   stream << "e";
   stream << "l";
   stream << "l";

   stream.flush();

   stream << "o";
   stream << "!";
   stream << "\r";
   stream << "\n";

   stream.flush();
}
