#include "Song.h"
#include "Artist.h"
#include "Utility.h"

Song::Song(const std::string& title_, const std::vector<Artist> &artists_, const std::string& length_) : Media(title_, artists_,
     length_) {
    std::cout << "Song(+artist): " << title << std::endl;
}

Song::Song(const std::string& title_, const std::string& length_) : Media(title_, length_) {
    std::cout << "Song: " << title << std::endl;
}

Song::Song(const Song& other) : Media(other), genre(other.genre) {
    std::cout << "Song(copiere)" << std::endl;
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

void Song::addArtist(const Artist& artist) {
    artists.push_back(artist);
}

void Song::play() {
    std::cout << "Song(play)" << std::endl;
}
