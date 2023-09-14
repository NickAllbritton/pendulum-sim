#include "Menu.h"

Menu::Menu(sf::RenderWindow &wnd)
    : wnd(wnd)
{
    vanilla_rav.loadFromFile("./resources/VanillaRavioli_Demo.ttf"); // load the font
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
}
