#ifndef PHYSICS_H
#define PHYSICS_H

#include <math.h>
#include <SFML/Graphics.hpp>

enum class SolutionMethod
{
    NULLMethod,
    SmallAngle,
    Euler,
    EulerCromer,
    RungeKutta
};

sf::Vector2f smallAngle(float time, float L, float theta_i);

#endif