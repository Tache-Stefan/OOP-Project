#include <iostream>
#include "includes/Application.h"

int main() {
    sf::Font font;
    if (!font.loadFromFile("fonts/Franie-Regular.otf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    Application app(font);

    app.run();
}
