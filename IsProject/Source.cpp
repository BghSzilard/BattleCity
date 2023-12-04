#include <SFML/Graphics.hpp>
#include "Menu.h"

int main()
{
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Menu");

    // Create a Menu with the window reference
    Menu menu(window);

    // Main game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        // Draw the menu
        menu.draw();

        // Display the window
        window.display();
    }


    return 0;
}
