#include <iostream>
#include "Artist.h"
#include "Song.h"

Artist::Artist() = default;

Artist::Artist(std::string name_, const std::vector<std::shared_ptr<Song>>& songs_) : name(std::move(name_)), songs(songs_) {
    std::cout << "Created Artist(+songs): " << name << std::endl;
}

Artist::Artist(std::string name_, std::string id_) : name(std::move(name_)), id(std::move(id_)) {
    std::cout << "Created Artist: " << name << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Artist& artist) {
    os << "Artist: " << artist.name << std::endl;
    return os;
}

void Artist::addSong(const std::shared_ptr<Song>& song) {
    songs.push_back(song);
}

const std::string& Artist::getName() const {return name;}

const std::string& Artist::getID() const {return id;}

void to_json(nlohmann::json& j, const Artist& artist) {
    j["name"] = artist.name;
}

void from_json(nlohmann::json& j, Artist& artist) {
    j.at("name").get_to(artist.name);
}

Artist& Artist::operator=(Artist& other) {
    swap(*this, other);
    return *this;
}

void swap(Artist& a1, Artist& a2) noexcept {
    using std::swap;
    swap(a1.name, a2.name);
    swap(a1.id, a2.id);
    swap(a1.songs, a2.songs);
}
