#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics.hpp>
#include "Physics.h"

class Graph
{
public:
    Graph(sf::RenderWindow& wnd, sf::Vector2f pos, sf::Vector2f size);
    void draw(sf::RenderWindow& wnd);
    void plot(float t, float E, Physics::SolutionMethod meth, sf::Color c);
    void deletePoints(Physics::SolutionMethod method);
    void setScale(float t, float E)
    {
        t_scale = t;
        E_scale = E;
    }
    void setSize(sf::Vector2f size)
    {
        background.setSize(size);
    }
    sf::Vector2f getSize() const
    {
        return background.getLocalBounds().getSize();
    }
    void setPos(const sf::Vector2f& pos)
    {
        background.setPosition(pos);
    }
private:
    sf::Vector2f ScreenCoordinates(sf::Vector2f graphPos);
    bool withinGraph(sf::Vector2f pos);

private:
    sf::Vector2f origin;
    sf::RectangleShape background;
    std::vector<std::pair<sf::CircleShape, Physics::SolutionMethod>> points;
    sf::Font nexa_light;
    std::pair<sf::Text, sf::Text> axisLabels;
    std::pair<sf::RectangleShape, sf::RectangleShape> axes;
    std::vector<sf::Text> tickLabels;
    // axis scales
    float t_scale;
    float E_scale;
};

#endif