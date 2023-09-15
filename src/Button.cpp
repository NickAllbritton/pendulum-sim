#include "Button.h"
#include <iostream>

Button::Button(sf::RenderWindow &wnd, sf::Font& font, sf::Color c, sf::Vector2f pos, std::string str, float w, float h)
{
    text.setCharacterSize(30.f);
    text.setFillColor(c);
    text.setFont(font);
    text.setPosition(pos);
    text.setString(str);

    // if the width and height are 0, that means automatically calculate the width and height
    width = (w > 0.f) ? w : text.getLocalBounds().width;
    height = (h > 0.f) ? h : text.getLocalBounds().height;
    this->pos = pos;
    this->c = c;
    state = false;
}

Button::Button(sf::RenderWindow &wnd, sf::Font& font, sf::Color c, sf::Vector2f pos, std::string str, const sf::Vector2f &size)
    : Button(wnd, font, c, pos, str, size.x, size.y) // call the first constructor
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

bool Button::mouseClickWithinBounds(sf::Vector2f mPos)
{
    // it seems like the mouse value that is returned by the OS is not the TIP of the mouse
    // pointer. Therefore, I will offset mPos to make more since

    mPos = mPos - sf::Vector2f(4.f, 7.f);
    return (mPos.x < pos.x + width) && (mPos.x > pos.x)
            && (mPos.y < pos.y + height) && (mPos.y > pos.y);
}