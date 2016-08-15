#ifndef VALIDATION_HPP
#define VALIDATION_HPP

#include <string>


namespace webcpp {

    class validation {
    public:
        validation() = delete;
        validation(const validation& orig) = delete;
        virtual ~validation() = default;

    public:
        static bool match(const std::string str, const std::string pattern);
        static std::string INTEGER
        , POSITIVE_INTEGER
        , NEGATIVE_INTEGER
        , NUMBER
        , POSITIVE_NUMBER
        , NEGATINE_NUMBER
        , FLOAT
        , POSTTIVE_FLOAT
        , NEGATIVE_FLOAT
        , UNPOSITIVE_FLOAT
        , UNNEGATIVE_FLOAT
        , EMAIL
        , COLOR
        , URL
        , CHINESE
        , ASCII
        , ZIPCODE
        , MOBILE
        , IP4
        , NOTEMPTY
        , PICTURE
        , RAR
        , DATE
        , QQ
        , TEL
        , LETTER
        , LETTER_U
        , LETTER_L
        , IDCARD;



    };

}

#endif /* VALIDATION_HPP */

