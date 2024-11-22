#include "Playlist.h"

#include "Utility.h"
#include <algorithm>
#include <random>
#include <chrono>

Playlist::Playlist(const std::string& title_, const std::vector<std::shared_ptr<Song>> &songs_) : title(title_), songs(songs_), length({}) {

    std::cout << "Created Playlist: " << title << "\n";
}

Playlist::Playlist(const std::string &title_) : title(title_) {
    std::cout << "Created Playlist: " << title << "\n";
}

void Playlist::addSong(const std::shared_ptr<Song>& song) {songs.push_back(song);}

std::ostream& operator<<(std::ostream& os, const Playlist& playlist) {
    os << "Playlist: " << playlist.title << "\n";
    os << "Songs: " << "\n";
    for (const auto& song : playlist.songs) {
        os << song->getTitle() << "\n";
    }
    return os;
}

std::string Playlist::getLength() const {return Utils::timeToString(length);}

void Playlist::calculateLength() {
    for(const auto& song : songs)
        length = Utils::addTimes(length, Utils::stringToTime(song->getLength()));
}

void Playlist::shuffle() {
    const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::ranges::shuffle(songs, std::default_random_engine(seed));
    std::cout << "Shuffled Playlist: " << title << "\n";
}
