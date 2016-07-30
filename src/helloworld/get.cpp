#include <Poco/Util/Application.h>
#include <Poco/Path.h>
#include <Poco/FileStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/File.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/DeflatingStream.h>

#include "help/mustache.hpp"

#include "get.hpp"


namespace webcpp {
	namespace helloworld {

		void get::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			Poco::Util::Application &app = Poco::Util::Application::instance();
			Poco::Path tplPath(app.config().getString("http.tplDirectory", "/var/www/tpl"));
			tplPath.append("/example/get.html");

			if (!Poco::File(tplPath).exists()) {
				response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
				response.send() << tplPath.getFileName() + " is not exists.";
				return;
			}

			Poco::FileInputStream tplInput(tplPath.toString());
			std::string tplValue;

			response.setChunkedTransferEncoding(true);
			response.setContentType("text/html;charset=utf-8");
			response.set("Content-Encoding", "gzip");


			Poco::StreamCopier::copyToString(tplInput, tplValue);
			Poco::DeflatingOutputStream out(response.send(), Poco::DeflatingStreamBuf::STREAM_GZIP);
			
			Poco::Net::HTMLForm form(request);
			
			Kainjow::Mustache tplEngine(tplValue);
			Kainjow::Mustache::Data data = Kainjow::Mustache::Data::Type::Object;
			data.set("title", "GET 表单");
			if (form.empty()) {
				data.set("notSubmit", Kainjow::Mustache::Data::Type::True);

			} else {
				Kainjow::Mustache::Data list = Kainjow::Mustache::Data::Type::List;
				data.set("isSubmit", Kainjow::Mustache::Data::Type::True);
				for (auto& item : form) {
					Kainjow::Mustache::Data tmp = Kainjow::Mustache::Data::Type::Object;
					tmp.set("name", item.first);
					tmp.set("value", item.second);
					list.push_back(tmp);
				}
				data.set("list", list);

			}
			tplEngine.render(data, out);
			out.close();
		}

		Poco::Net::HTTPRequestHandler* getFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
		{
			return new webcpp::helloworld::get();
		}

	}
}