#pragma once
#include "TextBox.h"

#include <SFML/Graphics.hpp>

#include "Playlist.h"

class TextBoxWrite : public TextBox {
private:
    bool isActive = false;
    std::string userInput = "";
    std::string currentSong = "";
    void handleEvents(sf::RenderWindow& window, const sf::Event& event);
public:
    TextBoxWrite();
    TextBoxWrite(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_, const sf::Color& textColor);
    bool containsClick(const sf::Vector2f& mousePosition);
    void handleEventsMusic(sf::RenderWindow& window, const sf::Event& event);
    void handleEventsSongDisplay(sf::RenderWindow& window, const sf::Event& event, Playlist& playlist);
    void handleEventsPlaylistDisplay(sf::RenderWindow& window, const sf::Event& event, std::vector<Playlist>& playlists);
    void draw(sf::RenderWindow& window) const override;
    void drawSearch(sf::RenderWindow& window) const;
    bool getActive() const;
    TextBoxWrite* clone() const override;
    TextBoxWrite& operator=(const TextBoxWrite &other);
    friend void swap(TextBoxWrite& t1, TextBoxWrite& t2) noexcept;
};
