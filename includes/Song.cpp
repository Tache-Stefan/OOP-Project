#include <iostream>
#include "Song.h"
#include "Artist.h"
#include "Utility.h"

Song::Song(const std::string& title_, const std::vector<std::shared_ptr<Artist>> &artists_, const std::string& length_) : Media(title_, artists_,
     length_) {
    std::cout << "Created Song(+artist): " << title << std::endl;
}

Song::Song(const std::string &title_, const std::string &length_, const std::string &genre)
        : Media(title_, length_), genre(genre) {}

Song::Song(const std::string& title_, const std::string& length_) : Media(title_, length_) {
    std::cout << "Created Song: " << title << std::endl;
}

Song::Song(const Song& other) : Media(other), genre(other.genre) {
    std::cout << "Created Song(copiere)" << std::endl;
}

Song& Song::operator=(const Song& other) {
    title = other.title;
    length = other.length;
    artists = other.artists;
    std::cout << "Song(operator=)" << std::endl;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Song& song) {
    os << "Song: " << song.title << ", " << Utils::timeToString(song.length) << "\n";
    return os;
}

std::string Song::getLength() const {return Utils::timeToString(length);}

void Song::addArtist(const std::shared_ptr<Artist>& artist) {
    artists.push_back(artist);
}

void Song::play() const {
    std::cout << "Playing song: " << title <<std::endl;
}
