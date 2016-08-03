#include <Poco/Util/Application.h>
#include <Poco/Path.h>
#include <Poco/FileStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/File.h>
#include <Poco/Net/HTTPCookie.h>
#include <Poco/NumberFormatter.h>
#include <Poco/Net/NameValueCollection.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/DigestStream.h>
#include <Poco/MD5Engine.h>
#include <Poco/URI.h>


#include "help/mustache.hpp"



#include "logout.hpp"


namespace webcpp {
	namespace helloworld {

		void logout::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			Poco::Util::Application &app = Poco::Util::Application::instance();
			Poco::Path tplPath(app.config().getString("http.tplDirectory", "/var/www/tpl"));
			tplPath.append("/example/logout.html");

			if (!Poco::File(tplPath).exists()) {
				response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
				response.send() << tplPath.getFileName() + " is not exists.";
				return;
			}

			Poco::FileInputStream tplInput(tplPath.toString());
			std::string tplValue;
			Poco::StreamCopier::copyToString(tplInput, tplValue);



			Poco::Net::HTTPCookie sessionCookie, emailCookie;
			sessionCookie.setName("session");
			emailCookie.setName("loginName");
			sessionCookie.setPath("/");
			emailCookie.setPath("/");
			sessionCookie.setMaxAge(0);
			emailCookie.setMaxAge(0);

			response.addCookie(sessionCookie);
			response.addCookie(emailCookie);



			Kainjow::Mustache::Data data = Kainjow::Mustache::Data::Type::Object;
			data.set("title", "退出");

			Kainjow::Mustache tpl(tplValue);
			tpl.render(data, response.send());



		}



	}
}