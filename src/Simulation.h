#include <SFML/Graphics.hpp>
#include "Menu.h"

#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation
{
public:
    Simulation(sf::RenderWindow& window); // pass the window object by reference to the constructor
    Simulation() = delete; // default constructor should NOT be defined
    ~Simulation() = default; // default destructor is fine
    void run(); // run the simulation

private:
    void events(); // handle events
    void update(); // simulation logic and physics
    void draw(); // draw the scene/system

public:
    float width; // window width (excluding border, etc...)
    float height;
private:
    sf::RenderWindow& wnd; // the simulation object owns a reference to the window handle
    Menu menu;
};

#endif