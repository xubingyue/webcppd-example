#include <Poco/ClassLibrary.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include "export.hpp"

POCO_BEGIN_MANIFEST(Poco::Net::HTTPRequestHandler)

POCO_EXPORT_CLASS(webcpp::helloworld::index)
POCO_EXPORT_CLASS(webcpp::helloworld::cookie)
POCO_EXPORT_CLASS(webcpp::helloworld::login)
POCO_EXPORT_CLASS(webcpp::helloworld::logout)
POCO_EXPORT_CLASS(webcpp::helloworld::gzip)
POCO_EXPORT_CLASS(webcpp::helloworld::get)
POCO_EXPORT_CLASS(webcpp::helloworld::post)
POCO_EXPORT_CLASS(webcpp::helloworld::upload)
POCO_EXPORT_CLASS(webcpp::helloworld::ajax)
POCO_EXPORT_CLASS(webcpp::helloworld::captcha)
POCO_EXPORT_CLASS(webcpp::helloworld::cropper)
POCO_EXPORT_CLASS(webcpp::helloworld::validate)
	
	
POCO_END_MANIFEST