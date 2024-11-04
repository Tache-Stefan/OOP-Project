#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Artist.h"
#include "Media.h"

class Song final : public Media {
private:
    std::string genre = "None";
public:
    Song(const std::string& title_, const std::vector<Artist> &artists_, const std::string& length_);
    Song(const std::string& title_, const std::string& length_);
    Song(const Song& other);
    Song& operator=(const Song& other);
    friend std::ostream& operator<<(std::ostream& os, const Song& song);
    ~Song() override = default;
    std::string getLength() const;
    void addArtist(const Artist& artist);
    void play() override;
};
