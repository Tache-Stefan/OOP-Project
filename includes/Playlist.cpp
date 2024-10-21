#include "Playlist.h"

Playlist::Playlist(const std::string& title_, const std::vector<Song> &songs_, const float length_) : title(title_), songs(songs_), length(length_) {
    std::cout << "Playlist: " << title << "\n";
}

std::ostream& operator<<(std::ostream& os, const Playlist& playlist) {
    os << "Playlist: " << playlist.title << "\n";
    return os;
}

float Playlist::getLength() const {return length;}

void Playlist::calculateLength() {
    float aux = 0;
    for(const auto& song : songs)
        aux += song.getLength();
    length = aux;
}
