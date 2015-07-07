#ifndef REQUESTHANDLER_HH
#define REQUESTHANDLER_HH

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

class RequestHandler : public Poco::Net::HTTPRequestHandler
{
   void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

#endif
