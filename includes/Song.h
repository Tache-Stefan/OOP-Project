#pragma once
#include <string>

#include "Media.h"

class Artist;

class Song : public Media {
private:
    std::string id = "";
public:
    Song();
    Song(std::string title_, const std::shared_ptr<Artist>& artist_, const struct tm& length_, std::string id_);
    Song(std::string title_, const struct tm& length_, std::string id_);
    Song(const Song& other);
    Song& operator=(const Song& other);
    friend std::ostream& operator<<(std::ostream& os, const Song& song);
    ~Song() override = default;
    std::string getLength() const;
    const std::string& getID() const;
    void play() const override;
    friend void to_json(nlohmann::json& j, const Song& song);
    friend void from_json(nlohmann::json& j, Song& song);
    Media* clone() const override;
};
