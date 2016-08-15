#include <Poco/Util/Application.h>
#include <Poco/Path.h>
#include <Poco/FileStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/RegularExpression.h>
#include <Poco/URI.h>
#include <Poco/File.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/JSON/Object.h>
#include <Poco/String.h>




#include "help/mustache.hpp"
#include "help/validation.hpp"


#include "validate.hpp"



namespace webcpp {
	namespace helloworld {

		void validate::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			Poco::URI uri = Poco::URI(request.getURI());

			if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST) {
				response.setContentType("application/json;charset=utf-8");
				Poco::JSON::Object data;

				Poco::Net::HTMLForm form(request, request.stream());

				if (form.has("text") && form.has("pattern")) {
					std::string text = form.get("text"), pattern = form.get("pattern");
					if (pattern == "chinese") {
						data.set("ok", webcpp::validation::match(text, webcpp::validation::CHINESE) ? 1 : 0);
					} else if (pattern == "email") {
						data.set("ok", webcpp::validation::match(text, webcpp::validation::EMAIL) ? 1 : 0);
					} else if (pattern == "idcard") {
						data.set("ok", webcpp::validation::match(text, webcpp::validation::IDCARD) ? 1 : 0);
					} else if (pattern == "mobile") {
						data.set("ok", webcpp::validation::match(text, webcpp::validation::MOBILE) ? 1 : 0);
					} else {
						data.set("ok", 0);
					}

				} else {
					data.set("ok", 0);
				}
				data.stringify(response.send());
				return;
			}
			Poco::Util::Application &app = Poco::Util::Application::instance();
			Poco::Path tplPath(app.config().getString("http.tplDirectory", "/var/www/tpl"));
			tplPath.append("/example/validate.html");

			if (!Poco::File(tplPath).exists()) {
				response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
				response.send() << tplPath.getFileName() + " is not exists.";
				return;
			}

			Poco::FileInputStream tplInput(tplPath.toString());
			std::string tplValue;
			Poco::StreamCopier::copyToString(tplInput, tplValue);

			Kainjow::Mustache::Data data = Kainjow::Mustache::Data::Type::Object;
			data.set("title", "表单数据验证");


			response.setChunkedTransferEncoding(true);
			response.setContentType("text/html;charset=utf-8");

			Kainjow::Mustache tplEngine(tplValue);
			tplEngine.render(data, response.send());
		}


	}
}