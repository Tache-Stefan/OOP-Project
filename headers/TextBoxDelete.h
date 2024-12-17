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
    void handleEvents(sf::RenderWindow &, const sf::Event &) override;
    TextBoxDelete* clone() const override;
    TextBoxDelete& operator=(const TextBoxDelete &other);
    friend void swap(TextBoxDelete& t1, TextBoxDelete& t2) noexcept;
    TextBoxDelete(const TextBoxDelete &other);
};
