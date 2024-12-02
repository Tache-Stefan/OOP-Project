#include "Playlist.h"

#include "Utility.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

#include "API.h"
#include "EnvironmentSetup.h"

Playlist::Playlist() = default;

Playlist::Playlist(const std::string& title_, const std::vector<std::shared_ptr<Song>>& songs_) : title(title_), songs(songs_), length({}) {

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

std::string Playlist::getTitle() const {return title;}

void Playlist::calculateLength() {
    for(const auto& song : songs)
        length = Utils::addTimes(length, Utils::stringToTime(song->getLength()));
}

void Playlist::play(const std::string& youtube_api) const {
    for (const auto& song : songs) {
        song->play(youtube_api);
    }
}

void Playlist::shuffle() {
    const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::ranges::shuffle(songs, std::default_random_engine(seed));
    std::cout << "Shuffled Playlist: " << title << "\n";
}

void to_json(nlohmann::json& j, const Playlist& playlist) {
    j["title"] = playlist.title;

    std::vector<std::string> song_titles;
    song_titles.reserve(playlist.songs.size());
    for (const auto& song_ptr : playlist.songs) {
        song_titles.push_back(song_ptr->getTitle());
    }

    j["songs"] = song_titles;
}

void from_json(const nlohmann::json& j, Playlist& playlist) {
    playlist.title = j["title"];
    std::vector<std::string> songs = j["songs"].get<std::vector<std::string>>();
    for (const auto &song : songs) {
        std::shared_ptr<Song> song_ptr = API::searchSpotifySong(EnvironmentSetup::getAccessToken(), song);
        playlist.addSong(song_ptr);
    }
}
