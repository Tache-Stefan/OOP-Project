#pragma once
#include "Media.h"

class Audiobook : public Media {
private:
    int chapter_count = 0;
    std::string language = "None";
public:
    Audiobook(const std::string &title_, const std::string &length_, int chapter_count, const std::string &language);
    Audiobook(const std::string &title_, const std::string &length_);
    friend std::ostream& operator<<(std::ostream& os, const Audiobook& audiobook);
    void play(const std::string& youtube_api) const override;
};
