#include "Podcast.h"

#include <iostream>
#include <thread>

#include "API.h"
#include "Utility.h"

Podcast::Podcast(const std::string &title_, const std::shared_ptr<Artist> &artist_, const struct tm& length_,
                 const int episode_number)
        : Media(title_, artist_, length_), episode_number(episode_number) {}

Podcast::Podcast(const std::string &title_, const struct tm& length_, const int episode_number)
        : Media(title_, length_), episode_number(episode_number) {}

std::ostream& operator<<(std::ostream& os, const Podcast& podcast) {
    os << "Podcast: " << podcast.title << ", episode: " << podcast.episode_number << ", length: " << Utils::timeToString(podcast.length) << "\n";
    return os;
}

void Podcast::play(const std::string& youtube_api) const {
    const std::string youtubeURL = API::searchYouTube(youtube_api, title);
    const std::string outputFile = "audio.mp3";
    if (!Utils::downloadAudio(youtubeURL, outputFile)) {
        return;
    }

    std::atomic<bool> stopPlayback(false);
    std::thread inputThread(Utils::monitorInput, std::ref(stopPlayback));
    //Utils::playAudio(outputFile, stopPlayback);
    inputThread.join();
}

Media* Podcast::clone() const {
    return new Podcast(*this);
}
