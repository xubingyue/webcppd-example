#ifndef CVROTATE_HPP
#define CVROTATE_HPP


#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include "cvrotate.hpp"

namespace webcpp {

    class cvrotate {
    public:
        cvrotate() = delete;
        cvrotate(const std::string& path, int degrees);
        cvrotate(const cvrotate& orig) = delete;
        virtual ~cvrotate() = default;
        bool isReady();
        friend std::ostream & operator<<(std::ostream& out, const cvrotate& x);
    private:
        cv::Mat matrix, otherMatrix;
        void rotate(int degrees);
    };

}

#endif /* CVROTATE_HPP */

