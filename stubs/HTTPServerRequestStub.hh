#ifndef HTTPSERVERREQUESTSTUB_HH
#define HTTPSERVERREQUESTSTUB_HH

#include <Poco/Net/HTTPServerRequest.h>

using namespace Poco::Net;

class HTTPServerRequestStub : public HTTPServerRequest
{
   const SocketAddress & clientAddress() const
   {
      return *(SocketAddress*)0;
   }

   bool expectContinue() const
   {
      return false;
   }

   HTTPServerResponse & response() const
   {
      return *(HTTPServerResponse*)0;
   }

   const SocketAddress & serverAddress() const
   {
      return *(SocketAddress*)0;
   }

   const HTTPServerParams & serverParams() const
   {
      return *(HTTPServerParams*)0;
   }

   std::istream& stream()
   {
      return *(std::istream*)0;
   }
};

#endif
