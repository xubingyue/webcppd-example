

#include "cvrotate.hpp"


namespace webcpp {

	cvrotate::cvrotate(const std::string& path, int degrees)
	: matrix(cv::imread(path)), otherMatrix()
	{
		this->rotate(degrees);
	}

	void cvrotate::rotate(int degrees)
	{
		switch (degrees % 360) {
		case 0:
			this->otherMatrix = this->matrix;
			break;
		case 90:
			cv::flip(this->matrix.t(), this->otherMatrix, 1);
			break;
		case 180:
			cv::flip(this->matrix, this->otherMatrix, -1);
			break;
		case 270:
			cv::flip(this->matrix.t(), this->otherMatrix, 0);
			break;
		default:
			cv::Mat r = cv::getRotationMatrix2D({this->matrix.cols / 2.0F, this->matrix.rows / 2.0F}, degrees, 1.0);
			int len = std::max(this->matrix.cols, this->matrix.rows);
			cv::warpAffine(this->matrix, this->otherMatrix, r, cv::Size(len, len));
			break; //image size will change
		}

	}

	bool cvrotate::isReady()
	{
		return this->matrix.cols > 0 && this->matrix.rows > 0;
	}

	std::ostream& operator<<(std::ostream& out, const cvrotate & x)
	{
		std::vector<uchar> result;
		cv::imencode(".png", x.otherMatrix, result);
		for (auto& item : result) {
			out << item;
		}
		return out;
	}

}