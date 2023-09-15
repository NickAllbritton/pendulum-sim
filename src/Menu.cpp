#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow &wnd)
    : wnd(wnd)
{
    constexpr int nOptions = 6;
    vanilla_rav.loadFromFile("./resources/VanillaRavioli_Demo.ttf"); // load the font

    for(int i = 0; i < nOptions; i++)
    {
        // initialize buttons
        sf::Vector2f pos(30.f, 200.f + (float)i * 50.f);
        Button b;

        // use the loop as a means of setting the text properly to each button
        switch(static_cast<MenuOptions>(i))
        {
            case MenuOptions::PlayPause:
                b = Button(wnd, vanilla_rav, sf::Color(18, 188, 148), pos, "Play");
                break;
            case MenuOptions::SmallAngle:
                b = Button(wnd, vanilla_rav, sf::Color(18, 188, 148), pos, "Small angle");
                break;
            case MenuOptions::Euler:
                b = Button(wnd, vanilla_rav, sf::Color(18, 188, 148), pos, "Euler method");
                break;
            case MenuOptions::EulerCromer:
                b = Button(wnd, vanilla_rav, sf::Color(18, 188, 148), pos, "Euler-Cromer method");
                break;
            case MenuOptions::RungeKutta:
                b = Button(wnd, vanilla_rav, sf::Color(18, 188, 148), pos, "Runge-Kutta method");
                break;
            case MenuOptions::About:
                b = Button(wnd, vanilla_rav, sf::Color(18, 188, 148), pos, "About");
                break;    
        }
        menuOptions.push_back(b);
    }
}

void Menu::draw()
{
    /***********************/
    /*    Draw the title   */
    /***********************/

    title.setFont(vanilla_rav);
	title.setCharacterSize(120.f);
	title.setFillColor(sf::Color(18, 188, 148));
	title.setString("PendulumSIM");
	// for the x:
	// divide the window width in half and subtract half the length of the title
	// for the y:
	// hardcoded for now... TODO: change the y to a dynamic value
	title.setPosition(sf::Vector2f(wnd.getSize().x / 2.f - title.getLocalBounds().width / 2.f, 5.f));
    wnd.draw(title);

    /*************************/
    /* Draw the menu options */
    /*************************/

    for(Button b : menuOptions)
    {
        b.draw(wnd);
    }
}

void Menu::clickAction(sf::Vector2f mPos)
{
    
    for(Button& b : menuOptions)
    {
        if(b.mouseClickWithinBounds(mPos)) 
        {
            b.click();
        }
    }
}
