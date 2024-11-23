#pragma once

#include <memory>
#include <string>
#include <vector>

class Song;

class Artist {
private:
    std::string name = "";
    std::string id = "";
    std::vector<std::shared_ptr<Song>> songs;
public:
    Artist();
    Artist(const std::string& name_, const std::vector<std::shared_ptr<Song>>& songs_);
    Artist(const std::string& name_, const std::string& id_);
    friend std::ostream& operator<<(std::ostream& os, const Artist& artist);
    void addSong(const std::shared_ptr<Song>& song);
    const std::string& getName() const;
    const std::string& getID() const;
};