#ifndef HTTPSERVERRESPONSESTUB_HH
#define HTTPSERVERRESPONSESTUB_HH

#include <Poco/Net/HTTPServerResponse.h>

#include <sstream>

using namespace Poco::Net;

class HTTPServerResponseStub : public HTTPServerResponse
{
public:
   HTTPServerResponseStub()
      : bufferM(),
        streamM(bufferM)
   {
   }
   
   const std::string& getDataSent() const
   {
      return bufferM;
   }
   
private:
   std::string bufferM;
   std::stringstream streamM;
   
   void redirect(const std::string&, HTTPStatus)
   {
   }

   void requireAuthentication(const std::string&)
   {
   }

   virtual std::ostream & send()
   {
      return streamM;
   }

   void sendBuffer(const void*, std::size_t)
   {
   }

   void sendContinue()
   {
   }

   void sendFile(const std::string&, const std::string&)
   {
   }

   bool sent() const
   {
      return false;
   }
};

#endif
