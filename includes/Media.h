#pragma once

#include <ctime>
#include <string>
#include <vector>

class Artist;

class Media {
protected:
    std::string title;
    std::vector<Artist> artists;
    struct tm length = {};
public:
    Media(const std::string& title_, const std::vector<Artist>& artists_, const std::string& length_);
    Media(const std::string& title_, const std::string& length_);
    Media(const Media& other);
    virtual void play() = 0;
    virtual ~Media() = default;
};
