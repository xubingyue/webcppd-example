#include <Poco/ClassLibrary.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include "export.hpp"

POCO_BEGIN_MANIFEST(Poco::Net::HTTPRequestHandler)
	
POCO_EXPORT_CLASS(webcpp::staticfile::index)
POCO_EXPORT_CLASS(webcpp::staticfile::list)

POCO_END_MANIFEST
