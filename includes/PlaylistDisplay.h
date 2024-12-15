#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Display.h"
#include "Playlist.h"
#include "SongDisplay.h"

class PlaylistDisplay : public Display {
private:
    std::vector<Playlist> playlists;
    std::array<sf::RectangleShape, 8> playRects;
    std::array<sf::Text, 8> playTexts;
    std::array<sf::RectangleShape, 8> shuffleRects;
    std::array<sf::Text, 8> shuffleTexts;
    SongDisplay songDisplay;
    sf::Text playlistsText;
    bool menuActive = false;
    int currentPlaylist = -1;
    static unsigned int currentIndex;
    static int change;
    void setMaxScroll(int& maxScroll) override;
public:
    explicit PlaylistDisplay(const sf::Font& font_);
    void draw(sf::RenderWindow& window) override;
    void handleEvents(sf::RenderWindow& window, const sf::Event &event, Playlist* playlist) override;
    void savePlaylists();
    void loadPlaylists();
    static void needChangeAddSong();
    static void needChangeRemoveSong();
    PlaylistDisplay* clone() const override;
};
