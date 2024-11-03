#include "Indicator.h"

Indicator::Indicator(sf::RenderWindow& wnd, sf::Font& font, Physics::SolutionMethod method, sf::Color color, int index)
{
    this->method = method;

    background.setOutlineThickness(2.f); // thick border
    background.setOutlineColor(color);
    background.setFillColor(sf::Color::Transparent);
    background.setSize({wnd.getSize().x * 0.12f, wnd.getSize().y * 0.1f});

    sf::Vector2f pos = {wnd.getSize().x * 0.03f + (background.getSize().x +9.f) * (index % 2) ,
                        wnd.getSize().y * 0.74f + (background.getSize().y +9.f) * ((index < 2)?0:1)};

    background.setPosition(pos);

    text.setFont(font);
    text.setCharacterSize(background.getSize().y * 0.5f); // 50% of background
    text.setFillColor(color);
    text.setStyle(sf::Text::Bold);
    text.setOutlineThickness(1.f);
    text.setOutlineColor(sf::Color::Black);

    switch(method)
    {
        case Physics::SolutionMethod::SmallAngle:
            text.setString("S-A");
            break;
        case Physics::SolutionMethod::Euler:
            text.setString("E-M");
            break;
        case Physics::SolutionMethod::EulerCromer:
            text.setString("E-C");
            break;
        case Physics::SolutionMethod::RungeKutta:
            text.setString("R-K");
            break;
    }

    text.setPosition({pos.x + background.getSize().x / 2.f - text.getLocalBounds().getSize().x / 2.f,
                    pos.y + text.getLocalBounds().getSize().y / 2.f});
}

void Indicator::draw(sf::RenderWindow& wnd)
{
    wnd.draw(background);
    wnd.draw(text);
}
