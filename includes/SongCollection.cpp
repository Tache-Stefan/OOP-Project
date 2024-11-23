#include "SongCollection.h"

#include <iostream>

std::unordered_map<std::string, std::shared_ptr<Song>> SongCollection::songMap;

void SongCollection::addSong(const std::shared_ptr<Song>& song) {
    songMap[song->getID()] = song;
    std::cout << "Added \"" << song->getTitle() << "\" to the song collection. \n";
}

bool SongCollection::searchSong(const std::string& id) {
    const auto it = songMap.find(id);
    if (it == songMap.end()) { return false; }
    return true;
}

std::ostream& operator<<(std::ostream& os, const SongCollection& song_collection) {
    os << "Current Song Collection:\n";
    for (const auto&[id, song] : song_collection.songMap) {
        os << "\t" << song->getTitle() << "\n";
    }
    return os;
}
