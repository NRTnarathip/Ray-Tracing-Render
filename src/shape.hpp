#pragma once
#include "glm/glm.hpp"
#include "ray.hpp"
#include "object.hpp"

class Shape : public Object
{
public:
    virtual Rayhit getRayHit(Ray &ray) = 0;
};