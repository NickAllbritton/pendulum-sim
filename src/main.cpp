#include "Simulation.h"

int main()
{
    // Release
    // create the window object with the end-user's first available full screen mode
    // note: the title "PendulumSim" will not be displayed in full screen mode. 
    // auto wnd = sf::RenderWindow{ sf::VideoMode::getFullscreenModes().at(0), "PendulumSim", sf::Style::Fullscreen };

    // Debug
    auto wnd = sf::RenderWindow{ {1500u, 800u}, "PendulumSim"};


    // holding down a key does not send repeated window events
    wnd.setKeyRepeatEnabled(false);

    // the following line was in the example code to set the framerate limit
    // wnd.setFramerateLimit(144);
    // TODO: We should discuss how to manage our time efficiently. C++ can be a fast language, but the problem remains:
    // We need to 1) Calculate the position of our bob and 2) Draw it. 
    // The more complex our code becomes the more time management matters

    Simulation sim(wnd);

    while (wnd.isOpen()) sim.run(); // every frame that the window is open, run the sim

    return 0;
}