#pragma once
#include <string>

class EnvironmentSetup {
private:
    std::string client_id;
    std::string client_secret;
    std::string youtube_api;
    std::string access_token;
    bool envSet;
public:
    EnvironmentSetup();
    const std::string& getClientID() const;
    const std::string& getClientSecret() const;
    const std::string& getYoutubeAPI() const;
    const std::string& getAccessToken() const;
};
