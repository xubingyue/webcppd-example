#include <Poco/Util/Application.h>

#include "index.hpp"

namespace webcpp {
	namespace helloworld {

		void index::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			Poco::Util::Application &app = Poco::Util::Application::instance();
			response.setChunkedTransferEncoding(true);
			response.send() << "<html>"
				<< "<head>"
				<< "</head>"
				<< "<body>"
				<< "<p>hello world</p>"
				<< "</body>"
				<< "</html>";
		}

		Poco::Net::HTTPRequestHandler* indexFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
		{
			return new webcpp::helloworld::index();
		}
	}
}



