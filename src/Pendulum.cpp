#include <cmath>
#include "Pendulum.h"

// DO NOT USE THIS FUNCTION. arcsin is not ideal for calculating angles
sf::Vector2f polarPos(const sf::Vector2f& rect)
{
    float r = (rect.x*rect.x+rect.y*rect.y) / (2.f * rect.y);
    float theta = std::asin(rect.x / r);
    return sf::Vector2f{r, theta};
}

sf::Vector2f rectPos(const sf::Vector2f& polar)
{
    // polar.y = theta --- the angle measured from the vertical
    // polar.x = r --- the distance from (0, L)
    float x = polar.x * std::sin(polar.y);
    float y = polar.x - polar.x * std::cos(polar.y);
    return sf::Vector2f{x, y};
}


Bob::Bob(float mass, sf::Vector2f pos, sf::Color c)
{
    this->pos = pos;
    vel = sf::Vector2f{0.f, 0.f};
    r = 15.f; // TODO: give a dynamic calculation so that larger mass has a larger radius
    img.setFillColor(c);
    img.setRadius(r);
    img.setOutlineColor(c); // dark grey
    img.setOutlineThickness(1.f);
}

void Bob::draw(sf::RenderWindow &wnd, World& world)
{
    img.setOrigin({img.getLocalBounds().getSize().x / 2.f, img.getLocalBounds().getSize().y / 2.f});
    img.setPosition(World::ScreenPos(world, rectPos(pos)));
    wnd.draw(img);
}

Pendulum::Pendulum(World& world, float length, float mass, sf::Vector2f bobPos, Physics::SolutionMethod method, sf::Color bobC)
    : bob(mass, bobPos, bobC), method(method), L(length)
{
    rod.setSize({ 1.f,length });
    rod.setOutlineColor(sf::Color::White); 
    rod.setFillColor(sf::Color(25, 25, 25)); // dark grey
    rod.setOutlineThickness(1.f);

    // TODO: rotate the pendulum into position in case bobPos is initially not the origin
    rod.setPosition(World::ScreenPos(world, sf::Vector2f{0.f, L}));
    // convert the bobPos.y (theta) into degrees and flip the sign due to SFML standards
    rod.setRotation((180.f / M_PI) * -bobPos.y);
}

void Pendulum::draw(sf::RenderWindow &wnd, World& world)
{
    rod.setPosition(World::ScreenPos(world, sf::Vector2f{0.f, L}));
    // convert the bobPos.y (theta) into degrees and flip the sign due to SFML standards
    rod.setRotation((180.f / M_PI) * -bob.getPos().y);

    wnd.draw(rod);
    bob.draw(wnd, world);
}

bool Pendulum::onBob(sf::Vector2f mousePos)
{
    // assume mousePos is in world coordinates
    // bob position is from center of bob
    bool onBobVar = mousePos.x >= rectPos(bob.getPos()).x - bob.getRadius() / 2.f && 
            mousePos.x <= rectPos(bob.getPos()).x + bob.getRadius() / 2.f &&
            mousePos.y >= rectPos(bob.getPos()).y - bob.getRadius() / 2.f && 
            mousePos.y <= rectPos(bob.getPos()).y + bob.getRadius() / 2.f;
    return onBobVar;
}
