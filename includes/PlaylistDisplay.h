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
    bool menuActive = false;
    int currentPlaylist = -1;
    float scrollSpeed;
    float verticalOffset;
    unsigned int visibleCount;
    int itemHeight;
    static unsigned int currentIndex;
    static bool change;
public:
    explicit PlaylistDisplay(const sf::Font& font_);
    void draw(sf::RenderWindow& window);
    void scrollUp();
    void scrollDown();
    void scrollWithMouse(float delta);
    void handleEvents(sf::RenderWindow& window, const sf::Event &event);
    void savePlaylists();
    void loadPlaylists();
    static void needChange();
};
