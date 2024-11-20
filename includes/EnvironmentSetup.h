#pragma once
#include <string>

class EnvironmentSetup {
private:
    std::string client_id;
    std::string client_secret;
    std::string youtube_api;
    bool envSet;
public:
    EnvironmentSetup();
    bool isEnvSet() const;
    const std::string& getClientID() const;
    const std::string& getClientSecret() const;
    const std::string& getYoutubeAPI() const;
    std::string retrieveSpotifyAccessToken() const;
};
