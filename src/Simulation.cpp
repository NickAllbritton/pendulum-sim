#include "Simulation.h"
#include <random>

MenuOptions MenuOptionFromMethod(Physics::SolutionMethod meth)
{
    switch(meth)
    {
        case Physics::SolutionMethod::SmallAngle:
            return MenuOptions::SmallAngle;
        case Physics::SolutionMethod::Euler:
            return MenuOptions::Euler;
        case Physics::SolutionMethod::EulerCromer:
            return MenuOptions::EulerCromer;
        case Physics::SolutionMethod::RungeKutta:
            return MenuOptions::RungeKutta;
        // this last case feels strange.... probably a way to make this more clean
        case Physics::SolutionMethod::NULLMethod:
            return MenuOptions::Reset;
    }
    return MenuOptions::Reset; // this line will not be reached but shuts up compiler warning
}

sf::Color returnSystemColor(SystemColors color)
{
    switch(color)
    {
        case SystemColors::OceanBlue:
            return sf::Color(7, 31, 215);
        case SystemColors::HotPink:
            return sf::Color(255, 23, 91);
        case SystemColors::ForestGreen:
            return sf::Color(15, 123, 21);
        case SystemColors::BloodRed:
            return sf::Color(249, 14, 13);
        case SystemColors::DeepPurple:
            return sf::Color(101, 17, 114);
        case SystemColors::VibrantYellow:
            return sf::Color(244, 226, 0);
    }
    return sf::Color(0, 0, 0); // this line will never be reached but shuts up annoying warning
}

Simulation::Simulation(sf::RenderWindow &window)
    : wnd(window), 
    width(window.getSize().x), height(window.getSize().y),
    menu(window), world(window, wnd.getSize().y * .29f, 1.f)
{
    L = wnd.getSize().y * .29f;
    m = 1.f;
    t = 0.f;
    play = false;
    bobRepositioning = false;
    initial = true;
    clickRemovedSystem = false;
    initialAngle = 0.f;
    ft = FrameTimer();

    systems = std::vector<Pendulum>(0);
    colors = std::vector<SystemColors>(0);
    indicators = std::vector<Indicator>(0);
}

sf::Color Simulation::randomColor()
{
    std::random_device dev; // seed for mersenne twister algorithm
    std::mt19937 rng( dev() );
    std::uniform_int_distribution<> dist(0, 5);
    int rand_color;
    bool noMatch;

    do
    {
        rand_color = dist(rng); // generate random int [0, 5]
        noMatch = true; // initially there is no match, of course
        for(auto& color : colors)
        {
            // if a color is matched, noMatch is false
            if(static_cast<SystemColors>(rand_color) == color) noMatch = false;
        }
    } while (!noMatch); // if there was a match, loop again
    
    colors.push_back(static_cast<SystemColors>(rand_color));

    return returnSystemColor(static_cast<SystemColors>(rand_color));
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

void Simulation::addSystem(Physics::SolutionMethod method, sf::Vector2f pos, sf::Color randColor)
{
    systems.push_back(Pendulum(world, L, m, pos, method, randColor));
    indicators.push_back(Indicator(wnd, world.nexaLight, method, randColor, systems.size() - 1));
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
    // create new vector to copy all but system/color to remove into
    std::vector<Pendulum> temp_sys = std::vector<Pendulum>(0);
    std::vector<SystemColors> temp_colors = std::vector<SystemColors>(0);
    std::vector<Indicator> temp_indicators = std::vector<Indicator>(0);
    for(int i = 0; i < systems.size(); i++)
    {
        if(i == index_remove) continue;
        else 
        {
            temp_sys.push_back(systems.at(i));
            temp_colors.push_back(colors.at(i));
            temp_indicators.push_back(indicators.at(i));
        }
    }
    systems.clear();
    colors.clear();
    indicators.clear();
    systems = temp_sys;
    colors = temp_colors;
    indicators = temp_indicators;
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
                else
                {
                    // determine what button the mouse is hovering over when button released
                    MenuOptions action = menu.clickNULLMethod(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y));
                    // if the initial click was over button that needs to be unclicked then simulate a click
                    if(action == MenuOptions::Reset) menu.simulateClick(action); // click reset back
                    else // click buttons for solution methods back (if attempt to create in noninitial state)
                    {
                        for(int i = 1; i < 5; i++)
                        {
                            // if the action matches a solution method and the system is non-initial
                            if(action == MenuOptionFromMethod(static_cast<Physics::SolutionMethod>(i)) && !initial) 
                            {
                                bool match = false; // is there a match
                                for(auto& sys : systems)
                                {
                                    // if you find a match, match is true
                                    if(sys.method == static_cast<Physics::SolutionMethod>(i)) match = true;
                                }
                                // if there is no system, undo the click
                                // because if the button is clicked for a system that has not been made yet
                                // and the state of the sim is non-initial, the button should not stay highlighted
                                if(!match && !clickRemovedSystem) menu.simulateClick(action); 
                                i = 4; // exit loop
                            }
                        }
                    }
                }
                if(clickRemovedSystem) clickRemovedSystem = false; // reset 
                break;
            case sf::Event::MouseButtonPressed:
                Physics::SolutionMethod method = 
                    menu.clickAction(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)); // check if the mouse click hit a button
                if(method != Physics::SolutionMethod::NULLMethod)
                {
                    bool systemCreated = false; // is the system already created
                    for(auto& system : systems)
                    {
                        if(system.method == method) systemCreated = true;
                    }
                    if(systemCreated) 
                    {
                        removeSystem(method);
                        clickRemovedSystem = true;
                    }
                    else if(initial) addSystem(method, sf::Vector2f{L, initialAngle}, randomColor());
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
                            // toggle play
                            play = !play;
                        }
                        else if(action == MenuOptions::Reset)
                        {
                            // put the sim back into an initial state with all the systems still included
                            if(play)
                            {
                                play = false;
                                menu.simulateClick(MenuOptions::PlayPause);
                            }
                            t = 0;
                            for(auto& sys : systems)
                            {
                                sys.setBobVel({0.f, 0.f});
                                sys.setBobPos({L, 0.f});
                            }
                            initialAngle = 0.f;
                            initial = true;
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

    if(systems.size() != 0)
    {
        for(auto& sys : systems)
        {
            // check if any system is not in the initial state
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
    menu.draw(); 
    world.draw(wnd);
    if(systems.size() != 0 && indicators.size() != 0)
    {
        for(auto& system : systems)
        {
            system.draw(wnd, world);
        }
        for(auto& indic : indicators)
        {
            indic.draw(wnd);
        }
    }
}
