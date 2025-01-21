#pragma once
#include <functional>

#include "TextBox.h"

class TextBoxTab : public TextBox {
private:
    bool isActive = false;
    std::function<void()> onClickCallback;
    void extraDraw(sf::RenderWindow& window) override;
public:
    TextBoxTab();
    TextBoxTab(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
               const sf::Color& textColor);
    void handleEvents(sf::RenderWindow& window, const sf::Event& event) override;
    void setOnClickCallback(const std::function<void()>& callback);
    TextBoxTab* clone() const override;
    TextBoxTab& operator=(const TextBoxTab &other);
    friend void swap(TextBoxTab& t1, TextBoxTab& t2) noexcept;
    TextBoxTab(const TextBoxTab &other);
};
