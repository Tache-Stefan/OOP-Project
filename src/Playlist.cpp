#include "../headers/Playlist.h"

#include "../headers/Utility.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <thread>

#include "../headers/API.h"
#include "../headers/MusicPlayer.h"

Playlist::Playlist() = default;

Playlist::Playlist(const std::string &title_, const std::vector<std::shared_ptr<Song>>& songs_) : MediaItem(title_), songs(songs_) {}

Playlist::Playlist(const std::string &title_) : MediaItem(title_) {}

void Playlist::addSong(const std::shared_ptr<Song>& song) {songs.emplace_back(song);}

std::ostream& operator<<(std::ostream& os, const Playlist& playlist) {
    os << "Playlist: " << playlist.title << "\n";
    os << "Songs: " << "\n";
    for (const auto& song : playlist.songs) {
        os << song->getTitle() << "\n";
    }
    return os;
}

Playlist::Playlist(const Playlist& other) = default;

std::string Playlist::getTitle() const {return title;}

std::vector<std::shared_ptr<Song>> Playlist::getSongs() const {return songs;}

void Playlist::setSongs(const std::vector<std::shared_ptr<Song>>& songs_) { songs = songs_;}

void Playlist::calculateLength() {
    for(const auto& song : songs)
        length = Utils::addTimes(length, Utils::stringToTime(song->getLength()));
}

void Playlist::play() const {
    MusicPlayer::setStopPlayback(true);
    MusicPlayer::setPlaylistPlaying(true);

    std::thread playlistThread([this]() {
        for (const auto& song : songs) {
            song->play();

            while (MusicPlayer::getIsMusicPlaying() || MusicPlayer::getLoadingMusic()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            if (!MusicPlayer::getPlaylistPlaying())
                break;
        }
        MusicPlayer::setPlaylistPlaying(false);
    });

    playlistThread.detach();
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
        song_titles.emplace_back(song_ptr->getTitle());
    }

    j["songs"] = song_titles;
}

void from_json(const nlohmann::json& j, Playlist& playlist) {
    playlist.title = j["title"];
    std::vector<std::string> songs = j["songs"].get<std::vector<std::string>>();
    for (const auto &song : songs) {
        std::shared_ptr<Song> song_ptr = API::searchSpotifySong(song);
        playlist.addSong(song_ptr);
    }
}

Playlist* Playlist::clone() const {
    return new Playlist(*this);
}

Playlist& Playlist::operator=(const Playlist& other) {
    Playlist* temp = other.clone();
    swap(*this, *temp);
    delete temp;
    return *this;
}

void swap(Playlist& p1, Playlist& p2) noexcept {
    using std::swap;
    swap(p1.title, p2.title);
    swap(p1.length, p2.length);
    swap(p1.songs, p2.songs);
}
