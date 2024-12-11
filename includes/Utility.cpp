#include "Utility.h"

#include <sstream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <array>
#include <nlohmann/json.hpp>

#include "MusicPlayer.h"
#include "TextBoxButton.h"

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

    struct tm durationToTm(const int duration_ms) {
        struct tm time_struct = {};

        int total_seconds = duration_ms / 1000;

        time_struct.tm_hour = total_seconds / 3600;
        total_seconds %= 3600;

        time_struct.tm_min = total_seconds / 60;
        time_struct.tm_sec = total_seconds % 60;

        return time_struct;
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

    bool downloadAudio(const std::string &youtubeUrl, const std::string &outputFile) {
        if (std::filesystem::exists(outputFile))
            std::filesystem::remove(outputFile);

        const std::string command = "yt-dlp -f bestaudio --extract-audio --audio-format mp3 -o " + outputFile + " " + youtubeUrl;

        std::cout << "Downloading audio from YouTube..." << std::endl;
        const int result = std::system(command.c_str());
        if (result != 0) {
            std::cerr << "Error: Failed to download audio!" << std::endl;
            return false;
        }

        std::cout << "Audio downloaded to: " << outputFile << std::endl;
        return true;
    }

    void loadEnvFile() {
        const std::string filename = "envconfig.txt";
        std::ifstream env_file(filename);
        if (!env_file.is_open()) {
            std::cerr << "Error: Unable to open envconfig.txt" << std::endl;
            return;
        }

        std::string line;
        while (std::getline(env_file, line)) {
            if (line.empty()) continue;

            const size_t separator_pos = line.find('=');
            if (separator_pos == std::string::npos) continue;

            std::string key = line.substr(0, separator_pos);
            std::string value = line.substr(separator_pos + 1);

#ifdef _WIN32
            _putenv((key + "=" + value).c_str());
#else
            setenv(key.c_str(), value.c_str(), 1);
#endif
        }
        env_file.close();
    }

    TextBoxTab initSearchTab(const sf::Font& font) {
        sf::RectangleShape searchBox(sf::Vector2f(200, 50));
        searchBox.setPosition(0, 0);
        sf::Text searchText("Search music", font, 20);
        searchText.setPosition(20, 12);
        return {searchBox, sf::Color::Green, font, searchText, sf::Color::Black};
    }

    TextBoxTab initPlaylistsTab(const sf::Font& font) {
        sf::RectangleShape playlistsBox(sf::Vector2f(200, 50));
        playlistsBox.setPosition(200, 0);
        sf::Text playlistsText("Playlists", font, 20);
        playlistsText.setPosition(250, 12);
        return {playlistsBox, sf::Color::Green, font, playlistsText, sf::Color::Black};
    }

    std::vector<TextBoxButton> initButtons() {
        sf::Font fontButtons;
        if (!fontButtons.loadFromFile("fonts/Coolvetica.otf")) {
            std::cerr << "Failed to load font." << std::endl;
        }

        const std::array<std::string, 5> aux = {"|<", "<", "| |", ">", ">|"};
        std::vector<TextBoxButton> buttons;
        buttons.reserve(5);
        for (unsigned int i = 0; i < 5; ++i) {
            if (aux[i] == "| |") {
                buttons.emplace_back(sf::RectangleShape(sf::Vector2f(60, 40)), sf::Color::Red, fontButtons,
                                     sf::Text(aux[i], fontButtons, 30), sf::Color::White);
            }
            else {
                buttons.emplace_back(sf::RectangleShape(sf::Vector2f(60, 40)), sf::Color::Green, fontButtons,
                                     sf::Text(aux[i], fontButtons, 30), sf::Color::White);
            }
            buttons[i].positionShape(
                sf::Vector2f(1200 * 0.335 + i * 85, 700 * 0.615),
                sf::Vector2f(1200 * 0.335 + 17 + i * 85, 700 * 0.615));
        }
        buttons[0].setOnClickCallback([] {
            MusicPlayer::setSeekToStart(true);
        });
        buttons[1].setOnClickCallback([] {
            MusicPlayer::setSkipBack(true);
        });
        buttons[2].setOnClickCallback([] {
            MusicPlayer::setStopPlayback(true);
        });
        buttons[3].setOnClickCallback([] {
            MusicPlayer::setSkipForward(true);
        });
        buttons[4].setOnClickCallback([] {
            MusicPlayer::setSeekToEnd(true);
        });

        return buttons;
    }

    std::vector<TextBoxTab> initTabs(const sf::Font& font, int& currentTab) {
        std::vector<TextBoxTab> tabs;
        tabs.reserve(2);

        sf::RectangleShape searchBox(sf::Vector2f(200, 50));
        searchBox.setPosition(0, 0);
        sf::Text searchText("Search music", font, 20);
        searchText.setPosition(20, 12);
        tabs.emplace_back(searchBox, sf::Color::Green, font, searchText, sf::Color::Black);
        tabs[0].setOnClickCallback([&currentTab] {
            currentTab = 1;
        });

        sf::RectangleShape playlistsBox(sf::Vector2f(200, 50));
        playlistsBox.setPosition(200, 0);
        sf::Text playlistsText("Playlists", font, 20);
        playlistsText.setPosition(250, 12);
        tabs.emplace_back(playlistsBox, sf::Color::Green, font, playlistsText, sf::Color::Black);
        tabs[1].setOnClickCallback([&currentTab] {
            currentTab = 2;
        });

        return tabs;
    }
}
