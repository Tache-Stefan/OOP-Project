#pragma once

#include <functional>

#include "TextBox.h"

class TextBoxButton : public TextBox {
private:
    bool isActive = false;
    std::function<void()> onClickCallback;
    sf::Color originalColor;
    void extraDraw(sf::RenderWindow& window) override;
    void drawRequirement(sf::RenderWindow&, bool &ok) override;
public:
    TextBoxButton(sf::RectangleShape box_, const sf::Color& boxColor, const sf::Font& font_, sf::Text text_,
                  const sf::Color& textColor);
    void setOnClickCallback(const std::function<void()> &callback);
    void handleEvents(sf::RenderWindow &window, const sf::Event &event) override;
    TextBoxButton* clone() const override;
    TextBoxButton& operator=(const TextBoxButton &other);
    friend void swap(TextBoxButton& t1, TextBoxButton& t2) noexcept;
    TextBoxButton(const TextBoxButton &other);
};
