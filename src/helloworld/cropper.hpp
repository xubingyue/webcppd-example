#ifndef CROPPER_HPP
#define CROPPER_HPP

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>

namespace webcpp {
    namespace helloworld {

        class cropper : public Poco::Net::HTTPRequestHandler {
            virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

        };
    }
}


#endif /* CROPPER_HPP */

