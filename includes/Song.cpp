#include "Song.h"

#include <iostream>
#include <thread>

#include "API.h"
#include "Artist.h"
#include "Utility.h"

Song::Song() = default;

Song::Song(std::string title_, const std::shared_ptr<Artist> &artist_, const struct tm& length_, std::string id_)
    : Media(std::move(title_), artist_, length_), id(std::move(id_)) {
    std::cout << "Created Song: " << title << std::endl;
}

Song::Song(std::string title_, const struct tm& length_, std::string id_) : Media(std::move(title_), length_), id(std::move(id_)) {
    std::cout << "Created Song: " << title << std::endl;
}

Song::Song(const Song& other) : Media(other), id(other.id) {
    std::cout << "Created Song(copiere)" << std::endl;
}

Song& Song::operator=(const Song& other) {
    title = other.title;
    length = other.length;
    artist = other.artist;
    id = other.id;
    std::cout << "Song(operator=)" << std::endl;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Song& song) {
    os << "Song: " << song.title << ", " << Utils::timeToString(song.length) << ", " << "id: " << song.id << std::endl;
    return os;
}

std::string Song::getLength() const {return Utils::timeToString(length);}

const std::string& Song::getID() const {return id;}

void Song::play(const std::string& youtube_api) const {
    std::atomic<bool> stopPlayback(false);
    std::atomic<bool> isMusicPlaying(false);
    std::thread inputThread(Utils::monitorInput, std::ref(stopPlayback));
    const std::string youtubeURL = API::searchYouTube(youtube_api, title);
    const std::string outputFile = "audio.mp3";
    if (!Utils::downloadAudio(youtubeURL, outputFile)) {
        return;
    }

    Utils::playAudio(outputFile, stopPlayback, isMusicPlaying);
    inputThread.join();
}

void Song::play(const std::string& youtube_api, std::atomic<bool>& stopPlayback, std::atomic<bool>& isMusicPlaying) const {

    std::thread playbackThread([this, youtube_api, &stopPlayback, &isMusicPlaying]() {
        const std::string youtubeURL = API::searchYouTube(youtube_api, title);
        const std::string outputFile = "audio.mp3";
        if (!Utils::downloadAudio(youtubeURL, outputFile)) {
            return;
        }

        Utils::playAudio(outputFile, stopPlayback, isMusicPlaying);
    });

    playbackThread.detach();
}

void to_json(nlohmann::json& j, const Song& song) {
    j["title"] = song.title;
}

void from_json(nlohmann::json& j, Song& song) {
    j.at("title").get_to(song.title);
}

Media* Song::clone() const {
    return new Song(*this);
}
