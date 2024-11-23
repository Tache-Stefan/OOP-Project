#pragma once

#include <string>
#include "Media.h"

class Artist;

class Song : public Media {
private:
    std::string genre = "None";
    std::string id = "";
public:
    Song();
    Song(const std::string& title_, const std::shared_ptr<Artist> &artist_, const std::string& length_, const std::string& id_);
    Song(const std::string &title_, const std::string &length_, const std::string &genre_, const std::string& id_);
    Song(const std::string& title_, const std::string& length_, const std::string& id_);
    Song(const Song& other);
    Song& operator=(const Song& other);
    friend std::ostream& operator<<(std::ostream& os, const Song& song);
    ~Song() override = default;
    std::string getLength() const;
    const std::string& getID() const;
    void play(const std::string& youtube_api) const override;
};
