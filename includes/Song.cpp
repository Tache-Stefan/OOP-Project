#include "Song.h"

#include <iostream>
#include <thread>

#include "API.h"
#include "Artist.h"
#include "Utility.h"

Song::Song() {};

Song::Song(const std::string& title_, const std::shared_ptr<Artist> &artist_, const std::string& length_, const std::string& id_)
    : Media(title_, artist_, length_), id(id_){
    std::cout << "Created Song(+artist): " << title << std::endl;
}

Song::Song(const std::string &title_, const std::string &length_, const std::string &genre_, const std::string& id_)
        : Media(title_, length_), genre(genre_), id(id_) {}

Song::Song(const std::string& title_, const std::string& length_, const std::string& id_) : Media(title_, length_), id(id_) {
    std::cout << "Created Song: " << title << std::endl;
}

Song::Song(const Song& other) : Media(other), genre(other.genre), id(other.id) {
    std::cout << "Created Song(copiere)" << std::endl;
}

Song& Song::operator=(const Song& other) {
    title = other.title;
    length = other.length;
    artist = other.artist;
    genre = other.genre;
    id = other.id;
    std::cout << "Song(operator=)" << std::endl;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Song& song) {
    os << "Song: " << song.title << ", " << Utils::timeToString(song.length) << "\n";
    return os;
}

std::string Song::getLength() const {return Utils::timeToString(length);}

std::string Song::getID() const {return id;}

void Song::play(const std::string& youtube_api) const {
    std::atomic<bool> stopPlayback(false);
    std::thread inputThread(Utils::monitorInput, std::ref(stopPlayback));
    const std::string youtubeURL = API::searchYouTube(youtube_api, title);
    const std::string outputFile = "audio.mp3";
    if (!Utils::downloadAudio(youtubeURL, outputFile)) {
        return;
    }

    Utils::playAudio(outputFile, stopPlayback);
    inputThread.join();
}
