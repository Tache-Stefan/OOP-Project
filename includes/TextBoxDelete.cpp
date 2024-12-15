#include "TextBoxDelete.h"

#include <iostream>
#include <memory>

#include "PlaylistDisplay.h"
#include "Song.h"

TextBoxDelete::TextBoxDelete() = default;

TextBoxDelete::TextBoxDelete(sf::RectangleShape box_, const sf::Font& font_, sf::Text text_)
                             : TextBox(std::move(box_), sf::Color::Red, font_, std::move(text_), sf::Color::White) {
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

TextBoxDelete* TextBoxDelete::clone() const {
    return new TextBoxDelete(*this);
}

TextBoxDelete& TextBoxDelete::operator=(const TextBoxDelete& other) {
    TextBoxDelete* temp = other.clone();
    swap(*this, *temp);
    delete temp;
    return *this;
}

void swap(TextBoxDelete& t1, TextBoxDelete& t2) noexcept {
    using std::swap;
    swap(t1.font, t2.font);
    swap(t1.box, t2.box);
    swap(t1.text, t2.text);
}

TextBoxDelete::TextBoxDelete(const TextBoxDelete& other) = default;
