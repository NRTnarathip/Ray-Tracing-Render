#pragma once
#include "glm/glm.hpp"
#include "ray.hpp"
#include "object.hpp"

class Shape : public Object
{
public:
    virtual Rayhit getRayHit(const Ray &ray) = 0;
};