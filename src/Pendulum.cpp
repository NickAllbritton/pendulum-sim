#include <cmath>
#include "Pendulum.h"

Bob::Bob(float mass, sf::Vector2f pos, sf::Color c)
{
    this->pos = pos;
    r = 15.f; // TODO: give a dynamic calculation so that larger mass has a larger radius
    img.setFillColor(c);
    img.setRadius(r);
    img.setOutlineColor(c); // dark grey
    img.setOutlineThickness(1.f);
}

void Bob::draw(sf::RenderWindow &wnd, World& world)
{
    img.setOrigin({img.getLocalBounds().getSize().x / 2.f, img.getLocalBounds().getSize().y / 2.f});
    img.setPosition(World::ScreenPos(world, pos));
    wnd.draw(img);
}

Pendulum::Pendulum(World& world, float length, float mass, sf::Vector2f bobPos, SolutionMethod method, sf::Color bobC)
    : bob(mass, bobPos, bobC), method(method), L(length)
{
    rod.setSize({ 1.f,length });
    rod.setOutlineColor(sf::Color::White); 
    rod.setFillColor(sf::Color(25, 25, 25)); // dark grey
    rod.setOutlineThickness(1.f);

    // TODO: rotate the pendulum into position in case bobPos is initially not the origin
    // rod.setOrigin(World::ScreenPos(world, sf::Vector2f{0.f, length - 2.f}));
    rod.setPosition(World::ScreenPos(world, sf::Vector2f{0.f, L}));
    rod.setRotation((180.f / M_PI) * -std::asin(bob.getPos().x / L));
}

void Pendulum::draw(sf::RenderWindow &wnd, World& world)
{
    rod.setPosition(World::ScreenPos(world, sf::Vector2f{0.f, L}));
    rod.setRotation((180.f / M_PI) * -std::asin(bob.getPos().x / L));

    wnd.draw(rod);
    bob.draw(wnd, world);
}
