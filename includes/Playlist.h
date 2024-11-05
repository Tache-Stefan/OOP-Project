#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Song.h"

class Playlist {
private:
    std::string title;
    std::vector<std::shared_ptr<Song>> songs;
    struct tm length = {};
public:
    Playlist(const std::string& title_, const std::vector<std::shared_ptr<Song>> &songs_, const std::string& length_);
    Playlist(const std::string& title_, const std::vector<std::shared_ptr<Song>> &songs_);
    friend std::ostream& operator<<(std::ostream& os, const Playlist& playlist);
    std::string getLength() const;
    void calculateLength();
};
