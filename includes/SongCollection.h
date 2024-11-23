#pragma once
#include <unordered_map>

#include "Song.h"

class SongCollection {
private:
    static std::unordered_map<std::string, std::shared_ptr<Song>> songMap;
public:
    static void addSong(const std::shared_ptr<Song>& song);
    static std::shared_ptr<Song> searchSongByID(const std::string& id);
    static std::shared_ptr<Song> searchSongByName(const std::string& name);
    friend std::ostream& operator<<(std::ostream& os, const SongCollection& song_collection);
};
