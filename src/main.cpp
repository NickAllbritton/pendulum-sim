#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            switch(event.type)
            {
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Q) window.close(); // press q to close the window
                break;
            }
        }

        window.clear();
        window.display();
    }
}