#pragma once
#include "Media.h"

class Audiobook : public Media {
private:
    int chapter_count = 0;
    std::string language = "None";
public:
    Audiobook(std::string title_, const struct tm& length_, const int chapter_count_, std::string language_);
    Audiobook(std::string title_, const struct tm& length_);
    friend std::ostream& operator<<(std::ostream& os, const Audiobook& audiobook);
    void play(const std::string& youtube_api) const override;
    Media* clone() const override;
};
