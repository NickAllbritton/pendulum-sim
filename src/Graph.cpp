#include "Graph.h"

Graph::Graph(sf::RenderWindow &wnd, sf::Vector2f pos, sf::Vector2f size)
{
    origin = {0.f, 0.f};

    nexa_light.loadFromFile("./resources/Nexa-ExtraLight.ttf");

    // draw background rectangle
    background.setSize(size); // 5% screen height after title and before right side of screen
    background.setPosition(pos);
    background.setFillColor(sf::Color::Black); 

    // create axes
    axes.first.setOutlineColor(sf::Color::White);
    axes.first.setOutlineThickness(1.f);
    axes.first.setFillColor(sf::Color::White);
    axes.second.setOutlineColor(sf::Color::White);
    axes.second.setOutlineThickness(1.f);
    axes.second.setFillColor(sf::Color::White);
    // set positions and sizes in draw function


    // create axis labels
    // t-axis
    axisLabels.first.setString("t");
    axisLabels.first.setCharacterSize(12);
    axisLabels.first.setFillColor(sf::Color::White);
    axisLabels.first.setFont(nexa_light);
    axisLabels.first.setStyle(sf::Text::Bold);
    // positions are set in draw function because graph position and size is initialized to (0,0)
    // E-axis
    axisLabels.second.setString("E");
    axisLabels.second.setCharacterSize(12);
    axisLabels.second.setFillColor(sf::Color::White);
    axisLabels.second.setFont(nexa_light);
    axisLabels.second.setStyle(sf::Text::Bold);
}

void Graph::draw(sf::RenderWindow &wnd)
{
    wnd.draw(background);

    // set the origin once
    if(origin == sf::Vector2f{0.f, 0.f})
                origin = background.getGlobalBounds().getPosition() + sf::Vector2f{-1.f, background.getGlobalBounds().getSize().y - 1.f};

    // t-axis
    axes.first.setSize({background.getGlobalBounds().getSize().x, 0.f});
    axes.first.setOrigin(origin);
    axes.first.setRotation(0.f); // along the bottom of the graph
    axes.first.setPosition(sf::Vector2f{2*origin.x, 2*origin.y} + sf::Vector2f{1.f, 0.f});
    wnd.draw(axes.first);

    // E-axis
    axes.second.setSize({0.f, background.getGlobalBounds().getSize().y});
    axes.second.setPosition(origin - sf::Vector2f{0.f, axes.second.getGlobalBounds().getSize().y - 1.f});
    wnd.draw(axes.second);

    axisLabels.first.setPosition(background.getGlobalBounds().getPosition() 
            + sf::Vector2f{background.getGlobalBounds().getSize().x / 2.f, background.getGlobalBounds().getSize().y + 3.f});
    wnd.draw(axisLabels.first);
    axisLabels.second.setPosition(background.getGlobalBounds().getPosition() 
            + sf::Vector2f{-13.f, background.getGlobalBounds().getSize().y / 2.f - axisLabels.second.getLocalBounds().getSize().y / 2.f});
    wnd.draw(axisLabels.second);

    sf::CircleShape point;
    point.setFillColor(sf::Color::White);
    point.setRadius(1.f);
    point.setPosition(ScreenCoordinates({20.f, 20.f}));
    wnd.draw(point);
}

void Graph::plot()
{
}

sf::Vector2f Graph::ScreenCoordinates(sf::Vector2f graphPos)
{
    // flip the y coordinate so that the top left is the origin with 
    // regular cartesian coordinates y-axis pointing up and then
    // add the origin of the graph in screen coordinates to translate
    return sf::Vector2f{graphPos.x, -graphPos.y} + origin;
}
