#pragma once

#include <vector>
#include <string>
#include <ctime>

namespace Utils {
    std::vector<std::string> split(const std::string& s, const char delimiter);
    struct tm stringToTime(const std::string& length_);
    std::string timeToString(const struct tm& timeStruct);
    struct tm addTimes(struct tm timeStruct1, const struct tm &timeStruct2);
}
