#include "Button.h"

Button::Button(sf::RenderWindow &wnd, sf::Font& font, sf::Color c, sf::Vector2f pos, float w, float h)
{
    text.setCharacterSize(20.f);
    text.setFillColor(c);
    text.setFont(font);
    text.setPosition(pos);

    // if the width and height are 0, that means automatically calculate the width and height
    width = (w > 0.f) ? w : text.getLocalBounds().width;
    height = (h > 0.f) ? h : text.getLocalBounds().height;
    this->pos = pos;
    this->c = c;
    state = false;
}

Button::Button(sf::RenderWindow &wnd, sf::Font& font, sf::Color c, sf::Vector2f pos, const sf::Vector2f &size)
    : Button(wnd, font, c, pos, size.x, size.y) // call the first constructor
{
}

void Button::draw(sf::RenderWindow &wnd)
{
    // to test the clicking methods
    if(state) text.setFillColor(sf::Color::Magenta);
    else text.setFillColor(c); // restore default

    // draw the button
    wnd.draw(text);
}

void Button::setText(std::string t)
{
    text.setString(t);
}

void Button::click()
{
    // toggle state
    state = !state;
}

bool Button::mouseClickWithinBounds(sf::Vector2f pos)
{
    return pos.x < this->pos.x + width && pos.x > this->pos.x
            && pos.y < this->pos.y + height && pos.y > this->pos.y;
}