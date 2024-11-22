#pragma once

#include <ctime>
#include <memory>
#include <string>
#include "Artist.h"

class Media {
protected:
    std::string title = "";
    std::shared_ptr<Artist> artist;
    struct tm length = {};
public:
    Media();
    Media(const std::string& title_, const std::shared_ptr<Artist>& artist_, const std::string& length_);
    Media(const std::string& title_, const std::string& length_);
    Media(const Media& other);
    const std::string& getTitle() const;
    virtual void play(const std::string& youtube_api) const = 0;
    virtual ~Media() = default;
};
