#pragma once
#include <string>
#include <unordered_map>

#include "Song.h"

class SongCollection {
private:
    static std::unordered_map<std::string, std::shared_ptr<Song>> songMap;
public:
    static void addSong(const std::shared_ptr<Song>& song);
    static bool searchSong(const std::string& id);
    friend std::ostream& operator<<(std::ostream& os, const SongCollection& song_collection);
};
