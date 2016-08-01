#ifndef INDEX_HPP
#define INDEX_HPP

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandler.h>

namespace webcpp {
    namespace staticfile {

        class index : public Poco::Net::HTTPRequestHandler {
        public:
            virtual void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res);
        };

        class indexFactory : public Poco::Net::HTTPRequestHandlerFactory {
            Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;

        };
    }
}

#endif /* INDEX_HPP */

