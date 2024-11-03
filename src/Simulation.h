#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "World.h"
#include "Pendulum.h"
#include "FrameTimer.h"
#include "Indicator.h"
#include "Graph.h"

#ifndef SIMULATION_H
#define SIMULATION_H


enum class SystemColors
{
    OceanBlue,
    HotPink,
    ForestGreen,
    BloodRed,
    DeepPurple,
    VibrantYellow
};

class Simulation
{
public:
    Simulation(sf::RenderWindow& window); // pass the window object by reference to the constructor
    Simulation() = delete; // default constructor should NOT be defined
    ~Simulation() = default; // default destructor is fine
    void run(); // run the simulation
    void addSystem(Physics::SolutionMethod method, sf::Vector2f pos, sf::Color randomColor);
    void removeSystem(Physics::SolutionMethod method); 
    sf::Color randomColor();

private:
    void events(); // handle events
    void update(); // simulation logic and physics
    void draw(); // draw the scene/system
    
public:
    float width; // window width (excluding border, etc...)
    float height;
private:
    sf::RenderWindow& wnd; // the simulation object owns a reference to the window handle
    sf::Font nexa_h;
    Menu menu;
    World world; // contains all the objects for the physics and logic
    Graph graph;
    std::vector<Pendulum> systems;  // a dynamic array of pendulum systems that will each have different solving methods
    std::vector<SystemColors> colors;
    std::vector<Indicator> indicators;

    // system variables
    float L; // length of the rod
    float m; // mass of the bob
    bool initial; // true if all systems are ready to evolve from the same rest state or new systems added 
    bool play; // is time evolving
    bool bobRepositioning; // is the bob being moved by the mouse
    bool clickRemovedSystem; // if a click removed a system
    float initialAngle;
    FrameTimer ft; // object to calculate the time of a frame so that times are consistent
    float t; // the newtonian universal time
    float dt; // steps in time
};

#endif