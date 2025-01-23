#pragma once
#include <string>

#include "MediaItem.h"

class Artist;

class Song : public MediaItem {
private:
    std::shared_ptr<Artist> artist;
    std::string id;
public:
    Song();
    ~Song() override = default;
    Song(std::string title_, const std::shared_ptr<Artist>& artist_, const struct tm& length_, std::string id_);
    Song(std::string title_, const struct tm& length_, std::string id_);
    Song(const Song& other);
    friend std::ostream& operator<<(std::ostream& os, const Song& song);
    std::string getLength() const;
    std::string getTitle() const override;
    const std::string& getID() const;
    void play() const;
    friend void to_json(nlohmann::json& j, const Song& song);
    friend void from_json(nlohmann::json& j, Song& song);
    Song* clone() const override;
    Song& operator=(const Song& other);
    friend void swap(Song& s1, Song& s2) noexcept;
};
