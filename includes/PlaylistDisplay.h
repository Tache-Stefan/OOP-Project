#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Playlist.h"

class PlaylistDisplay {
private:
    std::vector<Playlist> playlists;
    sf::Font font;
    float scrollSpeed;
    float verticalOffset;
    unsigned int visibleCount;
    int itemHeight;
    static unsigned int currentIndex;
public:
    explicit PlaylistDisplay(const sf::Font& font_);
    void draw(sf::RenderWindow& window);
    void scrollUp();
    void scrollDown();
    void scrollWithMouse(float delta);
    void handleEvents(sf::RenderWindow& window, const sf::Event &event);
    void savePlaylists();
    void loadPlaylists();
};
