#include "Audiobook.h"

#include <iostream>
#include <thread>

#include "API.h"
#include "Utility.h"

Audiobook::Audiobook(std::string title_, const struct tm& length_, const int chapter_count_, std::string language_)
        : Media(std::move(title_), length_), chapter_count(chapter_count_), language(std::move(language_)) {}

Audiobook::Audiobook(std::string title_, const struct tm& length_)
        : Media(std::move(title_), length_) {}

std::ostream& operator<<(std::ostream& os, const Audiobook& audiobook) {
        os << "Audiobook: " << audiobook.title << ", chapters: " << audiobook.chapter_count << ", length: "
        << Utils::timeToString(audiobook.length) << ", language: " << audiobook.language << "\n";
        return os;
}

void Audiobook::play(const std::string& youtube_api) const {
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

Media* Audiobook::clone() const {
    return new Audiobook(*this);
}
