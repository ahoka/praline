#ifndef PRALINE_HH
#define PRALINE_HH

#include <Poco/Util/ServerApplication.h>

namespace Praline
{

class Praline : public Poco::Util::ServerApplication {
public:
    Praline();
    ~Praline();
private:
    int main(const std::vector<std::string>& args);
};

}

#endif
