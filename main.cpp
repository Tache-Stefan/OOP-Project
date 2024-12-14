#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "includes/Application.h"

int main() {
    sf::Font font;
    if (!font.loadFromFile("fonts/Franie-Regular.otf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    Application app(font);

    app.run();
}
