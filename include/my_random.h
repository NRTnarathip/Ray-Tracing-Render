#pragma once
#include <iostream>
#include <glm/glm.hpp>

inline float rand01()
{
    return rand() / float(RAND_MAX);
}
inline float randMinMax(float min, float max)
{
    return min + (max - min) * rand01();
}
inline glm::vec3 randomVector3()
{
    return glm::vec3(randMinMax(-1, 1), randMinMax(-1, 1), randMinMax(-1, 1));
}
inline glm::vec3 randomInSphere()
{
    return glm::normalize(randomVector3());
}
inline glm::vec3 randomInHemisphere(const glm::vec3 &normal)
{
    glm::vec3 in_unit_sphere = randomInSphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}
