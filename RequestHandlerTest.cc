#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "hippomocks.h"

#include "RequestHandler.hh"

#include "stubs/HTTPServerRequestStub.hh"
#include "stubs/HTTPServerResponseStub.hh"

#include <Poco/NullChannel.h>

using namespace praline;

//using HTTPStatus = Poco::Net::HTTPResponse::HTTPStatus;
using Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK;
using Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST;
using Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED;
using Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR;

SCENARIO("RequestHandlerTest", "[http]")
{
   GIVEN("A request handler")
   {
      MockRepository mocks;
      TopicList& tl = *mocks.Mock<TopicList>();
      mocks.ExpectCall(&tl, TopicList::insert).Return(true);

      RequestHandler rh(tl);
      
      WHEN("Doing a PUT request to /topic")
      {
         HTTPServerRequestStub request;
         request.setMethod("PUT");
         request.setURI("/topic");

         HTTPServerResponseStub response;

         rh.handleRequest(request, response);

         THEN("The topic is created")
         {
            CHECK(response.getStatus() == 201);
         }
      }
   }
}
