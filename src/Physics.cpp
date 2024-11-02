#include "Physics.h"

namespace Physics
{

    sf::Vector2f smallAngle(float time, float L, float theta_i)
    {
        return sf::Vector2f{L, theta_i*std::cos(std::sqrt(g/L) * time)};
    }

    // second-order euler method
    std::pair<sf::Vector2f, sf::Vector2f> euler(float dt, sf::Vector2f prevPos, sf::Vector2f prevVel)
    {
        float theta = prevPos.y + dt*prevVel.y;
        float theta_double_dot = -g/prevPos.x * std::sin(prevPos.y);
        float theta_dot = prevVel.y + dt*theta_double_dot;
        return std::pair<sf::Vector2f, sf::Vector2f>(sf::Vector2f{prevPos.x, theta}, sf::Vector2f{0.f, theta_dot});
    }
}