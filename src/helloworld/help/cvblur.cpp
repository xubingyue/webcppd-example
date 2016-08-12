
#include "cvblur.hpp"

namespace webcpp {

	cvblur::cvblur(const std::string& path) : matrix(cv::imread(path)), out(matrix.clone())
	{

	}

	int cvblur::getHeight()
	{
		return this->matrix.rows;
	}

	int cvblur::getWidth()
	{
		return this->matrix.cols;
	}

	bool cvblur::blur(int k)
	{
		if (this->matrix.cols == 0 || this->matrix.rows == 0) {
			return false;
		}

		cv::blur(this->matrix, this->out, cv::Size(k, k));

		return true;
	}

	bool cvblur::gaussion(int k)
	{
		if (this->matrix.cols == 0 || this->matrix.rows == 0) {
			return false;
		}


		cv::GaussianBlur(this->matrix, this->out, cv::Size(k, k), 1.5);

		return true;
	}

	bool cvblur::median(int k)
	{
		if (this->matrix.cols == 0 || this->matrix.rows == 0) {
			return false;
		}


		cv::medianBlur(this->matrix, this->out, k);

		return true;
	}

	bool cvblur::bilateralFilter(int k)
	{
		if (this->matrix.cols == 0 || this->matrix.rows == 0) {
			return false;
		}


		cv::bilateralFilter(this->matrix, this->out, k, k * 2, k / 2);

		return true;
	}

	std::ostream& operator<<(std::ostream& out, const cvblur& x)
	{
		std::vector<uchar> result;
		cv::imencode(".png", x.out, result);
		for (auto & item : result) {
			out << item;
		}
		return out;
	}



}