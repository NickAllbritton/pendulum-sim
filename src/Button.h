#include <SFML/Graphics.hpp>
#include "Physics.h"
#include "Pendulum.h"

#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
    Button(sf::RenderWindow & wnd, sf::Font & font, sf::Color c, sf::Vector2f pos, std::string str, float w, float h);
    // overload that automatically calculates the width and height based on the text
    Button(sf::RenderWindow& wnd, sf::Font& font, sf::Color c, sf::Vector2f pos, 
                std::string str, const sf::Vector2f& size = sf::Vector2f(0.f, 0.f));
    Button() = default;
    ~Button() = default;
    void draw(sf::RenderWindow& wnd);
    void setText(std::string t);
    std::string getText()
    {
        return text.getString();
    }
    Physics::SolutionMethod click();
    bool mouseClickWithinBounds(sf::Vector2f pos);
public:
    sf::Vector2f pos; // position of top left corner of the button's hitbox
    float width;
    float height;
    bool state;
private:
    sf::Text text; // for now all buttons have text to be clickable
    sf::Color c; // each button should have a color
};

#endif