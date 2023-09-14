#include <SFML/Graphics.hpp>

#ifndef MENU_H
#define MENU_H

class Menu
{
public:
    Menu(sf::RenderWindow& wnd);
    Menu() = delete;
    ~Menu() = default;
    void draw(); // draw the title and program options
private:
    sf::RenderWindow& wnd; // reference to the window object
    sf::Font vanilla_rav; // downloaded font: https://www.dafont.com/vanilla-ravioli.font
    sf::Text title; // the overhead title
    sf::RectangleShape menuBox; // box that covers the area behind the menu options
};

#endif