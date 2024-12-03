#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <nlohmann/json.hpp>

#include "Song.h"

class Playlist {
private:
    std::string title = "";
    std::vector<std::shared_ptr<Song>> songs;
    struct tm length = {};
public:
    Playlist();
    Playlist(std::string title_, const std::vector<std::shared_ptr<Song>> &songs_);
    explicit Playlist(std::string title_);
    void addSong(const std::shared_ptr<Song>& song);
    friend std::ostream& operator<<(std::ostream& os, const Playlist& playlist);
    std::string getLength() const;
    std::string getTitle() const;
    std::vector<std::shared_ptr<Song>> getSongs() const;
    void calculateLength();
    void play(const std::string& youtube_api) const;
    void shuffle();
    friend void to_json(nlohmann::json& j, const Playlist& playlist);
    friend void from_json(const nlohmann::json& j, Playlist& playlist);
};
