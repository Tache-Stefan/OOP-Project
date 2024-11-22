#pragma once

#include <string>

#include "Song.h"

namespace API {
    std::string getSpotifyAccessToken(const std::string& client_id, const std::string& client_secret);
    Song searchSpotify(const std::string& access_token, const std::string& query, const std::string& type);
    std::string searchYouTube(const std::string& youtube_api, const std::string& query);
}
