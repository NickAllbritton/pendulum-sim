#include <cmath>
#include "Pendulum.h"

Bob::Bob(float mass, sf::Vector2f pos, sf::Color c)
{
    this->pos = pos;
    r = 25.f; // TODO: give a dynamic calculation so that larger mass has a larger radius
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

Pendulum::Pendulum(World& world, float length, float mass, sf::Vector2f bobPos, sf::Color bobC)
    : bob(mass, bobPos, bobC)
{
    L = length;

    rod.setSize({ 0.f,length });
    rod.setOutlineColor(sf::Color(25, 25, 25)); // dark grey
    rod.setFillColor(sf::Color::White);
    rod.setOutlineThickness(2.f);

    // TODO: rotate the pendulum into position in case bobPos is initially not the origin
    // rod.setOrigin(World::ScreenPos(world, sf::Vector2f{0.f, length - 2.f}));
    rod.setPosition(World::ScreenPos(world, sf::Vector2f{0.f, L - 2.f}));
    rod.setRotation((180.f / M_PI) * -std::asin(bob.getPos().x / L));
}

void Pendulum::draw(sf::RenderWindow &wnd, World& world)
{
    // TODO: always rotate the pendulum into position before drawing
    // for some reason this rotation code and the code in the constructor does not work
    // it doesn't display the rod at all
    // rod.setOrigin(World::ScreenPos(world, sf::Vector2f{0.f, L - 2.f}));
    rod.setPosition(World::ScreenPos(world, sf::Vector2f{0.f, L - 2.f}));
    rod.setRotation((180.f / M_PI) * -std::asin(bob.getPos().x / L));

    wnd.draw(rod);
    bob.draw(wnd, world);
}
