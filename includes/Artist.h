#pragma once

#include <memory>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class Song;

class Artist {
private:
    std::string name = "";
    std::string id = "";
    std::vector<std::shared_ptr<Song>> songs;
public:
    Artist();
    Artist(std::string name_, const std::vector<std::shared_ptr<Song>>& songs_);
    Artist(std::string name_, std::string id_);
    friend std::ostream& operator<<(std::ostream& os, const Artist& artist);
    void addSong(const std::shared_ptr<Song>& song);
    const std::string& getName() const;
    const std::string& getID() const;
    friend void to_json(nlohmann::json& j, const Artist& artist);
    friend void from_json(nlohmann::json& j, Artist& artist);
};