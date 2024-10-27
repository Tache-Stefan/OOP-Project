#include "Playlist.h"

#include "Utility.h"

Playlist::Playlist(const std::string& title_, const std::vector<Song> &songs_, const std::string& length_) : title(title_),
                   songs(songs_), length(Utils::stringToTime(length_)) {

    std::cout << "Playlist: " << title << "\n";
}

Playlist::Playlist(const std::string& title_, const std::vector<Song> &songs_) : title(title_), songs(songs_) {

    std::cout << "Playlist: " << title << "\n";
}

std::ostream& operator<<(std::ostream& os, const Playlist& playlist) {
    os << "Playlist: " << playlist.title << "\n";
    return os;
}

std::string Playlist::getLength() const {return Utils::timeToString(length);}

void Playlist::calculateLength() {
    for(const auto& song : songs)
        length = Utils::addTimes(length, Utils::stringToTime(song.getLength()));
}
