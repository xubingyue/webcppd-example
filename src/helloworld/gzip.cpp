#include <Poco/DeflatingStream.h>



#include "gzip.hpp"

namespace webcpp {
	namespace helloworld {

		void gzip::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			response.set("Content-Encoding", "gzip");
			Poco::DeflatingOutputStream out(response.send(), Poco::DeflatingStreamBuf::STREAM_GZIP);
			out << "hello world .";
			out.close();

		}

		Poco::Net::HTTPRequestHandler* gzipFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
		{
			return new webcpp::helloworld::gzip();
		}


	}
}