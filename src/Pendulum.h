#include <SFML/Graphics.hpp>
#include "World.h"
#include "Physics.h"

#ifndef PENDULUM_H
#define PENDULUM_H


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
private:
    sf::Vector2f pos; // position of the bob in polar coordinates
    float r; // the radius
    sf::CircleShape img;
};


class Pendulum
{
public:
    Pendulum(World& world, float length, float mass, sf::Vector2f bobPos, SolutionMethod method, sf::Color bobC);
    Pendulum() = default;
    ~Pendulum() = default;
    void draw(sf::RenderWindow& wnd, World& world);
    const sf::Vector2f getBobPos() const
    {
        return bob.getPos();
    }
    const sf::Vector2f& setBobPos(const sf::Vector2f& newPos)
    {
        return bob.setPos(newPos);
    }

public:
    SolutionMethod method;

private:
    Bob bob; // the bob
    sf::RectangleShape rod;
    float L;
};

#endif