#include <vector>
#include <algorithm>
#include "cvcropper.hpp"


namespace webcpp {

	cvcropper::cvcropper(const std::string& srcPath)
	: matrix(cv::imread(srcPath))
	, subMatrix(0)
	{

	}

	cvcropper::~cvcropper()
	{
		if (subMatrix) {
			delete subMatrix;
		}
	}

	int cvcropper::getHeight()
	{
		return this->matrix.rows;
	}

	int cvcropper::getWidth()
	{
		return this->matrix.cols;
	}

	bool cvcropper::create(int x, int y, int width, int height)
	{
		if (width <= this->getWidth() && height <= this->getHeight()) {
			this->subMatrix = new cv::Mat(this->matrix, cv::Rect(x, y, width, height));
			return true;
		}

		this->subMatrix = new cv::Mat(this->getHeight(), this->getWidth(), CV_8UC3, cv::Scalar::all(0));
		this->matrix.copyTo(*this->subMatrix);
		return false;
	}

	std::ostream& operator<<(std::ostream& out, const cvcropper& x)
	{
		std::vector<uchar> result;
		cv::imencode(".png", *x.subMatrix, result);
		for (auto & item : result) {
			out << item;
		}
		return out;
	}


}