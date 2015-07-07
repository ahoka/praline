#ifndef HTTPSUBSYSTEM_HH
#define HTTPSUBSYSTEM_HH

#include <Poco/Util/Subsystem.h>
#include <Poco/Util/Application.h>

#include <Poco/Net/HTTPServer.h>

class HttpSubsystem : public Poco::Util::Subsystem
{
private:
   virtual void initialize(Poco::Util::Application& app);
   virtual const char* name() const;
   virtual void reinitialize(Poco::Util::Application& app);
   virtual void uninitialize();

   Poco::Net::HTTPServer* serverM;
};

#endif
