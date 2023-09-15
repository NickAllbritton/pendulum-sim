#include "Menu.h"

Menu::Menu(sf::RenderWindow &wnd)
    : wnd(wnd)
{
    constexpr int nOptions = 6;
    vanilla_rav.loadFromFile("./resources/VanillaRavioli_Demo.ttf"); // load the font

    for(int i = 0; i < nOptions; i++)
    {
        // initialize buttons
        // TODO: give the proper initial values
        sf::Vector2f pos(30.f, 200.f + (float)i * 30.f);
        Button b(wnd, vanilla_rav, sf::Color(18, 188, 148), pos);

        // use the loop as a means of setting the text properly to each button
        switch(static_cast<MenuOptions>(i))
        {
            case MenuOptions::PlayPause:
                // if the button has been pressed display "Pause"
                // if it has not been pressed display "Play"
                // TODO: this is not the place for such logic. once the button is clicked, it won't change
                // because the constructor is not called every frame. that means this logic is pointless
                // but keep it to refactor later!
                b.setText(b.state ? "Pause" : "Play");
                break;
            case MenuOptions::SmallAngle:
                b.setText("Small angle (analytical approximation)");
                break;
            case MenuOptions::Euler:
                b.setText("Euler method (numerical approximation)");
                break;
            case MenuOptions::EulerCromer:
                b.setText("Euler-Cromer method (numerical approximation)");
                break;
            case MenuOptions::RungeKutta:
                b.setText("Runge-Kutta method (numerical approximation)");
                break;
            case MenuOptions::About:
                b.setText("About");
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
	title.setPosition(sf::Vector2f(wnd.getSize().x / 2.f - title.getLocalBounds().width / 2.f - 200.f, 5.f));
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
    for(Button b : menuOptions)
    {
        if(b.mouseClickWithinBounds(mPos)) b.click();
    }
}
