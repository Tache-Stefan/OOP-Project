#include "../headers/Utility.h"

#include <sstream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <array>
#include <nlohmann/json.hpp>

#include "../headers/MusicPlayer.h"
#include "../headers/TextBoxButton.h"

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

    std::vector<std::unique_ptr<TextBox>> initButtons() {
        sf::Font fontButtons;
        if (!fontButtons.loadFromFile("fonts/Coolvetica.otf")) {
            std::cerr << "Failed to load font." << std::endl;
        }

        const std::array<std::string, 5> aux = {"|<", "<", "| |", ">", ">|"};
        std::vector<std::unique_ptr<TextBox>> buttons;
        buttons.reserve(5);

        for (unsigned int i = 0; i < 5; ++i) {
            sf::Color buttonColor = aux[i] == "| |" ? sf::Color::Red : sf::Color::Green;

            auto button = std::make_unique<TextBoxButton>(
                sf::RectangleShape(sf::Vector2f(60, 40)),
                buttonColor,
                fontButtons,
                sf::Text(aux[i], fontButtons, 30),
                sf::Color::White
            );

            button->positionShape(
                sf::Vector2f(1200 * 0.335 + i * 85, 700 * 0.615),
                sf::Vector2f(1200 * 0.335 + 17 + i * 85, 700 * 0.615)
            );

            switch (i) {
                case 0:
                    button->setOnClickCallback([] {
                        MusicPlayer::setSeekToStart(true);
                    });
                break;
                case 1:
                    button->setOnClickCallback([] {
                        MusicPlayer::setSkipBack(true);
                    });
                break;
                case 2:
                    button->setOnClickCallback([] {
                        if (MusicPlayer::getPaused()) {
                            MusicPlayer::setPaused(false);
                        } else {
                            MusicPlayer::setPaused(true);
                        }
                    });
                break;
                case 3:
                    button->setOnClickCallback([] {
                        MusicPlayer::setSkipForward(true);
                    });
                break;
                case 4:
                    button->setOnClickCallback([] {
                        MusicPlayer::setSeekToEnd(true);
                    });
                break;
            }

            buttons.emplace_back(std::move(button));
        }

        return buttons;
    }

    std::vector<std::unique_ptr<TextBox>> initVolButtons() {
        sf::Font fontButtons;
        if (!fontButtons.loadFromFile("fonts/Coolvetica.otf")) {
            std::cerr << "Failed to load font." << std::endl;
        }

        const std::array<std::string, 2> aux = {"VOL-", "VOL+"};
        std::vector<std::unique_ptr<TextBox>> volButtons;
        volButtons.reserve(2);

        auto volMinusButton = std::make_unique<TextBoxButton>(
        sf::RectangleShape(sf::Vector2f(80, 40)),
        sf::Color::Red,
        fontButtons,
        sf::Text(aux[0], fontButtons, 28),
        sf::Color::White
        );
        volMinusButton->positionShape(
        sf::Vector2f(1200 - 160, 700 - 40),
        sf::Vector2f(1200 + 10 - 160, 700 - 40)
        );
        volMinusButton->setOnClickCallback([] {
        MusicPlayer::decreaseVolume();
        });
        volButtons.emplace_back(std::move(volMinusButton));

        auto volPlusButton = std::make_unique<TextBoxButton>(
        sf::RectangleShape(sf::Vector2f(80, 40)),
        sf::Color::Green,
        fontButtons,
        sf::Text(aux[1], fontButtons, 28),
        sf::Color::White
        );
        volPlusButton->positionShape(
            sf::Vector2f(1200 - 80, 700 - 40),
            sf::Vector2f(1200 + 10 - 80, 700 - 40)
        );
        volPlusButton->setOnClickCallback([] {
            MusicPlayer::increaseVolume();
        });
        volButtons.emplace_back(std::move(volPlusButton));

        return volButtons;
    }

    std::vector<std::unique_ptr<TextBox>> initTabs(const sf::Font& font, int& currentTab) {
        std::vector<std::unique_ptr<TextBox>> tabs;
        tabs.reserve(2);

        sf::RectangleShape searchBox(sf::Vector2f(200, 50));
        searchBox.setPosition(0, 0);
        sf::Text searchText("Music player", font, 20);
        searchText.setPosition(20, 12);

        auto musicPlayerTab = std::make_unique<TextBoxTab>(searchBox, sf::Color::Green, font, searchText, sf::Color::Black);
        musicPlayerTab->setOnClickCallback([&currentTab] {
            currentTab = 1;
        });
        tabs.emplace_back(std::move(musicPlayerTab));

        sf::RectangleShape playlistsBox(sf::Vector2f(200, 50));
        playlistsBox.setPosition(200, 0);
        sf::Text playlistsText("Playlists", font, 20);
        playlistsText.setPosition(250, 12);

        auto playlistsTab = std::make_unique<TextBoxTab>(playlistsBox, sf::Color::Green, font, playlistsText, sf::Color::Black);
        playlistsTab->setOnClickCallback([&currentTab] {
            currentTab = 2;
        });
        tabs.emplace_back(std::move(playlistsTab));

        return tabs;
    }
}
