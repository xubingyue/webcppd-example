#include <Poco/Util/Application.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/FileStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/File.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/MD5Engine.h>
#include <Poco/JSON/Object.h>
#include <Poco/RegularExpression.h>
#include <Poco/Net/HTTPCookie.h>

#include "help/mustache.hpp"
#include "help/cvcaptcha.hpp"



#include "captcha.hpp"

namespace webcpp {
	namespace helloworld {

		void captcha::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			Poco::URI uri = Poco::URI(request.getURI());
			Poco::MD5Engine md5;
			std::string captchaKey("captchaCode"), captchaValue;
			if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST) {
				response.setContentType("application/json;charset=utf-8");
				Poco::JSON::Object data;
				Poco::RegularExpression regex("/helloworld/captcha/validate/?.*");

				Poco::Net::HTMLForm form(request, request.stream());

				Poco::Net::NameValueCollection cookies;
				request.getCookies(cookies);

				if (regex.match(uri.getPath()) && form.has(captchaKey) && cookies.has(captchaKey)) {
					md5.update(form.get(captchaKey));
					captchaValue = Poco::MD5Engine::digestToHex(md5.digest());
					if (captchaValue == cookies.get(captchaKey)) {
						Poco::Net::HTTPCookie cookie;
						cookie.setName(captchaKey);
						cookie.setMaxAge(0);
						cookie.setPath("/");
						response.addCookie(cookie);
						data.set("ok", 1);
					} else {
						data.set("ok", 0);
					}
				} else {
					data.set("ok", 0);
				}
				data.stringify(response.send());
				return;
			}
			Poco::RegularExpression regex("/helloworld/captcha/get/?.*");
			if (regex.match(Poco::URI(request.getURI()).getPath())) {
				response.setContentType("image/png");
				webcpp::cvCaptcha cvCaptcha;
				cvCaptcha.addEllipse();
				cvCaptcha.addLine();
				cvCaptcha.addSlate();
				cvCaptcha.create();
				Poco::MD5Engine md5;
				md5.update(cvCaptcha.getContent());
				captchaValue = Poco::MD5Engine::digestToHex(md5.digest());
				Poco::Net::HTTPCookie cookie;
				cookie.setName(captchaKey);
				cookie.setValue(captchaValue);
				cookie.setPath("/");
				cookie.setMaxAge(60);
				response.addCookie(cookie);
				response.send() << cvCaptcha;
				return;

			}
			Poco::Util::Application &app = Poco::Util::Application::instance();
			Poco::Path tplPath(app.config().getString("http.tplDirectory", "/var/www/tpl"));
			tplPath.append("/example/captcha.html");

			if (!Poco::File(tplPath).exists()) {
				response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
				response.send() << tplPath.getFileName() + " is not exists.";
				return;
			}

			Poco::FileInputStream tplInput(tplPath.toString());
			std::string tplValue;
			Poco::StreamCopier::copyToString(tplInput, tplValue);

			Kainjow::Mustache::Data data = Kainjow::Mustache::Data::Type::Object;
			data.set("title", "验证码");
			Kainjow::Mustache tplEngine(tplValue);
			tplEngine.render(data, response.send());

		}

	}
}