#include "Simulation.h"

Simulation::Simulation(sf::RenderWindow &window)
    : wnd(window), 
    width(window.getSize().x), height(window.getSize().y),
    menu(window), world(window, wnd.getSize().y * .45f, 1.f)
{
    L = wnd.getSize().y * .45f;
    m = 1.f;
    t = 0.f;
    dt = 0.001f;
    play = false;
    initialAngle = M_PI / 4.f;
    ft = FrameTimer();

    systems = std::vector<Pendulum>(0);
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

void Simulation::addSystem(SolutionMethod method)
{
    systems.push_back(Pendulum(world, L, m, sf::Vector2f{L, M_PI / 4.f}, method, sf::Color::Cyan));
}

void Simulation::removeSystem(SolutionMethod method)
{
    int index_remove;
    // find the index of the system to remove
    for(int i = 0; i < systems.size(); i++)
    {
        if(systems.at(i).method == method) index_remove = i;
    }
    // create new vector to copy all but system to remove into
    std::vector<Pendulum> temp_sys = std::vector<Pendulum>(0);
    for(int i = 0; i < systems.size(); i++)
    {
        if(i == index_remove) continue;
        else temp_sys.push_back(systems.at(i));
    }
    systems.clear();
    systems = temp_sys;
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
                SolutionMethod method = 
                    menu.clickAction(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)); // check if the mouse click hit a button
                if(method != SolutionMethod::NULLMethod)
                {
                    bool systemCreated = false; // is the system already created
                    for(auto& system : systems)
                    {
                        if(system.method == method) systemCreated = true;
                    }
                    if(systemCreated) removeSystem(method);
                    else addSystem(method);
                }
                else
                {
                    MenuOptions action = menu.clickNULLMethod(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                    if(action == MenuOptions::PlayPause)
                    {
                        play = !play;
                    }
                    else
                    {
                        //TODO: Display about page.... 
                    }
                }
                break;
        }
    }
}

void Simulation::update()
{
    dt = ft.frame(); // calculate the time between frames

    if(systems.size() != 0)
    {
        for(auto& sys : systems)
        {
            if(sys.method == SolutionMethod::SmallAngle)
            {
                sys.setBobPos(smallAngle(t, sys.getBobPos().x, initialAngle));
            }
            else if(sys.method == SolutionMethod::Euler)
            {
                // approximate the system using Euler method
            }
            else if(sys.method == SolutionMethod::EulerCromer)
            {
                // approximate the system using Euler-Cromer method
            }
            else if(sys.method == SolutionMethod::RungeKutta)
            {
                // approximate the system using Runge-Kutta method
            }
        }
    }

    if(play) t += dt; // update the time if the game is in play
}

void Simulation::draw()
{
    // TODO: draw all the things
    menu.draw(); 
    world.draw(wnd);
    if(systems.size() != 0)
    {
        for(auto& system : systems)
        {
            system.draw(wnd, world);
        }
    }
}
