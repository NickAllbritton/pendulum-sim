#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"

#ifndef MENU_H
#define MENU_H

enum class MenuOptions
{
    PlayPause,
    SmallAngle,
    Euler,
    EulerCromer,
    RungeKutta,
    Reset
};

class Menu
{
public:
    Menu(sf::RenderWindow& wnd);
    Menu() = delete;
    ~Menu() = default;
    void draw(); // draw the title and program options
    Physics::SolutionMethod clickAction(sf::Vector2f mPos); // if there is a click event call this method
    void simulateClick(MenuOptions button); // simulate a click of a button
    MenuOptions clickNULLMethod(sf::Vector2f mPos); // if the click was determined to not be a method action
    sf::Vector2f getTitleSize() const
    {
        return title.getLocalBounds().getSize();
    }
private:
    sf::RenderWindow& wnd; // reference to the window object
    sf::Font vanilla_rav; // downloaded font: https://www.dafont.com/vanilla-ravioli.font
    sf::Text title; // the overhead title
    std::vector<Button> menuOptions;
    // sf::RectangleShape menuBox; // box that covers the area behind the menu options
};

#endif