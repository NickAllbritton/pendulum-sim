#include "Graph.h"

Graph::Graph(sf::RenderWindow &wnd, sf::Vector2f pos, sf::Vector2f size)
{
    origin = {0.f, 0.f};
    points = std::vector<std::pair<sf::CircleShape, Physics::SolutionMethod>>(0);

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

    for(auto& point : points)
    {
        wnd.draw(point.first);
    }
}

void Graph::plot(float t, float E, float L, Physics::SolutionMethod meth, sf::Color c)
{
    // the entire t-axis is 3 min or 180 seconds
    float t_coord = t * background.getGlobalBounds().getSize().x / 180.f;
    // the entire E-axis is 2.6mgL (with m = 1)
    float E_coord = E * background.getGlobalBounds().getSize().y / (2.2f * Physics::g * L);

    sf::CircleShape pt;
    pt.setFillColor(c);
    pt.setRadius(1.f);
    pt.setPosition(ScreenCoordinates({t_coord, E_coord}));

    // add the point to the points
    points.push_back({pt, meth});
}

void Graph::deletePoints(Physics::SolutionMethod method)
{
    if(points.size() != 0)
    {
        std::vector<std::pair<sf::CircleShape, Physics::SolutionMethod>> tmp_points;
        for(int i = 0; i < points.size(); i++)
        {
            if(points.at(i).second == method) continue; // do not add the points corresponding to the target
            else tmp_points.push_back(points.at(i)); // add all others
        }
        points = tmp_points; // replace the points with only the points that were not removed
    }
}

sf::Vector2f Graph::ScreenCoordinates(sf::Vector2f graphPos)
{
    // flip the y coordinate so that the top left is the origin with 
    // regular cartesian coordinates y-axis pointing up and then
    // add the origin of the graph in screen coordinates to translate
    return origin - sf::Vector2f{graphPos.x, graphPos.y};
}
