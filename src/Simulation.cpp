#include "Simulation.h"

Simulation::Simulation(sf::RenderWindow &window)
    : wnd(window), 
    width(window.getSize().x), height(window.getSize().y),
    menu(window), world(window, wnd.getSize().y * .5, 1.f)
{
    L = wnd.getSize().y * .5;
    m = 1.f;
    systems = std::vector<Pendulum>(0);
    float x = -L/5.f;
    float y = L - std::sqrt(L*L - x*x);
    systems.push_back(Pendulum(world, L, m, sf::Vector2f(x, y), sf::Color::Magenta));
}

void Simulation::run()
{
    // first check for window events to handle
    events();

    // next update the system
    update();

    // clear the screen from previous frame's drawing
    wnd.clear(sf::Color(32, 27, 32)); // background is a deep grey
    // draw the system
    draw();
    wnd.display(); // display the window
}

void Simulation::events()
{
    // loop through each window event created and then handle it 
    for (auto event = sf::Event{}; wnd.pollEvent(event);)
    {
        switch(event.type)
        {
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Q) wnd.close(); // press q to close the window
            case sf::Event::MouseButtonPressed:
                menu.clickAction(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)); // check if the mouse click hit a button
            break;
        }
    }
}

void Simulation::update()
{
    // TODO: do physics
}

void Simulation::draw()
{
    // TODO: draw all the things
    menu.draw(); 
    world.draw(wnd);
    for(auto& system : systems)
    {
        system.draw(wnd, world);
    }
}
