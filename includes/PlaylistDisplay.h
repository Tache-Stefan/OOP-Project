#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Playlist.h"
#include "SongDisplay.h"

class PlaylistDisplay {
private:
    std::vector<Playlist> playlists;
    sf::Font font;
    SongDisplay songDisplay;
    TextBoxWrite inputBox;
    sf::Text inputText;
    sf::Text playlistsText;
    std::array<sf::RectangleShape, 8> textsRects;
    std::array<sf::Text, 8> texts;
    std::array<sf::RectangleShape, 8> deleteRects;
    bool menuActive = false;
    int currentPlaylist = -1;
    float scrollSpeed;
    float verticalOffset;
    unsigned int visibleCount;
    int itemHeight;
    static unsigned int currentIndex;
    static int change;
public:
    explicit PlaylistDisplay(const sf::Font& font_);
    void draw(sf::RenderWindow& window);
    void scrollUp();
    void scrollDown();
    void scrollWithMouse(float delta);
    void handleEvents(sf::RenderWindow& window, const sf::Event &event);
    void savePlaylists();
    void loadPlaylists();
    static void needChangeAddSong();
    static void needChangeRemoveSong();
};
