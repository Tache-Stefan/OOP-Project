#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Media.h"

class Artist;

class Song final : public Media {
private:
    std::string genre = "None";
public:
    Song(const std::string& title_, const std::vector<std::shared_ptr<Artist>> &artists_, const std::string& length_);
    Song(const std::string& title_, const std::string& length_);
    Song(const Song& other);
    Song& operator=(const Song& other);
    friend std::ostream& operator<<(std::ostream& os, const Song& song);
    ~Song() override = default;
    std::string getLength() const;
    void addArtist(const std::shared_ptr<Artist>& artist);
    void play() override;
};
