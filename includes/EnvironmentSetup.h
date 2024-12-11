#pragma once
#include <string>

class EnvironmentSetup {
private:
    std::string client_id;
    std::string client_secret;
    static std::string youtube_api;
    static std::string access_token;
    bool envSet;
    EnvironmentSetup();
public:
    EnvironmentSetup(const EnvironmentSetup&) = delete;
    EnvironmentSetup& operator=(const EnvironmentSetup&) = delete;
    static EnvironmentSetup& getInstance();
    static const std::string& getYoutubeAPI();
    static const std::string& getAccessToken();
};
