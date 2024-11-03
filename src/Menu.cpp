#include "Menu.h"
#include <iostream>

std::string MenuButtonText(MenuOptions button)
{
    switch(button)
    {
        case MenuOptions::PlayPause:
            return "Play";
        case MenuOptions::SmallAngle:
            return "Small angle";
        case MenuOptions::Euler:
            return "Euler method";
        case MenuOptions::EulerCromer:
            return "Euler-Cromer method";
        case MenuOptions::RungeKutta:
            return "Runge-Kutta method";
        case MenuOptions::Reset:
            return "Reset";
        default:
            return "ERROR";    
    }
}

 MenuOptions MenuOptionFromText(std::string text)
{
    if(text == "Play") return MenuOptions::PlayPause;
    else if(text == "Small angle") return MenuOptions::SmallAngle;
    else if(text ==  "Euler method") return MenuOptions::Euler;
    else if(text == "Euler-Cromer method") return MenuOptions::EulerCromer;
    else if(text ==  "Runge-Kutta method") return MenuOptions::RungeKutta;
    else if(text ==  "Reset") return MenuOptions::Reset;
}

Menu::Menu(sf::RenderWindow &wnd)
    : wnd(wnd)
{
    constexpr int nOptions = 6;
    vanilla_rav.loadFromFile("./resources/VanillaRavioli_Demo.ttf"); // load the font

    for(int i = 0; i < nOptions; i++)
    {
        // initialize buttons
        sf::Vector2f pos(wnd.getSize().y * .05, wnd.getSize().y * .2 + (float)i * wnd.getSize().y * .09);
        Button b;

        // use the loop as a means of setting the text properly to each button
        b = Button(wnd, vanilla_rav, sf::Color(18, 188, 148), pos, MenuButtonText(static_cast<MenuOptions>(i)));
        menuOptions.push_back(b);
    }
}

void Menu::draw()
{
    /***********************/
    /*    Draw the title   */
    /***********************/

    title.setFont(vanilla_rav);
	title.setCharacterSize(wnd.getSize().y*.16); // title height is 16% the window height
	title.setFillColor(sf::Color(18, 188, 148));
	title.setString("PendulumSIM");
	// top of the screen with the same padding on the left as the menu buttons
	title.setPosition(sf::Vector2f(wnd.getSize().y * .05, 0.f));
    wnd.draw(title);

    /*************************/
    /* Draw the menu options */
    /*************************/

    for(Button b : menuOptions)
    {
        b.draw(wnd);
    }
}

Physics::SolutionMethod Menu::clickAction(sf::Vector2f mPos)
{
    for(Button& b : menuOptions)
    {
        if(b.mouseClickWithinBounds(mPos)) 
        {
            return b.click();
        }
    }
    return Physics::SolutionMethod::NULLMethod;
}

void Menu::simulateClick(MenuOptions button)
{
    for(Button& b : menuOptions)
    {
        if(b.getText() == MenuButtonText(button)) b.click();
    }
}

MenuOptions Menu::clickNULLMethod(sf::Vector2f mPos)
{
    for(Button& b : menuOptions)
    {
        if(b.mouseClickWithinBounds(mPos)) 
        {
            return MenuOptionFromText(b.getText());
        }
    }
}
