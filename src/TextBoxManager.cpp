#include "../headers/TextBoxManager.h"
#include "../headers/TextBoxWrite.h"
#include "../headers/Utility.h"

TextBoxManager::TextBoxManager() = default;

void TextBoxManager::addTextBox(std::unique_ptr<TextBox> textBox) {
    textBoxes.emplace_back(std::move(textBox));
}

void TextBoxManager::addVectorTextBox(std::vector<std::unique_ptr<TextBox>> textBoxes_) {
    for (auto& textBox : textBoxes_) {
        textBoxes.emplace_back(std::move(textBox));
    }
}

void TextBoxManager::draw(const int currentTab, sf::RenderWindow& window) {
    for (const auto& textBox : textBoxes) {
        if (textBox->isTab()) {
            textBox->draw(window);
            continue;
        }
        if (currentTab == 1) {
            if (auto* mainWrite = dynamic_cast<TextBoxWrite*>(textBox.get())) {
                mainWrite->drawSearch(window);
                mainWrite->centerShape(window);
                continue;
            }
            textBox->draw(window);
        }
    }
}

void TextBoxManager::resizeUI(const sf::RenderWindow& window, const float windowWidth, const float windowHeight) const {
    const sf::FloatRect bounds = textBoxes[0]->getBounds();
    for (unsigned int i = 1; i <= 5; ++i) {
        textBoxes[i]->positionShape(
        sf::Vector2f(window.getSize().x / 2.0f - bounds.width / 2.0f + i * 85,
                window.getSize().y / 2.0f - bounds.height / 2.0f + 100),
                sf::Vector2f(window.getSize().x / 2.0f - bounds.width / 2.0f + 17 + i * 85,
                window.getSize().y / 2.0f - bounds.height / 2.0f + 100));
    }
    for (int i = 7; i >= 6; --i) {
        textBoxes[i == 7 ? 6 : 7]->positionShape(
        sf::Vector2f(windowWidth - (i - 5) * 80, windowHeight - 40),
        sf::Vector2f(windowWidth + 10 - (i - 5) * 80, windowHeight - 40));
    }
}

void TextBoxManager::handleEvents(const int currentTab, sf::RenderWindow& window, const sf::Event& event) {
    for (const auto& textBox : textBoxes) {
        if (textBox->isTab()) {
            textBox->handleEvents(window, event);
            continue;
        }
        if (currentTab == 1) {
            textBox->handleEvents(window, event);
        }
    }
}
