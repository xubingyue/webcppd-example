#include <Poco/Util/Application.h>
#include <Poco/Path.h>
#include <Poco/FileStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/File.h>
#include <Poco/Net/HTTPCookie.h>
#include <Poco/NumberFormatter.h>
#include <Poco/Net/NameValueCollection.h>

#include "help/mustache.hpp"

#include "cookie.hpp"

namespace webcpp {
	namespace helloworld {

		void cookie::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			Poco::Util::Application &app = Poco::Util::Application::instance();
			Poco::Path tplPath(app.config().getString("http.tplDirectory", "/var/www/tpl"));
			tplPath.append("/example/cookie.html");

			if (!Poco::File(tplPath).exists()) {
				response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
				response.send() << tplPath.getFileName() + " is not exists.";
				return;
			}

			Poco::FileInputStream tplInput(tplPath.toString());
			std::string tplValue;
			Poco::StreamCopier::copyToString(tplInput, tplValue);


			Kainjow::Mustache::Data data = Kainjow::Mustache::Data::Type::Object;
			data.set("title", "cookie 列表");
			Poco::Net::NameValueCollection cookies;
			request.getCookies(cookies);

			int maxCount = 10, count = static_cast<int> (cookies.size());

			if (count < maxCount) {
				std::string countStr = Poco::NumberFormatter::format(count);
				Poco::Net::HTTPCookie cookie;
				cookie.setName("session_" + countStr);
				cookie.setValue(countStr);
				cookie.setDomain("localhost");
				cookie.setMaxAge(3600);
				cookie.setPath("/");
				cookie.setHttpOnly(true);
				response.addCookie(cookie);
			}




			Kainjow::Mustache::Data list = Kainjow::Mustache::Data::Type::List;
			for (auto& item : cookies) {
				Kainjow::Mustache::Data tmp = Kainjow::Mustache::Data::Type::Object;
				tmp.set("name", item.first);
				tmp.set("value", item.second);
				list.push_back(tmp);
			}
			data.set("list", list);

			response.setChunkedTransferEncoding(true);
			response.setContentType("text/html;charset=utf-8");

			Kainjow::Mustache tplEngine(tplValue);
			tplEngine.render(data, response.send());
		}



	}
}
