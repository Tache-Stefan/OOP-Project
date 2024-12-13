#include "Song.h"

#include <iostream>
#include <thread>

#include "API.h"
#include "Artist.h"
#include "EnvironmentSetup.h"
#include "MusicPlayer.h"
#include "Utility.h"

Song::Song() = default;

Song::Song(std::string title_, const std::shared_ptr<Artist> &artist_, const struct tm& length_, std::string id_)
    : MediaItem(std::move(title_), length_), artist(artist_), id(std::move(id_)) {
    std::cout << "Created Song: " << title << std::endl;
}

Song::Song(std::string title_, const struct tm& length_, std::string id_) : MediaItem(std::move(title_), length_), id(std::move(id_)) {
    std::cout << "Created Song: " << title << std::endl;
}

Song::Song(const Song& other) : MediaItem(other), artist(other.artist), id(other.id) {
    std::cout << "Created Song(copiere)" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Song& song) {
    os << "Song: " << song.title << ", " << Utils::timeToString(song.length) << ", " << "id: " << song.id << std::endl;
    return os;
}

std::string Song::getLength() const {return Utils::timeToString(length);}

std::string Song::getTitle() const {return title;}

const std::string& Song::getID() const {return id;}

void Song::play() const {

    std::thread playbackThread([this]() {
        const std::string youtubeURL = API::searchYouTube(EnvironmentSetup::getYoutubeAPI(), title);
        const std::string outputFile = "audio.mp3";
        if (!Utils::downloadAudio(youtubeURL, outputFile)) {
            return;
        }

        MusicPlayer::playMusic();
    });

    playbackThread.detach();
}

void to_json(nlohmann::json& j, const Song& song) {
    j["title"] = song.title;
}

void from_json(nlohmann::json& j, Song& song) {
    j.at("title").get_to(song.title);
}

Song* Song::clone() const {
    return new Song(*this);
}

Song& Song::operator=(const Song& other) {
    Song* temp = other.clone();
    swap(*this, *temp);
    delete temp;
    return *this;
}

void swap(Song& s1, Song& s2) noexcept {
    using std::swap;
    swap(s1.title, s2.title);
    swap(s1.length, s2.length);
    swap(s1.artist, s2.artist);
    swap(s1.id, s2.id);
}
