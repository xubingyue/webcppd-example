#include <Poco/Util/Application.h>
#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/DateTimeParser.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/Format.h>
#include <Poco/StreamCopier.h>
#include <Poco/RegularExpression.h>
#include <Poco/DirectoryIterator.h>
#include <Poco/SortedDirectoryIterator.h>
#include <fstream>
#include <vector>
#include <Poco/NumberFormatter.h>

#include "../helloworld/help/mustache.hpp"

#include "list.hpp"

namespace webcpp {
	namespace staticfile {

		void list::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			Poco::Util::Application &app = Poco::Util::Application::instance();

			if (!app.config().getBool("http.enableIndex", false)) {
				response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
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
			} else {
				Poco::Path tplPath(app.config().getString("http.tplDirectory", "/var/www/tpl") + "/staticfile/list.html");
				if (!Poco::File(tplPath).exists()) {
					response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
					response.send() << tplPath.getFileName() + " template file is not found.";
				} else {
					std::string tplKey("webcpp::staticfile::list.tpl"), tplValue;
					std::ifstream tplIn(tplPath.toString(), std::ifstream::in);
					Poco::StreamCopier::copyToString(tplIn, tplValue);
					std::string url = Poco::URI(request.getURI()).getPath();
					Poco::RegularExpression regex("^/staticfile/list/(.*)$");
					if (regex.subst(url, "/$1") == 0) {
						url = "/";
					}
					Poco::Path path(app.config().getString("http.root", "/var/www") + url);
					if (Poco::File(path).exists()) {
						Poco::SortedDirectoryIterator it(path), jt;
						Kainjow::Mustache::Data list = Kainjow::Mustache::Data::Type::List;
						while (it != jt) {
							Kainjow::Mustache::Data tmp = Kainjow::Mustache::Data::Type::Object;
							Poco::Path tmpPath(url);
							tmpPath.append(Poco::Path(it->path()).getFileName());
							tmp.set("path", tmpPath.toString());
							tmp.set("isFile", it->isFile() ? Kainjow::Mustache::Data::Type::True : Kainjow::Mustache::Data::Type::False);
							tmp.set("isDirectory", it->isDirectory() ? Kainjow::Mustache::Data::Type::True : Kainjow::Mustache::Data::Type::False);
							tmp.set("lastModify", Poco::DateTimeFormatter::format(Poco::LocalDateTime(Poco::DateTime(it->getLastModified())), Poco::DateTimeFormat::SORTABLE_FORMAT));
							if (it->isFile()) {
								tmp.set("size", Poco::NumberFormatter::format(it->getSize()));

							}
							list.push_back(tmp);
							++it;
						}
						Kainjow::Mustache::Data data = Kainjow::Mustache::Data::Type::Object;
						data.set("list", list);
						data.set("parent", Poco::Path(url).parent().toString());
						Kainjow::Mustache tpl(tplValue);
						response.setChunkedTransferEncoding(true);
						response.setContentType("text/html;charset=UTF-8");
						tpl.render(data, response.send());
					} else {
						response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
						response.redirect("/staticfile/list");
					}
				}

			}

		}

		Poco::Net::HTTPRequestHandler* listFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
		{
			return new webcpp::staticfile::list();
		}


	}
}