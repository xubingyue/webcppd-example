#ifndef GZIP_HPP
#define GZIP_HPP


#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>


namespace webcpp {
    namespace helloworld {

        class gzip : public Poco::Net::HTTPRequestHandler {
        public:
            virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
        };

        class gzipFactory : public Poco::Net::HTTPRequestHandlerFactory {
        public:
            Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
        };
    }
}

#endif /* GZIP_HPP */

