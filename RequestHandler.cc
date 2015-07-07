#include "RequestHandler.hh"

#include <Poco/Logger.h>
#include <Poco/URI.h>
#include <vector>

namespace
{
   Poco::Logger& logger = Poco::Logger::get("RequestHandler");
}

using Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK;

void RequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
   logger.information(Poco::Logger::format("URL: $0", request.getURI()));
   logger.information("Method: %s", request.getMethod());

   std::vector<std::string> path;
   Poco::URI(request.getURI()).getPathSegments(path);
   logger.information("Path len: %z", path.size());
//   path[0]

//   response.setContentLength(0);
   response.setChunkedTransferEncoding(true);
   response.setStatus(HTTP_OK);

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
