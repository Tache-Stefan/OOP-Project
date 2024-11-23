#include "ArtistCollection.h"

#include <iostream>

std::unordered_map<std::string, std::shared_ptr<Artist>> ArtistCollection::artistMap;

void ArtistCollection::addArtist(const std::shared_ptr<Artist>& artist) {
    artistMap[artist->getID()] = artist;
    std::cout << "Added \"" << artist->getName() << "\" to the artist collection. \n";
}

/*bool ArtistCollection::searchArtist(const std::string& id) {
    const auto it = artistMap.find(id);
    if (it == artistMap.end()) { return false; }
    return true;
}*/

std::shared_ptr<Artist> ArtistCollection::getArtist(const std::string& id) {
    const auto it = artistMap.find(id);
    if (it != artistMap.end()) {return it->second;}
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const ArtistCollection& artist_collection) {
    os << "Current Artist Collection:\n";
    for (const auto&[id, artist] : artist_collection.artistMap) {
        os << "\t" << artist->getName() << "\n";
    }
    return os;
}
