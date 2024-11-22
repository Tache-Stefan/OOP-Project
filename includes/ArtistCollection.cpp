#include "ArtistCollection.h"

#include <iostream>

std::unordered_map<std::string, std::shared_ptr<Artist>> ArtistCollection::artistMap;

void ArtistCollection::addArtist(const std::shared_ptr<Artist>& artist) {
    artistMap[artist->getName()] = artist;
    std::cout << "Added \"" << artist->getName() << "\" to the collection. \n";
}

bool ArtistCollection::searchArtist(const std::string& name) {
    const auto it = artistMap.find(name);
    if (it == artistMap.end()) { return false; }
    return true;
}

std::ostream& operator<<(std::ostream& os, const ArtistCollection& artist_collection) {
    os << "Current Artist Collection:\n";
    for (const auto&[name, artist] : artist_collection.artistMap) {
        os << "\t" << artist->getName() << "\n";
    }
    return os;
}
