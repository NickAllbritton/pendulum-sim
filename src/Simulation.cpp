#include "Simulation.h"

Simulation::Simulation(sf::RenderWindow &window)
    : wnd(window), 
    width(window.getSize().x), height(window.getSize().y),
    menu(window), world(window, wnd.getSize().y * .5f, 1.f)
{
    L = wnd.getSize().y * .5f;
    m = 1.f;
    t = 0.f;
    play = false;
    initialAngle = 8.f * M_PI / 15.f;
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

void Simulation::addSystem(Physics::SolutionMethod method, sf::Vector2f pos)
{
    systems.push_back(Pendulum(world, L, m, pos, method, sf::Color::Cyan));
}

void Simulation::removeSystem(Physics::SolutionMethod method)
{
    // start time over when removing small angle pendulum
    if(method == Physics::SolutionMethod::SmallAngle) t = 0.f; 

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
                Physics::SolutionMethod method = 
                    menu.clickAction(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)); // check if the mouse click hit a button
                if(method != Physics::SolutionMethod::NULLMethod)
                {
                    bool systemCreated = false; // is the system already created
                    for(auto& system : systems)
                    {
                        if(system.method == method) systemCreated = true;
                    }
                    if(systemCreated) removeSystem(method);
                    else addSystem(method, sf::Vector2f{L, initialAngle});
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
    dt = play ? dt : 0.f; // if the sim is not in play, set dt to 0

    if(systems.size() != 0)
    {
        for(auto& sys : systems)
        {
            if(sys.method == Physics::SolutionMethod::SmallAngle)
            {
                sys.setBobPos(Physics::smallAngle(t, sys.getBobPos().x, initialAngle));
            }
            else if(sys.method == Physics::SolutionMethod::Euler)
            {
                // return a std::pair of the values of the position and velocity
                auto theta_sys = Physics::euler(dt, sys.getBobPos(), sys.getBobVel());
                sys.setBobPos(theta_sys.first);
                sys.setBobVel(theta_sys.second);
            }
            else if(sys.method == Physics::SolutionMethod::EulerCromer)
            {
                // return a std::pair of the values of the position and velocity
                auto theta_sys = Physics::eulerCromer(dt, sys.getBobPos(), sys.getBobVel());
                sys.setBobPos(theta_sys.first);
                sys.setBobVel(theta_sys.second);
            }
            else if(sys.method == Physics::SolutionMethod::RungeKutta)
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
