#ifndef CVCAPTCHA_HPP
#define CVCAPTCHA_HPP

#include <string>
#include <ostream>
#include <array>
#include <Poco/Random.h>
#include <opencv2/opencv.hpp>


namespace webcpp {

    class cvCaptcha {
    public:
        cvCaptcha(bool lined = false, bool ellipsed = false, bool slated = false);
        cvCaptcha(const cvCaptcha& orig) = delete;
        virtual ~cvCaptcha() = default;

    public:
        int getSize();
        std::string getContent();
        void create();
        void addLine();
        void addEllipse();
        void addSlate();
        void setlineNumber(int n);
        void setEllipseNumber(int n);
        void setSlateNumber(int n);
        void writeToFile(const std::string& filepath);
        int getWidth();
        int getHeight();
        friend std::ostream& operator<<(std::ostream& out, const cvCaptcha& x);

    private:
        int n, lineNumber, ellipseNumber, slateNumber;
        std::string content;
        Poco::Random rng;
        cv::Mat matrix;
        bool lined, ellipsed, slated;
        static const std::string allChar;
        static const std::array<int, 9> fontFace;
    private:
        std::string getRandomChar(int n = 1);
        int getRandomFontFace();
        void drawRandomLine(int n = 8);
        void drawRandomEllipse(int n = 8);
        void drawRandomSlate(int n = 300);
        cv::Scalar RandomColor();
        template<typename T>
        T uniform(T a, T b);
    };

}

#endif /* CVCAPTCHA_HPP */

