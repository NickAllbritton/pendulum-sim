#include "World.h"

World::World(sf::RenderWindow& wnd)
{
    background.setOutlineColor(sf::Color(18, 188, 148)); // draw an aesthetic outline around the world
    background.setOutlineThickness(2.f);
    background.setFillColor(sf::Color::Black); 

    const float wndWidth = wnd.getSize().x;
    const float wndHeight = wnd.getSize().y;

    // did some algebra for this one. 
    // .05 * wndH = padR                        | we want the padding at the bottom to be the same as on the right
    // .05 * wndH = padRPercent * wndW          | express the padding on the right as a percent of the width
    // .05 * wndH / wndW = padRPercent          | solve for the percent to be used in the width calculation
    const float pRPercent = .05f * wndHeight / wndWidth; 

    // calculate the size of the world
    this->width = wndWidth * (.70-pRPercent); // the 70% space left after the left most of the position minus the percent of the width for
                                             // padding
    this->height = wndHeight * .75; // and the height is 75% of the screen
    background.setSize(sf::Vector2f(width, height));

    // calculate the position of the world space
    auto x = .3 * wndWidth; // 30% the screen space to the right to leave that much space for the menu to the right
    auto y = .2 * wndHeight; // 1/5 the screen space down from the top to leave space for the title
    background.setPosition(sf::Vector2f(x, y));

    
}

void World::draw(sf::RenderWindow& wnd)
{
    // Draw the background
    wnd.draw(background);

    // draw the pendulums

}