#include <SFML/Graphics.hpp>
#include "World.h"
#include "Physics.h"

#ifndef PENDULUM_H
#define PENDULUM_H

sf::Vector2f polarPos(const sf::Vector2f& rect);
sf::Vector2f rectPos(const sf::Vector2f& polar);

// not a dude. it's what you call the ball at the tip of the pendulum
class Bob
{
public:
    Bob(float mass, sf::Vector2f pos, sf::Color c);
    Bob() = default;
    ~Bob() = default;
    void draw(sf::RenderWindow& wnd, World& world);
    const sf::Vector2f getPos() const
    {
        return pos;
    }
    const sf::Vector2f& setPos(const sf::Vector2f& newPos)
    {
        return pos = newPos;
    }
    const float getRadius() const
    {
        return r;
    }
    const sf::Vector2f getVel() const
    {
        return vel;
    }
    const sf::Vector2f& setVel(const sf::Vector2f& newVel)
    {
        return vel = newVel;
    }
private:
    sf::Vector2f pos; // position of the bob in polar coordinates
    sf::Vector2f vel;
    float r; // the radius
    sf::CircleShape img;
};


class Pendulum
{
public:
    Pendulum(World& world, float length, float mass, sf::Vector2f bobPos, Physics::SolutionMethod method, sf::Color bobC);
    Pendulum() = default;
    ~Pendulum() = default;
    void draw(sf::RenderWindow& wnd, World& world);
    bool onBob(sf::Vector2f mousePos);
    const sf::Vector2f getBobPos() const
    {
        return bob.getPos();
    }
    const sf::Vector2f& setBobPos(const sf::Vector2f& newPos)
    {
        return bob.setPos(newPos);
    }
    const sf::Vector2f getBobVel() const
    {
        return bob.getVel();
    }
    const sf::Vector2f& setBobVel(const sf::Vector2f& newVel)
    {
        return bob.setVel(newVel);
    }
public:
    Physics::SolutionMethod method;

private:
    Bob bob; // the bob
    sf::RectangleShape rod;
    float L;
};

#endif