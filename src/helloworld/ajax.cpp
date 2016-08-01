#include <Poco/Util/Application.h>
#include <Poco/Path.h>
#include <Poco/FileStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/File.h>

#include <Poco/Random.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <Poco/Net/HTMLForm.h>

#include "help/mustache.hpp"

#include "ajax.hpp"


namespace webcpp {
	namespace helloworld {

		void ajax::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST) {
				Poco::Net::HTMLForm form(request, request.stream());
				response.setContentType("application/json;charset=utf-8");
				Poco::Random rng;
				Poco::JSON::Object result;
				if (form.has("method")) {
					Poco::JSON::Array list;
					int count = 5;
					for (int i = 0; i < count; ++i) {

						if (form.get("method") == "getDouble") {
							list.add(rng.nextDouble());
						}
						if (form.get("method") == "getInt") {
							list.add(rng.next(1000));
						}

					}
					result.set("items", list);
					result.set("ok", 1);
				} else {
					result.set("ok", 0);
				}

				result.stringify(response.send());
			} else {
				Poco::Util::Application &app = Poco::Util::Application::instance();
				Poco::Path tplPath(app.config().getString("http.tplDirectory", "/var/www/tpl"));
				tplPath.append("/example/ajax.html");

				if (!Poco::File(tplPath).exists()) {
					response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
					response.send() << tplPath.getFileName() + " is not exists.";

					return;
				}

				Poco::FileInputStream tplInput(tplPath.toString());
				std::string tplValue;
				Poco::StreamCopier::copyToString(tplInput, tplValue);

				Kainjow::Mustache::Data data = Kainjow::Mustache::Data::Type::Object;
				data.set("title", "Ajax");


				response.setChunkedTransferEncoding(true);
				response.setContentType("text/html;charset=utf-8");

				Kainjow::Mustache tplEngine(tplValue);
				tplEngine.render(data, response.send());
			}


		}

		Poco::Net::HTTPRequestHandler * ajaxFactory::createRequestHandler(const Poco::Net::HTTPServerRequest & request)
		{
			return new webcpp::helloworld::ajax();
		}

	}
}