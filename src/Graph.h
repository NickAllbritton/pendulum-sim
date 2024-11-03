#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics.hpp>

class Graph
{
public:
    Graph(sf::RenderWindow& wnd, sf::Vector2f pos, sf::Vector2f size);
    void draw(sf::RenderWindow& wnd);
    void plot();
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

private:
    sf::Vector2f origin;
    sf::RectangleShape background;
    std::vector<sf::CircleShape> points;
    sf::Font nexa_light;
    std::pair<sf::Text, sf::Text> axisLabels;
    std::pair<sf::RectangleShape, sf::RectangleShape> axes;
    std::vector<sf::Text> tickLabels;
};

#endif