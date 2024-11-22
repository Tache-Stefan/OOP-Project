#pragma once
#include <string>
#include <unordered_map>

#include "Song.h"

class SongCollection {
private:
    std::unordered_map<std::string, std::shared_ptr<Song>> songMap;
public:
    void addSong(const std::shared_ptr<Song>& song);
    bool searchSong(const std::string& id);
    friend std::ostream& operator<<(std::ostream& os, const SongCollection& song_collection);
};
