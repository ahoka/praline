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
   
   void redirect(const std::string & uri, HTTPStatus status = HTTP_FOUND)
   {
   }

   void requireAuthentication(const std::string & realm)
   {
   }

   virtual std::ostream & send()
   {
      return streamM;
   }

   void sendBuffer(const void * pBuffer, std::size_t length)
   {
   }

   void sendContinue()
   {
   }

   void sendFile(const std::string & path, const std::string & mediaType)
   {
   }

   bool sent() const
   {
      return false;
   }
};

#endif
