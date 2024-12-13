#pragma once

#include <SFML/Graphics.hpp>
#include "Display.h"
#include "Song.h"
#include "TextBoxWrite.h"

class SongDisplay : public Display {
private:
    std::vector<std::shared_ptr<Song>> songs;
    sf::Text songsText;
    static unsigned int currentIndex;
    void setMaxScroll(int& maxScroll) override;
public:
    explicit SongDisplay(const sf::Font& font_);
    void setSongs(const std::vector<std::shared_ptr<Song>>& songs_);
    std::vector<std::shared_ptr<Song>> getSongs() const;
    void draw(sf::RenderWindow &window) override;
    void handleEvents(sf::RenderWindow &window, const sf::Event& event, Playlist* playlist) override;
    SongDisplay* clone() const override;
};
