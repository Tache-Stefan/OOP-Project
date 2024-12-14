#include "ArtistCollection.h"

#include <iostream>

std::unordered_map<std::string, std::shared_ptr<Artist>> ArtistCollection::artistMap;

// cppcheck-suppress unusedFunction ; false positive
void ArtistCollection::addArtist(const std::shared_ptr<Artist>& artist) {
    artistMap[artist->getID()] = artist;
    std::cout << "Added \"" << artist->getName() << "\" to the artist collection. \n";
}

// cppcheck-suppress unusedFunction ; false positive
std::shared_ptr<Artist> ArtistCollection::getArtist(const std::string& id) {
    const auto it = artistMap.find(id);
    if (it != artistMap.end()) {return it->second;}
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const ArtistCollection&) {
    os << "Current Artist Collection:\n";
    for (const auto&[id, artist] : ArtistCollection::artistMap) {
        os << "\t" << artist->getName() << "\n";
    }
    return os;
}
