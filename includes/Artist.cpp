#include <iostream>
#include "Artist.h"
#include "Song.h"

Artist::Artist(const std::string& name_, const std::vector<std::shared_ptr<Song>>& songs_) : name(name_), songs(songs_) {
    std::cout << "Created Artist(+songs): " << name << std::endl;
}
Artist::Artist(const std::string& name) {
    std::cout << "Created Artist: " << name << std::endl;
}
std::ostream& operator<<(std::ostream& os, const Artist& artist) {
    os << "Artist: " << artist.name << std::endl;
    return os;
}
void Artist::addSong(const std::shared_ptr<Song>& song) {
    songs.push_back(song);
}