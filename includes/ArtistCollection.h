#pragma once
#include <unordered_map>

#include "Artist.h"

class ArtistCollection {
private:
    static std::unordered_map<std::string, std::shared_ptr<Artist>> artistMap;
public:
    static void addArtist(const std::shared_ptr<Artist>& artist);
    //static bool searchArtist(const std::string& id);
    static std::shared_ptr<Artist> getArtist(const std::string& id);
    friend std::ostream& operator<<(std::ostream& os, const ArtistCollection& artist_collection);
};
