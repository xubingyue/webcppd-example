#ifndef AJAX_HPP
#define AJAX_HPP



#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>


namespace webcpp {
    namespace helloworld {

        class ajax : public Poco::Net::HTTPRequestHandler {
        public:
            virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
        };

    }
}

#endif /* AJAX_HPP */

