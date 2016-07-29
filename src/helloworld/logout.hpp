#ifndef LOGOUT_HPP
#define LOGOUT_HPP


#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>


namespace webcpp {
    namespace helloworld {

        class logout : public Poco::Net::HTTPRequestHandler {
        public:
            virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
        };

        class logoutFactory : public Poco::Net::HTTPRequestHandlerFactory {
        public:
            Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
        };
    }
}

#endif /* LOGOUT_HPP */

