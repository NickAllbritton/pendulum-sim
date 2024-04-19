#include "Simulation.h"


sf::Vector2f polarPos(sf::Vector2f& rect)
{
    float r = std::sqrt(rect.x*rect.x + rect.y*rect.y);
    float theta = (180.f / M_PI) * std::atan(rect.y / rect.x);
    return sf::Vector2f{r, theta};
}

Simulation::Simulation(sf::RenderWindow &window)
    : wnd(window), 
    width(window.getSize().x), height(window.getSize().y),
    menu(window), world(window, wnd.getSize().y * .45, 1.f)
{
    L = wnd.getSize().y * .45;
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
            case sf::Event::Closed:
                wnd.close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Q) wnd.close(); // press q to close the window
                break;
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
