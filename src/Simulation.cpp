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
    bobRepositioning = false;
    initial = true;
    initialAngle = 0.f;
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
            case sf::Event::MouseButtonReleased:
                if(bobRepositioning) 
                {
                    bobRepositioning = false;
                    for(auto& sys : systems)
                    {
                        // save the mouse position in world coordinates (cartesian)
                        auto mousePos = World::WorldPos(world, sf::Vector2f{(float)event.mouseButton.x, (float)event.mouseButton.y});
                        // find the difference vector between mousePos and (0, L) (polar origin)
                        auto diff = mousePos - sf::Vector2f{0, L};
                        // calculate the angle of this vector using trig
                        // NOTE: x and y are swapped due to x being the opposite side length
                        // and that y is negated because the resulting trig is upside down of 
                        // standard trig as it is expected by devs who wrote std::atan, for example
                        // if the release position is above the origin of the polar system (0, L)
                        // the subtraction of the cartesian origin does not create an upside down triangle
                        // the negation of the y coordinate thus has the effect of swinging the angle around
                        // by pi. adding another pi puts it in the correct place, if so
                        float angle = (mousePos.y >= L) ? std::atan(diff.x / -diff.y) + M_PI : std::atan(diff.x / -diff.y);
                        sys.setBobPos(sf::Vector2f{L, angle});

                        // reset initial conditions relevant for accurate physics
                        sys.setBobVel(sf::Vector2f{0.f, 0.f}); 
                        initialAngle = angle;
                        t = 0;
                    }
                }
                break;
            case sf::Event::MouseButtonPressed:
                // TODO: indicate that the system is not in an initial state so that the user isn't confused 
                // that adding new pendulums does nothing besides change the color of the menu button clicked
                // Due to the structure of the program, I'm not sure how to do that right now
                Physics::SolutionMethod method = 
                    menu.clickAction(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)); // check if the mouse click hit a button
                if(method != Physics::SolutionMethod::NULLMethod)
                {
                    bool systemCreated = false; // is the system already created
                    for(auto& system : systems)
                    {
                        if(system.method == method) systemCreated = true;
                    }
                    if(systemCreated) removeSystem(method);
                    else if(initial) addSystem(method, sf::Vector2f{L, initialAngle});
                }
                else
                {
                    // first check if click was within the world
                    if(world.withinWorld(sf::Vector2f{(float)event.mouseButton.x, (float)event.mouseButton.y}))
                    {
                        for(auto& sys : systems)
                        {
                            if(sys.onBob(World::WorldPos(world, sf::Vector2f{(float)event.mouseButton.x, (float)event.mouseButton.y})))
                            {
                                // set the bobRepositioning state true
                                bobRepositioning = true;
                            }
                        }
                    }
                    else // if it is not then evaluate whether a menu button was clicked
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
                }
                break;
        }
    }
}

void Simulation::update()
{
    dt = ft.frame(); // calculate the time between frames
    dt = play ? dt : 0.f; // if the sim is not in play, set dt to 0

    if(!play)
    {
        for(auto& sys : systems)
        {
            // check that each system is still in the initial state
            if(sys.getBobPos().y != initialAngle) initial = false; 
        }
    }

    if(play && !bobRepositioning && systems.size() != 0) //evolve the system
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
                // approximate the system using Euler-Cromer method
            }
            else if(sys.method == Physics::SolutionMethod::RungeKutta)
            {
                // approximate the system using Runge-Kutta method
            }
        }
        t += dt;
    }
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
