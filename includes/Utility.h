#pragma once

#include <atomic>
#include <vector>
#include <string>
#include <ctime>

namespace Utils {
    std::vector<std::string> split(const std::string& s, const char delimiter);
    struct tm stringToTime(const std::string& length_);
    std::string timeToString(const struct tm& timeStruct);
    struct tm addTimes(struct tm timeStruct1, const struct tm &timeStruct2);
    std::string base64_encode(const std::string& input);
    bool downloadAudio(const std::string &youtubeUrl, const std::string &outputFile);
    void monitorInput(std::atomic<bool> &stopPlayback);
    void playAudio(const std::string &filePath, std::atomic<bool> &stopPlayback);
    void loadEnvFile();
}
