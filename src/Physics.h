#ifndef PHYSICS_H
#define PHYSICS_H

#include <math.h>
#include <SFML/Graphics.hpp>

namespace Physics
{

    // TODO: Make g dependent on L so that the value is more physical
    // if that is even possible
    // For now, g is hardcoded to a nice value that looks like a real pendulum.
    constexpr float g = 150.f;

    enum class SolutionMethod
    {
        NULLMethod,
        SmallAngle,
        Euler,
        EulerCromer,
        RungeKutta
    };

    sf::Vector2f smallAngle(float time, float L, float theta_i);

    std::pair<sf::Vector2f, sf::Vector2f> euler(float dt, sf::Vector2f prevPos, sf::Vector2f prevVel);

    std::pair<sf::Vector2f, sf::Vector2f> eulerCromer(float dt, sf::Vector2f prevPos, sf::Vector2f prevVel);
}

#endif