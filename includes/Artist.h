#pragma once

#include <memory>
#include <string>
#include <vector>

class Song;

class Artist {
private:
    std::string name;
    std::vector<std::shared_ptr<Song>> songs;
public:
    Artist(const std::string& name_, const std::vector<std::shared_ptr<Song>>& songs_);
    explicit Artist(const std::string& name);
    friend std::ostream& operator<<(std::ostream& os, const Artist& artist);
    void addSong(const std::shared_ptr<Song>& song);
};