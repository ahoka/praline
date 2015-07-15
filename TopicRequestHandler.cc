#include "RequestHandler.hh"

#include <Poco/Logger.h>
#include <Poco/URI.h>
#include <vector>

namespace
{
   Poco::Logger& logger = Poco::Logger::get("RequestHandler");
}

using Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK;
using Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST;
using Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED;
using Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR;

RequestHandler::RequestHandler(Praline::TopicList& topicList)
   : topicListM(topicList)
{
}

namespace
{
   void internalError(Poco::Net::HTTPServerResponse& response)
   {
      response.setStatusAndReason(HTTP_INTERNAL_SERVER_ERROR);
      response.setContentLength(0);
      response.send().flush();
   }
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
      auto topic = Praline::Topic(path[0]);
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
