#include "EnvironmentSetup.h"
#include "API.h"
#include "Utility.h"

#include <iostream>

EnvironmentSetup::EnvironmentSetup() : envSet(false) {
    Utils::loadEnvFile();

    const char* client_id_env = getenv("SPOTIFY_CLIENT_ID");
    const char* client_secret_env = getenv("SPOTIFY_CLIENT_SECRET");
    const char* youtube_api_env = getenv("YOUTUBE_DATA_API");

    if(!client_id_env || !client_secret_env || !youtube_api_env) {
        std::cerr << "Error: Spotify or Youtube API keys missing!" << std::endl;
        client_id = "";
        client_secret = "";
        youtube_api = "";
    }
    else {
        client_id = client_id_env;
        client_secret = client_secret_env;
        youtube_api = youtube_api_env;
        envSet = true;
    }

    if(envSet) {
        access_token = API::getSpotifyAccessToken(client_id, client_secret);
        if(!access_token.empty()) {
            std::cout << "Access token retrieved successfully." << std::endl;
        }
        else {
            std::cerr << "Error: Failed to retrieve access token." << std::endl;
        }
    }
    else {
        std::cerr << "Error: Environment variables not set up correctly." << std::endl;
    }
}

const std::string& EnvironmentSetup::getYoutubeAPI() const {return youtube_api;}

const std::string& EnvironmentSetup::getAccessToken() const {return access_token;}
