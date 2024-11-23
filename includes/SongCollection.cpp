#include "SongCollection.h"

#include <iostream>

std::unordered_map<std::string, std::shared_ptr<Song>> SongCollection::songMap;

void SongCollection::addSong(const std::shared_ptr<Song>& song) {
    songMap[song->getID()] = song;
    std::cout << "Added \"" << song->getTitle() << "\" to the song collection. \n";
}

std::shared_ptr<Song> SongCollection::searchSongByID(const std::string& id) {
    const auto it = songMap.find(id);
    if (it == songMap.end()) { return nullptr; }
    return it->second;
}

std::shared_ptr<Song> SongCollection::searchSongByName(const std::string& name) {
    for (const auto& pair : songMap) {
        if (pair.second->getTitle() == name) {
            return pair.second;
        }
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const SongCollection& song_collection) {
    os << "Current Song Collection:\n";
    for (const auto&[id, song] : song_collection.songMap) {
        os << "\t" << song->getTitle() << "\n";
    }
    return os;
}
