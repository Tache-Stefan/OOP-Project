#include "../headers/EnvironmentSetup.h"
#include "../headers/API.h"
#include "../headers/Utility.h"
#include "../headers/Exceptions.h"

#include <iostream>

std::string EnvironmentSetup::youtube_api;
std::string EnvironmentSetup::access_token;

EnvironmentSetup::EnvironmentSetup() : envSet(false) {
    const char* githubActions = std::getenv("GITHUB_ACTIONS");
    if (githubActions == nullptr) {
        Utils::loadEnvFile();
    }

    const char* client_id_env = getenv("SPOTIFY_CLIENT_ID");
    const char* client_secret_env = getenv("SPOTIFY_CLIENT_SECRET");
    const char* youtube_api_env = getenv("YOUTUBE_DATA_API");

    if(!client_id_env || !client_secret_env || !youtube_api_env) {
        throw EnvironmentException("Spotify or Youtube API keys missing!");
    }
    client_id = client_id_env;
    client_secret = client_secret_env;
    youtube_api = youtube_api_env;

    access_token = API::getSpotifyAccessToken(client_id, client_secret);
    if(!access_token.empty()) {
        std::cout << "Access token retrieved successfully." << std::endl;
    }
    else {
        throw EnvironmentException("Failed to retrieve access token!");
    }
}

EnvironmentSetup& EnvironmentSetup::getInstance() {
    static EnvironmentSetup setup;
    return setup;
}

const std::string& EnvironmentSetup::getYoutubeAPI() {return youtube_api;}

const std::string& EnvironmentSetup::getAccessToken() {return access_token;}
