#include "Song.h"
#include "Artist.h"

Song::Song(const std::string& title_, const float length_, const std::vector<Artist> &artists_) : title(title_), length(length_), artists(artists_) {
    std::cout << "Song(+artist): " << title << std::endl;
}

Song::Song(const std::string& title_, const float length_) : title(title_), length(length_) {
    std::cout << "Song: " << title << std::endl;
}

Song::Song(const Song& other) : title(other.title), length(other.length), artists(other.artists) {
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
    os << "Song: " << song.title << ", " << song.length << "\n";
    return os;
}

float Song::getLength() const {return length;}

void Song::addArtist(const Artist& artist) {
    artists.push_back(artist);
}