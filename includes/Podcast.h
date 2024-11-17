#pragma once
#include "Media.h"

class Podcast final : public Media {
private:
    int episode_number = 0;
public:
    Podcast(const std::string &title_, const std::vector<std::shared_ptr<Artist>> &artists_, const std::string &length_,
            int episode_number);
    Podcast(const std::string &title_, const std::string &length_, int episode_number);
    friend std::ostream& operator<<(std::ostream& os, const Podcast& podcast);
    void play(const std::string& youtube_api) const override;
};
