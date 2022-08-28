#pragma once
#include "glm/glm.hpp"
#include "ray.hpp"

class Material
{
public:
    glm::vec3 albedo{1, 1, 1};
    virtual bool scatter(Ray &scatter, const Rayhit &hit, glm::vec3 &attenuation) = 0;
};

class Lambertian : public Material
{
public:
    bool scatter(Ray &scatter, const Rayhit &hit, glm::vec3 &attenuation) override;
};
class Metal : public Material
{
public:
    float fuzzy = 0.0f;
    bool scatter(Ray &scatter, const Rayhit &hit, glm::vec3 &attenuation) override;
};