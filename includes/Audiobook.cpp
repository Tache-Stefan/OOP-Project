#include <iostream>
#include "Audiobook.h"

#include "Utility.h"

Audiobook::Audiobook(const std::string &title_, const std::string &length_, const int chapter_count, const std::string &language)
        : Media(title_, length_), chapter_count(chapter_count), language(language) {}

Audiobook::Audiobook(const std::string &title_, const std::string &length_)
        : Media(title_, length_) {}

std::ostream& operator<<(std::ostream& os, const Audiobook& audiobook) {
        os << "Audiobook: " << audiobook.title << ", chapters: " << audiobook.chapter_count << ", length: "
        << Utils::timeToString(audiobook.length) << ", language: " << audiobook.language << "\n";
        return os;
}

void Audiobook::play(const std::string& youtube_api) const {
        std::cout << "Playing audiobook: " << title <<std::endl;
}
