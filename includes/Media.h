#pragma once

#include <ctime>
#include <memory>
#include <string>
#include <vector>
#include "Artist.h"

class Media {
protected:
    std::string title;
    std::vector<std::shared_ptr<Artist>> artists;
    struct tm length = {};
public:
    Media(const std::string& title_, const std::vector<std::shared_ptr<Artist>>& artists_, const std::string& length_);
    Media(const std::string& title_, const std::string& length_);
    Media(const Media& other);
    const std::string& getTitle() const;
    virtual void play() = 0;
    virtual ~Media() = default;
};
