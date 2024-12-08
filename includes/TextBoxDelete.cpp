#include "TextBoxDelete.h"

#include <iostream>
#include <memory>

#include "PlaylistDisplay.h"
#include "Song.h"

TextBoxDelete::TextBoxDelete() = default;

TextBoxDelete::TextBoxDelete(sf::RectangleShape box_, const sf::Font& font_, sf::Text text_)
                             : TextBox(box_, sf::Color::Red, font_, text_, sf::Color::White) {
    text.setString("X");
    text.setCharacterSize(34);
    box.setOutlineThickness(0.5f);
    box.setOutlineColor(sf::Color::White);
}

void TextBoxDelete::clickedSong(std::vector<std::shared_ptr<Song>>& songs, const unsigned int songIndex) {
    if (songIndex < songs.size()) {
        std::cout << "delete" << std::endl;
        songs.erase(songs.begin() + songIndex);
        PlaylistDisplay::needChangeRemoveSong();
    }
}

void TextBoxDelete::clickedPlaylist(std::vector<Playlist>& playlists, const unsigned int playlistIndex) {
    if (playlistIndex < playlists.size()) {
        std::cout << "delete" << std::endl;
        playlists.erase(playlists.begin() + playlistIndex);
    }
}

TextBox* TextBoxDelete::clone() const {
    return new TextBoxDelete(*this);
}
