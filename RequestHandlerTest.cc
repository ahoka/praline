#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "fakeit.hpp"

#include "RequestHandler.hh"

#include <Poco/NullChannel.h>

using namespace fakeit;
using namespace praline;

SCENARIO("RequestHandlerTest", "[http]")
{
   GIVEN("A request handler")
   {
      Mock<TopicList> topicListMock;
      RequestHandler rh(topicListMock.get());

      WHEN("Doing a POST request to /topic")
      {
         Mock<RequestHandler::Response> response;
         Mock<RequestHandler::Request> request;

         Method(request, getMethod) = std::string("POST");
         Method(request, getURI) = std::string("/topic");

//         rh.handleRequest(request.get(), response.get());

         THEN("The topic is created")
         {
         }
      }
   }
}
