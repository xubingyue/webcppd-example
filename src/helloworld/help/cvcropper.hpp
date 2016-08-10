#ifndef CVCROPPER_HPP
#define CVCROPPER_HPP


#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>


namespace webcpp {

    class cvcropper {
    public:
        cvcropper(const std::string& srcPath);
        cvcropper() = delete;
        cvcropper(const cvcropper& orig) = delete;
        int getWidth();
        int getHeight();
        bool create(int x, int y, int width, int height);
        virtual ~cvcropper();
        friend std::ostream & operator<<(std::ostream& out, const cvcropper& x);

    private:
        cv::Mat matrix,*subMatrix;
    };

}
#endif /* CVCROPPER_HPP */

