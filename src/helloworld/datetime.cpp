#include <Poco/LocalDateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>
#include "datetime.hpp"


namespace webcpp {
	namespace helloworld {

		void datetime::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			Poco::LocalDateTime now;
			response.send() << Poco::DateTimeFormatter::format(now.timestamp(), Poco::DateTimeFormat::HTTP_FORMAT);
		}

		Poco::Net::HTTPRequestHandler* datetimeFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
		{
			return new webcpp::helloworld::datetime();
		}


	}
}