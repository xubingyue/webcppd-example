#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include <string>

namespace webcpp {
    namespace helloworld {

        class login : public Poco::Net::HTTPRequestHandler {
        public:
            virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
        private:
            static std::string secret;
        };
    }
}


#endif /* LOGIN_HPP */

