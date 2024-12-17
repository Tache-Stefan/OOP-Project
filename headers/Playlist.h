#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "MediaItem.h"
#include "Song.h"

class Playlist : public MediaItem {
private:
    std::vector<std::shared_ptr<Song>> songs;
public:
    Playlist();
    ~Playlist() override = default;
    Playlist(const std::string &title_, const std::vector<std::shared_ptr<Song>> &songs_);
    explicit Playlist(const std::string &title_);
    void addSong(const std::shared_ptr<Song>& song);
    friend std::ostream& operator<<(std::ostream& os, const Playlist& playlist);
    Playlist(const Playlist &other);
    std::string getLength() const;
    std::string getTitle() const override;
    std::vector<std::shared_ptr<Song>> getSongs() const;
    void setSongs(const std::vector<std::shared_ptr<Song>>& songs_);
    void calculateLength();
    void play() const override;
    void shuffle();
    friend void to_json(nlohmann::json& j, const Playlist& playlist);
    friend void from_json(const nlohmann::json& j, Playlist& playlist);
    Playlist *clone() const override;
    Playlist& operator=(const Playlist& other);
    friend void swap(Playlist& p1, Playlist& p2) noexcept;
};
