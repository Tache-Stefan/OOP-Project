#pragma once

#include "Song.h"
#include "Artist.h"

namespace API {
    std::string getSpotifyAccessToken(const std::string& client_id, const std::string& client_secret);
    std::shared_ptr<Song> searchSpotifySong(const std::string& query);
    std::shared_ptr<Artist> searchSpotifyArtist(const std::string& query);
    std::string searchYouTube(const std::string& query);
}
