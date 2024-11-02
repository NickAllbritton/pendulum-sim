#include "Physics.h"

namespace Physics
{

    sf::Vector2f smallAngle(float time, float L, float theta_i)
    {
        return sf::Vector2f{L, theta_i*std::cos(std::sqrt(g/L) * time)};
    }

}