#pragma once
#include "Media.h"

class Podcast : public Media {
private:
    int episode_number = 0;
public:
    Podcast(const std::string& title_, const std::shared_ptr<Artist>& artist_, const struct tm& length_,
            int episode_number);
    Podcast(const std::string& title_, const struct tm& length_, int episode_number);
    friend std::ostream& operator<<(std::ostream& os, const Podcast& podcast);
    void play(const std::string& youtube_api) const override;
    Media* clone() const override;
};
