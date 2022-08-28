#pragma once
#include "glm/glm.hpp"
#include "ray.hpp"

class AABB
{
public:
    bool checkHit(Ray &ray);
};