#pragma once

#include "PlaylistDisplay.h"
#include "Song.h"
#include "TextBox.h"

class TextBoxDelete : public TextBox {
public:
    TextBoxDelete();
    TextBoxDelete(sf::RectangleShape box_, const sf::Font& font_, sf::Text text_);
    template<class T>
    static void clickedItem(std::vector<T> &items, unsigned int index);
    void handleEvents(sf::RenderWindow &, const sf::Event &) override;
    TextBoxDelete* clone() const override;
    TextBoxDelete& operator=(const TextBoxDelete &other);
    friend void swap(TextBoxDelete& t1, TextBoxDelete& t2) noexcept;
    TextBoxDelete(const TextBoxDelete &other);
};

template<class T>
void TextBoxDelete::clickedItem(std::vector<T>& items, const unsigned int index) {
    if (index < items.size()) {
        items.erase(items.begin() + index);
    }
}

template<>
inline void TextBoxDelete::clickedItem<std::shared_ptr<Song>>(std::vector<std::shared_ptr<Song>>& songs, const unsigned int index) {
    if (index < songs.size()) {
        songs.erase(songs.begin() + index);
        PlaylistDisplay::needChangeRemoveSong();
    }
}
