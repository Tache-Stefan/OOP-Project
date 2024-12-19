#pragma once

#include "TextBoxAbstractFactory.h"

class TextBoxConcreteFactory : public TextBoxAbstractFactory {
public:
    std::unique_ptr<TextBox> createButton(const sf::Font &font, const std::string &label) const override;
    std::unique_ptr<TextBox> createVolButton(const sf::Font &font, const std::string &label) const override;
    std::unique_ptr<TextBox> createTab(const sf::Font &font, const std::string &label) const override;
    std::unique_ptr<TextBox> createWrite(const sf::Font &font) const override;
};
