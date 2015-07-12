#include "RequestHandler.hh"

#include <Poco/Logger.h>
#include <Poco/URI.h>
#include <vector>

namespace
{
   Poco::Logger& logger = Poco::Logger::get("RequestHandler");
}

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

RequestHandler::RequestHandler(Praline::TopicList& topicList)
   : topicListM(topicList)
{
}

void RequestHandler::handleRequest(Request& request, Response& response)
{
   logger.information("URL: %s", request.getURI());
   logger.information("Method: %s", request.getMethod());

   std::vector<std::string> path;
   Poco::URI(request.getURI()).getPathSegments(path);
   logger.information("Path len: %z", path.size());

   if (request.getMethod() == "PUT" && path.size() == 1)
   {
      logger.information("creating topic %s", path[0]);
      bool success = topicListM.insert(Topic(path[0]));
      if (success)
      {
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
      return;
   }

   if (path.size() != 2)
   {
      logger.information("dropping request");
      response.setStatusAndReason(HTTP_BAD_REQUEST);
      response.setContentLength(0);
      response.send().flush();
      return;
   }

   logger.information("request valid");
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
