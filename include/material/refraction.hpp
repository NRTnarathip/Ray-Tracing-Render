#pragma once
#include "material.hpp"

class Reflaction : public Material
{
public:
    bool scatter(Ray &scatter, const Rayhit &hit, glm::vec3 &attenuation)
    {

        return true;
    };
};