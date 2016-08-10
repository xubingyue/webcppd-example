#include <Poco/Format.h>
#include <Poco/NumericString.h>
#include <Poco/Util/Application.h>
#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/StreamCopier.h>
#include <libmemcached/memcached.hpp>

#include <fstream>

#include "../helloworld/help/mustache.hpp"

#include "index.hpp"

namespace webcpp {
	namespace home {

		void index::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			response.redirect("/helloworld/index");
		}
	}
}



