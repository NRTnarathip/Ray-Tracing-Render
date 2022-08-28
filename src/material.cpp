#include "material.hpp"
#include "my_random.h"
inline glm::vec3 reflect(const glm::vec3 &v, const glm::vec3 &n)
{
    return v - 2 * glm::dot(v, n) * n;
}
bool Lambertian::scatter(Ray &scatter, const Rayhit &hit, glm::vec3 &attenuation)
{
    auto hitPoint = hit.hit.point;
    auto hitNormal = hit.hit.normal;
    auto newDirBouncing = hitPoint + randomInHemisphere(hitNormal);
    scatter.dir = glm::normalize(newDirBouncing - hitPoint);
    scatter.origin = hitPoint;
    attenuation = albedo;
    return true;
};
bool Metal::scatter(Ray &scatter, const Rayhit &hit, glm::vec3 &attenuation)
{
    glm::vec3 reflectDir = reflect(scatter.dir, hit.hit.normal);
    reflectDir = normalize(reflectDir + randomInHemisphere(reflectDir) * fuzzy);
    scatter.dir = reflectDir;
    scatter.origin = hit.hit.point;
    attenuation = albedo;
    return dot(scatter.dir, hit.hit.normal) > 0;
};