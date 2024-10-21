#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Song.h"

class Playlist {
private:
    std::string title;
    std::vector<Song> songs;
    float length;
public:
    Playlist(const std::string& title_, const std::vector<Song> &songs_, const float length_ = 0);
    friend std::ostream& operator<<(std::ostream& os, const Playlist& playlist);
    float getLength() const;
    void calculateLength();
};
