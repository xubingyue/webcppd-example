#include <Poco/Util/Application.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Path.h>
#include <Poco/FileStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/File.h>
#include <Poco/NumericString.h>
#include <Poco/NumberFormatter.h>
#include <Poco/NumberParser.h>
#include <Poco/String.h>

#include <string>
#include <thread>
#include <chrono>
#include <vector>

#include "help/uploadPartHandler.hpp"
#include "help/mustache.hpp"

#include "upload.hpp"

namespace webcpp {
	namespace helloworld {

		void upload::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			Poco::Util::Application &app = Poco::Util::Application::instance();
			Poco::Path tplPath(app.config().getString("http.tplDirectory", "/var/www/tpl"));
			tplPath.append("/example/upload.html");

			if (!Poco::File(tplPath).exists()) {
				response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
				response.send() << tplPath.getFileName() + " is not exists.";
				return;
			}

			Poco::FileInputStream tplInput(tplPath.toString());
			std::string tplValue;
			Poco::StreamCopier::copyToString(tplInput, tplValue);

			Kainjow::Mustache::Data data = Kainjow::Mustache::Data::Type::Object;
			data.set("title", "upload 文件");
			if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST) {
				webcpp::uploadPartHandler handler("uploadFile1|uploadFile2", app.config().getString("http.uploadAllowType"), app.config().getString("http.root"), app.config().getDouble("http.uploadMaxSize"));
				Poco::Net::HTMLForm form(request, request.stream(), handler);
				auto result = handler.getData();
				auto fun = [](const std::vector<std::string>& path, int expires)
				{
					std::this_thread::sleep_for(std::chrono::seconds(expires));
					for (auto &item : path) {
						Poco::File tmpFile(item);
						if (tmpFile.exists()) {
							tmpFile.remove();
						}
					}
				};
				Kainjow::Mustache::Data list = Kainjow::Mustache::Data::Type::List;
				std::vector<std::string> path;
				for (auto & item : result) {
					Kainjow::Mustache::Data tmp = Kainjow::Mustache::Data::Type::Object;
					tmp.set("name", item.name);
					tmp.set("filename", item.filename);
					tmp.set("size", Poco::NumberFormatter::format(item.size));
					tmp.set("type", item.type);
					tmp.set("savepath", item.savepath);
					tmp.set("webpath", "/staticfile/index/" + item.webpath);
					tmp.set("ok", item.ok ? Poco::NumberFormatter::format(1) : Poco::NumberFormatter::format(0));
					tmp.set("message", item.message);

					list.push_back(tmp);

					path.push_back(item.savepath);
				}
				std::thread th(fun, path, 60);
				th.detach();
				data.set("list", list);
			}
			Kainjow::Mustache tplEngine(tplValue);
			tplEngine.render(data, response.send());



		}


	}
}