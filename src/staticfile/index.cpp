#include <Poco/Util/Application.h>
#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/DateTimeParser.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/Format.h>
#include <Poco/RegularExpression.h>


#include "help/mime.hpp"

#include "index.hpp"

namespace webcpp {
	namespace staticfile {

		void index::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			Poco::Util::Application &app = Poco::Util::Application::instance();
			std::string url = Poco::URI(request.getURI()).getPath();
			Poco::RegularExpression regex("^/staticfile/index/(.*)$");
			if (regex.subst(url, "/$1") == 0) {
				url = "/";
			}

			Poco::Path path(app.config().getString("http.root", "/var/www") + url);


			if (path.isDirectory() || path.getExtension().empty()) {
				path.append("index.html");
			}


			Poco::File file(path);

			if (file.exists() && path.isFile()) {

				Poco::DateTime dt;
				int tz;

				if (request.has("If-Modified-Since")) {
					Poco::DateTimeParser::parse(Poco::DateTimeFormat::HTTP_FORMAT, request.get("If-Modified-Since"), dt, tz);
					if (file.getLastModified() == dt.timestamp()) {
						response.setStatusAndReason(Poco::Net::HTTPServerResponse::HTTP_NOT_MODIFIED);
						response.set("Last-Modified", Poco::DateTimeFormatter::format(dt, Poco::DateTimeFormat::HTTP_FORMAT, tz));
					}
				}

				response.setChunkedTransferEncoding(true);
				response.set("Cache-Control", Poco::format("max-age=%[0]d", app.config().getInt("http.expires", 3600)));
				response.add("Cache-Control", "must-revalidate");
				std::string mimeType = webcpp::mime().getType(path.getExtension());
				response.sendFile(path.toString(), mimeType);

			} else {
				response.setStatusAndReason(Poco::Net::HTTPServerResponse::HTTP_NOT_FOUND);

				response.setContentType("text/html;charset=UTF-8");
				response.send() << "<html><head><title>"
					<< static_cast<int> (response.getStatus())
					<< " "
					<< response.getReason()
					<< "</title><body bgcolor=\"white\"><center><h1>"
					<< static_cast<int> (response.getStatus())
					<< " "
					<< response.getReason()
					<< "</h1></center><hr/>"
					<< "</body></html>";
			}


		}

	}
}
