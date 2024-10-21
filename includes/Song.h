#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "Artist.h"

class Artist;

class Song {
private:
    std::string title;
    float length;
    std::vector<Artist> artists;
public:
    Song(const std::string& title_, const float length_, const std::vector<Artist> &artists_);
    Song(const std::string& title_, const float length_);
    Song(const Song& other);
    Song& operator=(const Song& other);
    friend std::ostream& operator<<(std::ostream& os, const Song& song);
    ~Song() {std::cout << "Song(destr)" << std::endl; }
    float getLength() const;
    void addArtist(const Artist& artist);
};

