#pragma once

#include <memory>

#include "TextBox.h"

class TextBoxAbstractFactory {
public:
    virtual ~TextBoxAbstractFactory();
    virtual std::unique_ptr<TextBox> createButton(const sf::Font& font, const std::string& label) const = 0;
    virtual std::unique_ptr<TextBox> createVolButton(const sf::Font& font, const std::string& label) const = 0;
    virtual std::unique_ptr<TextBox> createTab(const sf::Font& font, const std::string& label) const = 0;
    virtual std::unique_ptr<TextBox> createWrite(const sf::Font& font) const = 0;
    virtual std::unique_ptr<TextBox> createTimer(const sf::Font& font) const = 0;
    virtual std::unique_ptr<TextBox> createVolShow(const sf::Font& font) const = 0;
};
