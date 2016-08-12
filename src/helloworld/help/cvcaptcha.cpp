#include <Poco/String.h>
#include <vector>
#include "cvcaptcha.hpp"

namespace webcpp {
	const std::string cvCaptcha::allChar = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const std::array<int, 9> cvCaptcha::fontFace = {0, 1, 2, 3, 4, 5, 6, 7, 16};

	cvCaptcha::cvCaptcha(bool lined, bool ellipsed, bool slated) :
	n(6), lineNumber(10), ellipseNumber(10), slateNumber(300),
	content(), rng(), matrix(80, 200, CV_8UC3, cv::Scalar::all(255)),
	lined(lined), ellipsed(ellipsed), slated(slated)
	{

	}

	std::string cvCaptcha::getRandomChar(int n)
	{
		std::string result;
		unsigned int p = 0;
		std::string::size_type size = cvCaptcha::allChar.size();
		for (int i = 0; i < n; ++i) {
			p = this->rng.next(size);
			result.push_back(cvCaptcha::allChar[p]);
		}

		return result;
	}

	int cvCaptcha::getRandomFontFace()
	{
		return cvCaptcha::fontFace[this->rng.next(cvCaptcha::fontFace.size())];
	}

	int cvCaptcha::getSize()
	{
		return this->n;
	}

	std::string cvCaptcha::getContent()
	{
		return this->content;
	}

	void cvCaptcha::addEllipse()
	{
		this->ellipsed = true;
	}

	void cvCaptcha::addLine()
	{
		this->lined = true;
	}

	void cvCaptcha::addSlate()
	{
		this->slated = true;
	}

	void cvCaptcha::setlineNumber(int n)
	{
		this->lineNumber = n;
	}

	void cvCaptcha::setEllipseNumber(int n)
	{
		this->ellipseNumber = n;
	}

	void cvCaptcha::setSlateNumber(int n)
	{
		this->slateNumber = n;
	}

	void cvCaptcha::create()
	{
		this->content.clear();
		int p = 0;
		for (int i = 0; i<this->n; ++i) {
			int fontFace = this->getRandomFontFace();
			double fontScale = 1.0;
			int thickness = 2;
			std::string text = this->getRandomChar(1);
			this->content.append(Poco::toLower(text));
			int baseline = 0;
			cv::Size textSize = cv::getTextSize(text, fontFace,
				fontScale, thickness, &baseline);

			p += (i == 0 ? textSize.width / 2 : textSize.width + 12);
			cv::Point textOrg(p, (this->matrix.rows + textSize.height) / 2 + (this->rng.nextBool() ? -5 : 5));


			cv::putText(this->matrix, text, textOrg, fontFace, fontScale,
				this->RandomColor(), thickness, CV_AA);
		}

		if (this->lined)
			this->drawRandomLine(this->lineNumber);
		if (this->ellipsed)
			this->drawRandomEllipse(this->ellipseNumber);
		if (this->slated)
			this->drawRandomSlate(this->slateNumber);


	}

	void cvCaptcha::writeToFile(const std::string& filepath)
	{
		cv::imwrite(filepath, this->matrix);
	}

	void cvCaptcha::drawRandomLine(int n)
	{
		cv::Point pt1, pt2;

		for (int i = 0; i < n; i++) {
			pt1.x = this->rng.next(this->matrix.cols);
			pt1.y = this->rng.next(this->matrix.rows);
			pt2.x = this->rng.next(this->matrix.cols);
			pt2.y = this->rng.next(this->matrix.rows);

			cv::line(this->matrix, pt1, pt2, this->RandomColor(), this->uniform(1, 2), 1);
		}

	}

	void cvCaptcha::drawRandomEllipse(int n)
	{
		for (int i = 0; i < n; ++i) {
			cv::ellipse(this->matrix,
				cv::Point(this->rng.next(this->matrix.cols), this->rng.next(this->matrix.cols)),
				cv::Size(this->rng.next(this->matrix.rows), this->rng.next(this->matrix.rows)),
				this->uniform(0, 360),
				0,
				360,
				this->RandomColor(),
				1,
				2);
		}
	}

	void cvCaptcha::drawRandomSlate(int n)
	{
		int i, j;
		for (int k = 0; k < n; ++k) {
			i = this->rng.next(this->matrix.cols);
			j = this->rng.next(this->matrix.rows);

			if (this->matrix.channels() == 1) {
				this->matrix.at<uchar>(j, i) = this->rng.next(255);
			} else {
				this->matrix.at<cv::Vec3b>(j, i)[0] = this->rng.next(255);
				this->matrix.at<cv::Vec3b>(j, i)[1] = this->rng.next(255);
				this->matrix.at<cv::Vec3b>(j, i)[2] = this->rng.next(255);
			}
		}
	}

	cv::Scalar cvCaptcha::RandomColor()
	{
		return cv::Scalar(this->rng.next(255), this->rng.next(255), this->rng.next(255));
	}

	template<typename T>
	T cvCaptcha::uniform(T a, T b)
	{
		return a == b ? a : (T) (this->rng.next(b - a) + a);
	}

	int cvCaptcha::getWidth()
	{
		return this->matrix.cols;
	}

	int cvCaptcha::getHeight()
	{
		return this->matrix.rows;
	}

	std::ostream& operator<<(std::ostream& out, const cvCaptcha & x)
	{
		std::vector<uchar> result;
		cv::imencode(".png", x.matrix, result);
		for (auto& item : result) {
			out << item;
		}
		return out;
	}



}

