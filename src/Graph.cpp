#include "Graph.h"

Graph::Graph(sf::RenderWindow &wnd, sf::Vector2f pos, sf::Vector2f size)
{
    nexa_light.loadFromFile("./resources/Nexa-ExtraLight.ttf");

    // draw background rectangle
    background.setSize(size); // 5% screen height after title and before right side of screen
    background.setPosition(pos);
    background.setFillColor(sf::Color::Black); 

    // create axes

    // create labels
}

void Graph::draw(sf::RenderWindow &wnd)
{
    wnd.draw(background);
}

void Graph::plot()
{
}

sf::Vector2f Graph::GraphCoordinates(sf::Vector2f screenPos)
{
    return sf::Vector2f();
}
