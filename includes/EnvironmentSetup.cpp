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
}

bool EnvironmentSetup::isEnvSet() const {return envSet;}

const std::string& EnvironmentSetup::getClientID() const {return client_id;}

const std::string& EnvironmentSetup::getClientSecret() const {return client_secret;}

const std::string& EnvironmentSetup::getYoutubeAPI() const {return youtube_api;}

std::string EnvironmentSetup::retrieveSpotifyAccessToken() const {
    if(!envSet) {
        std::cerr << "Error: Environment variables not set up correctly." << std::endl;
        return "";
    }
    return API::getSpotifyAccessToken(client_id, client_secret);
}
