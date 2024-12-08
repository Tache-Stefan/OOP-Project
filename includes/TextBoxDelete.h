#pragma once

#include "Playlist.h"
#include "Song.h"
#include "TextBox.h"

class TextBoxDelete : public TextBox {
public:
    TextBoxDelete();
    TextBoxDelete(sf::RectangleShape box_, const sf::Font& font_, sf::Text text_);
    static void clickedSong(std::vector<std::shared_ptr<Song>>& songs, unsigned int songIndex);
    static void clickedPlaylist(std::vector<Playlist>& playlists, unsigned int playlistIndex);
    TextBox* clone() const override;
};
