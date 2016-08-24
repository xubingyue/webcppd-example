#ifndef CVQRCODE_HPP
#define CVQRCODE_HPP

#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

namespace webcpp {

    class cvqrcode {
    public:
        cvqrcode(const std::string& text, int width=180,int version = 2);
        cvqrcode() = delete;
        cvqrcode(const cvqrcode& orig) = delete;
        virtual ~cvqrcode() = default;
        bool created();
        friend std::ostream & operator<<(std::ostream& out, const cvqrcode& x);
    private:
        int version, width,height;
        cv::Mat image;
        bool successful;
    };
}

#endif /* CVQRCODE_HPP */

