#include <Poco/Util/Application.h>
#include <Poco/Path.h>
#include <Poco/FileStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/File.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/RegularExpression.h>
#include <Poco/URI.h>
#include "help/cvqrcode.hpp"


#include "help/mustache.hpp"

#include "qrencode.hpp"

namespace webcpp {
	namespace helloworld {

		void qrencode::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{

			Poco::RegularExpression regex("/helloworld/qrencode/create/?.*");
			if (regex.match(Poco::URI(request.getURI()).getPath())) {
				Poco::Net::HTMLForm form(request);
				if (form.has("text")) {
					std::string text = form.get("text");
					if (text.size() <= 500) {
						webcpp::cvqrcode qrcode(text);
						if (qrcode.created()) {
							response.setContentType("image/png");
							response.send() << qrcode;
							return;
						} else {
							response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
							response.setContentType("text/plain");
							response.send() << "create image failed";
							return;
						}
					} else {
						response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
						response.setContentType("text/plain");
						response.send() << "create text is too bigger ";
						return;
					}
				} else {
					response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
					response.setContentType("text/plain");
					response.send() << "request method failed";
					return;
				}
			}
			Poco::Util::Application &app = Poco::Util::Application::instance();
			Poco::Path tplPath(app.config().getString("http.tplDirectory", "/var/www/tpl"));
			tplPath.append("/example/qrencode.html");

			if (!Poco::File(tplPath).exists()) {
				response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
				response.send() << tplPath.getFileName() + " is not exists.";
				return;
			}

			Poco::FileInputStream tplInput(tplPath.toString());
			std::string tplValue;
			Poco::StreamCopier::copyToString(tplInput, tplValue);

			Kainjow::Mustache::Data data = Kainjow::Mustache::Data::Type::Object;
			data.set("title", "二维码创建");

			response.setChunkedTransferEncoding(true);
			response.setContentType("text/html;charset=utf-8");

			Kainjow::Mustache tplEngine(tplValue);
			tplEngine.render(data, response.send());


		}

	}
}

