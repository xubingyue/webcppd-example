#include <Poco/ClassLibrary.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include "export.hpp"

POCO_BEGIN_MANIFEST(Poco::Net::HTTPRequestHandlerFactory)

POCO_EXPORT_CLASS(webcpp::helloworld::indexFactory)
POCO_EXPORT_CLASS(webcpp::helloworld::cookieFactory)
POCO_EXPORT_CLASS(webcpp::helloworld::loginFactory)
POCO_EXPORT_CLASS(webcpp::helloworld::logoutFactory)	
POCO_EXPORT_CLASS(webcpp::helloworld::gzipFactory)
POCO_EXPORT_CLASS(webcpp::helloworld::getFactory)
POCO_EXPORT_CLASS(webcpp::helloworld::postFactory)
POCO_EXPORT_CLASS(webcpp::helloworld::uploadFactory)	
	
POCO_END_MANIFEST