#include <Poco/ClassLibrary.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include "export.hpp"

POCO_BEGIN_MANIFEST(Poco::Net::HTTPRequestHandlerFactory)
	
POCO_EXPORT_CLASS(webcpp::staticfile::indexFactory)
POCO_EXPORT_CLASS(webcpp::staticfile::listFactory)

POCO_END_MANIFEST
