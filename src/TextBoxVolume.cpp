#include "../headers/TextBoxVolume.h"
#include "../headers/Application.h"
#include "../headers/MusicPlayer.h"

TextBoxVolume::TextBoxVolume(const sf::RectangleShape &box_, const sf::Color &boxColor, const sf::Font &font_,
                             const sf::Text &text_, const sf::Color &textColor) :
                             TextBox(box_, boxColor, font_, text_, textColor) {}

void TextBoxVolume::updateText() {
    currentVolume = MusicPlayer::getVolume();
    const std::string curVolString = std::to_string(currentVolume);
    const std::string maxVolString = std::to_string(maxVolume);
    text.setString(curVolString + " / " + maxVolString);
}

void TextBoxVolume::drawRequirement(bool &ok) {
    if (Application::getCurrentTab() != 1)
        ok = false;
}

void TextBoxVolume::extraDraw(sf::RenderWindow&) {
    updateText();
}

void TextBoxVolume::handleEvents(sf::RenderWindow&, const sf::Event&) {}

TextBoxVolume* TextBoxVolume::clone() const {
    return new TextBoxVolume(*this);
}

