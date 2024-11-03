#ifndef INDICATOR_H
#define INDICATOR_H

#include <SFML/Graphics.hpp>
#include "Physics.h"

class Indicator
{
public:
    Indicator(sf::RenderWindow& wnd, sf::Font& font, Physics::SolutionMethod method, sf::Color color, int index);
    Indicator() = default;
    void draw(sf::RenderWindow& wnd);
    Physics::SolutionMethod getMethod() const
    {
        return method;
    }
private:
    sf::RectangleShape background;
    sf::Text text;
    Physics::SolutionMethod method;
};

#endif