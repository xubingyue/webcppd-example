#include <Poco/RegularExpression.h>

#include "validation.hpp"

namespace webcpp {

	std::string validation::INTEGER = "^-?[1-9]\\d*$"
		, validation::POSITIVE_INTEGER = "^[1-9]\\d*$"
		, validation::NEGATIVE_INTEGER = "^-[1-9]\\d*$"
		, validation::NUMBER = "^([+-]?)\\d*\\.?\\d+$"
		, validation::POSITIVE_NUMBER = "^[1-9]\\d*|0$"
		, validation::NEGATINE_NUMBER = "^-[1-9]\\d*|0$"
		, validation::FLOAT = "^([+-]?)\\d*\\.\\d+$"
		, validation::POSTTIVE_FLOAT = "^[1-9]\\d*.\\d*|0.\\d*[1-9]\\d*$"
		, validation::NEGATIVE_FLOAT = "^-([1-9]\\d*.\\d*|0.\\d*[1-9]\\d*)$"
		, validation::UNPOSITIVE_FLOAT = "^[1-9]\\d*.\\d*|0.\\d*[1-9]\\d*|0?.0+|0$"
		, validation::UNNEGATIVE_FLOAT = "^(-([1-9]\\d*.\\d*|0.\\d*[1-9]\\d*))|0?.0+|0$"
		, validation::EMAIL = "^\\w+((-\\w+)|(\\.\\w+))*\\@[A-Za-z0-9]+((\\.|-)[A-Za-z0-9]+)*\\.[A-Za-z0-9]+$"
		, validation::COLOR = "^[a-fA-F0-9]{6}$"
		, validation::URL = "^http[s]?:\\/\\/([\\w-]+\\.)+[\\w-]+([\\w-./?%&=]*)?$"
		, validation::CHINESE = "^[\u4E00-\u9FA5\uF900-\uFA2D]+$"
		, validation::ASCII = "^[\\x00-\\xFF]+$"
		, validation::ZIPCODE = "^\\d{6}$"
		, validation::MOBILE = "^(13|15)[0-9]{9}$"
		, validation::IP4 = "^(25[0-5]|2[0-4]\\d|[0-1]\\d{2}|[1-9]?\\d)\\.(25[0-5]|2[0-4]\\d|[0-1]\\d{2}|[1-9]?\\d)\\.(25[0-5]|2[0-4]\\d|[0-1]\\d{2}|[1-9]?\\d)\\.(25[0-5]|2[0-4]\\d|[0-1]\\d{2}|[1-9]?\\d)$"
		, validation::NOTEMPTY = "^\\S+$"
		, validation::PICTURE = "(.*)\\.(jpg|bmp|gif|ico|pcx|jpeg|tif|png|raw|tga)$"
		, validation::RAR = "(.*)\\.(rar|zip|7zip|tgz)$"
		, validation::DATE = "^((((1[6-9]|[2-9]\\d)\\d{2})-(0?[13578]|1[02])-(0?[1-9]|[12]\\d|3[01]))|(((1[6-9]|[2-9]\\d)\\d{2})-(0?[13456789]|1[012])-(0?[1-9]|[12]\\d|30))|(((1[6-9]|[2-9]\\d)\\d{2})-0?2-(0?[1-9]|1\\d|2[0-8]))|(((1[6-9]|[2-9]\\d)(0[48]|[2468][048]|[13579][26])|((16|[2468][048]|[3579][26])00))-0?2-29-)) (20|21|22|23|[0-1]?\\d):[0-5]?\\d:[0-5]?\\d$"
		, validation::QQ = "^[1-9]*[1-9][0-9]*$"
		, validation::TEL = "^(([0\\+]\\d{2,3}-)?(0\\d{2,3})-)?(\\d{7,8})(-(\\d{3,}))?$"
		, validation::LETTER = "^[A-Za-z]+$"
		, validation::LETTER_U = "^[A-Z]+$"
		, validation::LETTER_L = "^[a-z]+$"
		, validation::IDCARD = "^(\\d{15}$|^\\d{18}$|^\\d{17}(\\d|X|x))$";

	bool validation::match(const std::string str, const std::string pattern)
	{
		Poco::RegularExpression reg(pattern);
		return reg.match(str);
	}

}
