#ifndef UPLOADPARTHANDLER_HPP
#define UPLOADPARTHANDLER_HPP

#include <iostream>
#include <string>
#include <memory>
#include <Poco/Net/PartHandler.h>
#include <Poco/StringTokenizer.h>


namespace webcpp {

    class uploadPartHandler : public Poco::Net::PartHandler {
    public:

        struct fileinfo {
            std::string name, filename, type, savepath, message;
            double size;
            bool ok;
        };
    public:
        uploadPartHandler() = delete;
        uploadPartHandler(
                const std::string allowName
                , const std::string allowType = "image/png|image/jpeg|application/zip"
                , const std::string uploadDirectory = "/tmp"
                , double allowMaxSize = 8096);
        uploadPartHandler(const uploadPartHandler& orig) = delete;
        virtual ~uploadPartHandler() = default;
        void handlePart(const Poco::Net::MessageHeader & header, std::istream & stream);
        std::vector<fileinfo> getData();

    private:
        std::vector<fileinfo> data;
        std::string allowName, allowType, directory;
        double allowMaxSize;
    };

}

#endif /* UPLOADPARTHANDLER_HPP */

