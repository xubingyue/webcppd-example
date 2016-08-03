#include <Poco/Util/Application.h>
#include <Poco/Path.h>
#include <Poco/FileStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/File.h>
#include <Poco/Net/HTTPCookie.h>
#include <Poco/NumberFormatter.h>
#include <Poco/Net/NameValueCollection.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/MD5Engine.h>
#include <Poco/URI.h>
#include <Poco/JSON/Object.h>


#include "help/mustache.hpp"

#include "login.hpp"

namespace webcpp {
	namespace helloworld {

		std::string login::secret = "abcdefghijklmnopqrstuvwxyz@0123456789";

		void login::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST) {
				Poco::Net::HTMLForm form(request, request.stream());
				if (form.has("InputEmail") && form.has("InputPassword")) {
					std::string InputEmail = form.get("InputEmail"), InputPassword = form.get("InputPassword"), password("123456");
					Poco::JSON::Object result;
					response.setContentType("applicaton/json;charset=utf-8");
					if (InputPassword == password) {
						Poco::MD5Engine md5;

						md5.update(InputEmail + login::secret);

						Poco::Net::HTTPCookie sessionCookie, emailCookie;
						sessionCookie.setName("session");
						sessionCookie.setValue(Poco::MD5Engine::digestToHex(md5.digest()));
						sessionCookie.setMaxAge(-1);
						sessionCookie.setPath("/");
						response.addCookie(sessionCookie);

						emailCookie.setName("loginName");
						emailCookie.setValue(InputEmail);
						emailCookie.setPath("/");
						emailCookie.setMaxAge(-1);
						response.addCookie(emailCookie);


						result.set("ok", 1);
					} else {
						result.set("ok", 0);

					}
					result.stringify(response.send());
					return;
				}
			}
			Poco::Util::Application &app = Poco::Util::Application::instance();
			Poco::Path tplPath(app.config().getString("http.tplDirectory", "/var/www/tpl"));
			tplPath.append("/example/login.html");

			if (!Poco::File(tplPath).exists()) {
				response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
				response.send() << tplPath.getFileName() + " is not exists.";
				return;
			}

			Poco::FileInputStream tplInput(tplPath.toString());
			std::string tplValue;
			Poco::StreamCopier::copyToString(tplInput, tplValue);


			Kainjow::Mustache::Data data = Kainjow::Mustache::Data::Type::Object;
			data.set("title", "登陆");
			Poco::Net::NameValueCollection cookies;
			request.getCookies(cookies);
			if (cookies.has("session") && cookies.has("loginName")) {
				Poco::MD5Engine md5;
				md5.update(cookies.get("loginName") + login::secret);
				if (cookies.get("session") == Poco::MD5Engine::digestToHex(md5.digest())) {
					data.set("isLogin", Kainjow::Mustache::Data::Type::True);
					data.set("notLogin", Kainjow::Mustache::Data::Type::False);
					data.set("loginName", cookies.get("loginName"));
				} else {
					data.set("isLogin", Kainjow::Mustache::Data::Type::False);
					data.set("notLogin", Kainjow::Mustache::Data::Type::True);
				}
			} else {
				data.set("isLogin", Kainjow::Mustache::Data::Type::False);
				data.set("notLogin", Kainjow::Mustache::Data::Type::True);
			}


			Kainjow::Mustache tpl(tplValue);
			tpl.render(data, response.send());
		}



	}
}