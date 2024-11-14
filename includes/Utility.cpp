#include "Utility.h"
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace Utils {
    std::vector<std::string> split(const std::string& s, const char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    struct tm stringToTime(const std::string& length_) {
        struct tm timeStruct = {};
        timeStruct.tm_mday = 1;

        if (const std::vector<std::string> timeParts = split(length_, ':'); timeParts.size() == 3) {
            timeStruct.tm_hour = std::stoi(timeParts[0]);
            timeStruct.tm_min = std::stoi(timeParts[1]);
            timeStruct.tm_sec = std::stoi(timeParts[2]);
        } else {
            std::cerr << "Invalid time: " << length_ << std::endl;
        }

        return timeStruct;
    }

    std::string timeToString(const struct tm& timeStruct) {
        std::ostringstream oss;
        oss << (timeStruct.tm_hour < 10 ? "0" : "") << timeStruct.tm_hour << ":"
            << (timeStruct.tm_min < 10 ? "0" : "") << timeStruct.tm_min << ":"
            << (timeStruct.tm_sec < 10 ? "0" : "") << timeStruct.tm_sec;

        return oss.str();
    }

    struct tm addTimes(struct tm timeStruct1, const struct tm &timeStruct2) {
        timeStruct1.tm_sec += timeStruct2.tm_sec;
        timeStruct1.tm_min += timeStruct2.tm_min;
        timeStruct1.tm_hour += timeStruct2.tm_hour;

        if (timeStruct1.tm_sec >= 60) {
            timeStruct1.tm_sec -= 60;
            timeStruct1.tm_min += 1;
        }
        if (timeStruct1.tm_min >= 60) {
            timeStruct1.tm_min -= 60;
            timeStruct1.tm_hour += 1;
        }

        return timeStruct1;
    }

    std::string base64_encode(const std::string& input) {
        const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        std::string encoded;
        int val = 0, valb = -6;
        for (const unsigned char c : input) {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0) {
                encoded.push_back(base64_chars[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6) {
            encoded.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
        }
        while (encoded.size() % 4) {
            encoded.push_back('=');
        }
        return encoded;
    }
}
