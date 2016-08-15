#ifndef VALIDATE_HPP
#define VALIDATE_HPP

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

namespace webcpp {
    namespace helloworld {

        class validate : public Poco::Net::HTTPRequestHandler {
            virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

        };
    }
}


#endif /* VALIDATE_HPP */

