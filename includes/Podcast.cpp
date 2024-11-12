#include "Podcast.h"

#include <iostream>

#include "Utility.h"

Podcast::Podcast(const std::string &title_, const std::vector<std::shared_ptr<Artist>> &artists_, const std::string &length_,
                 const int episode_number)
        : Media(title_, artists_, length_), episode_number(episode_number) {}

Podcast::Podcast(const std::string &title_, const std::string &length_, const int episode_number)
        : Media(title_, length_), episode_number(episode_number) {}

std::ostream& operator<<(std::ostream& os, const Podcast& podcast) {
    os << "Podcast: " << podcast.title << ", episode: " << podcast.episode_number << ", length: " << Utils::timeToString(podcast.length) << "\n";
    return os;
}

void Podcast::play() const {
    std::cout << "Playing podcast: " << title <<std::endl;
}
