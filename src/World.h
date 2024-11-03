#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>
// #include <vector>
// #include <boost/numeric/odeint.hpp> // for ODE solvers

#ifndef WORLD_H
#define WORLD_H

class World
{
public:
    World(sf::RenderWindow& wnd, float length, float mass); 
    // World = delete; // once the constructor is written delete the default constructor
    ~World() = default;
    void draw(sf::RenderWindow& wnd); // draw the world
    bool withinWorld(sf::Vector2f globalPos) const;
    // allow outside functions to use a world object to define their drawable's positions
    static sf::Vector2f ScreenPos(World& world, sf::Vector2f worldPos)
    {
        return world.screenPos(worldPos);
    }
    static sf::Vector2f WorldPos(World& world, sf::Vector2f screenPos)
    {
        return world.worldPos(screenPos);
    }
private:
    // TODO: alternative to this solution use a sf::View to handle world coordinates
    // return the screen position of every position in the world coordinates
    sf::Vector2f screenPos(sf::Vector2f worldPos) const
    {
        // assume worldPos is relative to the origin of the world coordinates, of course
        // Following the simplest convention in mechanics we set the origin of our world coordinates to the point of
        // minimum potential energy
        sf::Vector2f origin(background.getGlobalBounds().getPosition().x + width / 2.f,
                            background.getGlobalBounds().getPosition().y + height - 0.2f*L);
        return origin + sf::Vector2f{worldPos.x, -worldPos.y}; // minus the y because negative y-values in screen space mean moving up
    }
    sf::Vector2f worldPos(sf::Vector2f screenPos) const
    {
        sf::Vector2f worldOrigin(background.getGlobalBounds().getPosition().x + width / 2.f,
                            background.getGlobalBounds().getPosition().y + height - 0.2f*L);
        return sf::Vector2f{(screenPos - worldOrigin).x, -(screenPos - worldOrigin).y};
    }
private:
    sf::RectangleShape background;
    sf::RectangleShape x_axis;
    std::vector<sf::RectangleShape> x_ticks; // tick marks on the x-axis
    std::vector<sf::RectangleShape> y_ticks; // you can figure it out
    sf::RectangleShape y_axis;
    std::vector<sf::Text> tick_xlabels; // tick labels for the x-axis
    std::vector<sf::Text> tick_ylabels; // tick labels for the y-axis
    float width;
    float height;
    const float L; // the length of the pendulum in world space
    const float m; // mass of the bob
public:
    sf::Font nexaLight; // font for tick marks and other data displayed
};

#endif