#pragma once

#include <ctime>
#include <string>
#include "Artist.h"

class MediaItem {
protected:
    std::string title;
    struct tm length = {};
public:
    MediaItem();
    MediaItem(std::string title_, const struct tm& length_);
    explicit MediaItem(std::string title_);
    MediaItem(const MediaItem& other);
    virtual std::string getTitle() const = 0;
    virtual MediaItem* clone() const = 0;
    virtual ~MediaItem() = default;
};
