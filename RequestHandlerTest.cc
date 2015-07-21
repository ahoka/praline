#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "hippomocks.h"

#include "RequestHandler.hh"

#include "stubs/HTTPServerRequestStub.hh"
#include "stubs/HTTPServerResponseStub.hh"

#include <Poco/NullChannel.h>

using namespace praline;
using namespace Poco::Net;

SCENARIO("RequestHandlerTest", "[http]")
{
   GIVEN("A request handler")
   {
      MockRepository mocks;
      TopicList& tl = *mocks.Mock<TopicList>();
      mocks.ExpectCall(&tl, TopicList::insert).Return(true);

      RequestHandler rh(tl);

      WHEN("Doing a PUT request to a non existing /topic")
      {
         HTTPServerRequestStub request;
         request.setMethod("PUT");
         request.setURI("/topic");

         HTTPServerResponseStub response;

         rh.handleRequest(request, response);

         THEN("The topic is created")
         {
            CHECK(response.getStatus() == HTTPResponse::HTTPStatus::HTTP_CREATED);
         }
      }
   }

   GIVEN("A request handler")
   {
      MockRepository mocks;
      TopicList& tl = *mocks.Mock<TopicList>();
      mocks.ExpectCall(&tl, TopicList::insert).Return(false);

      RequestHandler rh(tl);

      WHEN("Doing a PUT request to an existing /topic")
      {
         HTTPServerRequestStub request;
         request.setMethod("PUT");
         request.setURI("/topic");

         HTTPServerResponseStub response;

         rh.handleRequest(request, response);

         THEN("The topic creation is idempotent")
         {
            CHECK(response.getStatus() == HTTPResponse::HTTPStatus::HTTP_OK);
         }
      }
   }

   GIVEN("A request handler")
   {
      MockRepository mocks;
      TopicList& tl = *mocks.Mock<TopicList>();
      mocks.ExpectCall(&tl, TopicList::remove).Return(true);

      RequestHandler rh(tl);

      WHEN("Doing a DELETE request to an existing /topic")
      {
         HTTPServerRequestStub request;
         request.setMethod("DELETE");
         request.setURI("/topic");

         HTTPServerResponseStub response;

         rh.handleRequest(request, response);

         THEN("The request succeeds")
         {
            CHECK(response.getStatus() == HTTPResponse::HTTPStatus::HTTP_OK);
         }
      }
   }

   GIVEN("A request handler")
   {
      MockRepository mocks;
      TopicList& tl = *mocks.Mock<TopicList>();
      mocks.ExpectCall(&tl, TopicList::remove).Return(false);

      RequestHandler rh(tl);

      WHEN("Doing a DELETE request to an non existing /topic")
      {
         HTTPServerRequestStub request;
         request.setMethod("DELETE");
         request.setURI("/topic");

         HTTPServerResponseStub response;

         rh.handleRequest(request, response);

         THEN("The topic was not found")
         {
            CHECK(response.getStatus() == HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
         }
      }
   }
}
