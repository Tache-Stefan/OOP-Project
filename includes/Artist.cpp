#include <iostream>
#include "Artist.h"
#include "Song.h"

Artist::Artist() {}

Artist::Artist(const std::string& name_, const std::vector<std::shared_ptr<Song>>& songs_) : name(name_), songs(songs_) {
    std::cout << "Created Artist(+songs): " << name << std::endl;
}
Artist::Artist(const std::string& name_, const std::string& id_) : name(name_), id(id_) {
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
