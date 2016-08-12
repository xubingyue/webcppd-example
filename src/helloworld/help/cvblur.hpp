#ifndef CVBLUR_HPP
#define CVBLUR_HPP


#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

namespace webcpp {

    class cvblur {
    public:
        cvblur(const std::string& path);
        cvblur() = delete;
        cvblur(const cvblur& orig) = delete;
        virtual ~cvblur() = default;
        int getWidth();
        int getHeight();
        bool blur(int k = 11);
        bool gaussion(int k = 11);
        bool median(int k = 11);
        bool bilateralFilter(int k = 11);
        friend std::ostream & operator<<(std::ostream& out, const cvblur& x);


    private:
        cv::Mat matrix, out;
    };

}

#endif /* CVBLUR_HPP */

