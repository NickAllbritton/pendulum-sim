#include "World.h"

World::World(sf::RenderWindow& wnd)
{
    background.setOutlineColor(sf::Color(18, 188, 148)); // draw an aesthetic outline around the world
    background.setOutlineThickness(2.f);
    background.setFillColor(sf::Color::Black); 

    // calculate the size of the world
    // TODO: define the world width as the leftover space after the menu options are drawn to the left
    this->width = wnd.getSize().x / 2; // for now the width should be half the window width
    this->height = wnd.getSize().y - 200.f;
    background.setSize(sf::Vector2f(width, height));

    // calculate the position of the world space
    // for now the x position of the box should be in the middle of the screen (moved a little to the left)
    auto x = wnd.getSize().x / 2 - 10.f; 
    auto y = 180.f;

    // TODO: change the y position from a hard-coded value potentially
    background.setPosition(sf::Vector2f(x, y));
}

void World::draw(sf::RenderWindow& wnd)
{
    // Draw the background
    wnd.draw(background);

    // draw the pendulums

}