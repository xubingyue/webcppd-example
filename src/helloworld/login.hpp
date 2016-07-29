#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include <string>

namespace webcpp {
    namespace helloworld {

        class login : public Poco::Net::HTTPRequestHandler {
        public:
            virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
        private:
            static std::string secret;
        };

        class loginFactory : public Poco::Net::HTTPRequestHandlerFactory {
        public:
            Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
        };
    }
}


#endif /* LOGIN_HPP */

