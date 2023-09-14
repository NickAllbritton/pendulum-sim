#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>
#include <boost/numeric/odeint.hpp> // for ODE solvers

#ifndef WORLD_H
#define WORLD_H

class World
{
public:
    World(sf::RenderWindow& wnd); 
    // World = delete; // once the constructor is written delete the default constructor
    ~World() = default;
    void draw(sf::RenderWindow& wnd); // draw the world
private:
    // todo: create a vector of pendulum objects (one for each approximation method)
    sf::RectangleShape background;
    float width;
    float height;
};

#endif