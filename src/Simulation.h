#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "World.h"
#include "Pendulum.h"

#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation
{
public:
    Simulation(sf::RenderWindow& window); // pass the window object by reference to the constructor
    Simulation() = delete; // default constructor should NOT be defined
    ~Simulation() = default; // default destructor is fine
    void run(); // run the simulation
    void addSystem(SolutionMethod method);
    void removeSystem(SolutionMethod method); 

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
    World world; // contains all the objects for the physics and logic
    sf::Text clicked;
    sf::Font font;
    std::vector<Pendulum> systems;  // a dynamic array of pendulum systems that will each have different solving methods

    // system variables
    float L; // length of the rod
    float m; // mass of the bob
    bool play; // is time evolving
    float initialAngle;
    float t; // time variable
    float dt; // steps in time
};

#endif