#include <iostream>
#include "headers/Application.h"
#include "headers/Exceptions.h"

int main() {
    sf::Font font;
    if (!font.loadFromFile("fonts/Franie-Regular.otf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    try {
        auto& app = Application::getInstance(font);
        app.run();
    } catch (const EnvironmentException& e) {
        std::cerr << e.what() << std::endl;
    }
}
