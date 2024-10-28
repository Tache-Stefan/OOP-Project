#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "Artist.h"

class Song {
private:
    std::string title;
    struct tm length = {};
    std::vector<Artist> artists;
public:
    Song(const std::string& title_, const std::string& length_, const std::vector<Artist> &artists_);
    Song(const std::string& title_, const std::string& length_);
    Song(const Song& other);
    Song& operator=(const Song& other);
    friend std::ostream& operator<<(std::ostream& os, const Song& song);
    ~Song() = default;
    std::string getLength() const;
    void addArtist(const Artist& artist);
};
