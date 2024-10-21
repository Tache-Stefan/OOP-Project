#pragma once

#include <iostream>
#include <string>
#include <vector>

class Song;

class Artist {
private:
    std::string name;
    std::vector<Song> songs;
public:
    Artist(const std::string& name_, const std::vector<Song> &songs_);
    explicit Artist(const std::string& name);
    friend std::ostream& operator<<(std::ostream& os, const Artist& artist);
    void addSong(const Song& song);
};