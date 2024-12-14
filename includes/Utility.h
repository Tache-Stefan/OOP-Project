#pragma once

#include <atomic>
#include <vector>
#include <string>

#include "TextBoxButton.h"
#include "TextBoxTab.h"

namespace Utils {
    std::vector<std::string> split(const std::string& s, const char delimiter);
    struct tm stringToTime(const std::string& length_);
    std::string timeToString(const struct tm& timeStruct);
    struct tm addTimes(struct tm timeStruct1, const struct tm &timeStruct2);
    struct tm durationToTm(const int duration_ms);
    std::string base64_encode(const std::string& input);
    bool downloadAudio(const std::string &youtubeUrl, const std::string &outputFile);
    void monitorInput(std::atomic<bool> &stopPlayback);
    void loadEnvFile();
    TextBoxTab initSearchTab(const sf::Font& font);
    TextBoxTab initPlaylistsTab(const sf::Font& font);
    std::vector<TextBoxButton> initButtons();
    std::vector<TextBoxButton> initVolButtons();
    std::vector<TextBoxTab> initTabs(const sf::Font& font, int& currentTab);
}
