#pragma once
#include "shape.hpp"
#include <iostream>

class Sphere : public Shape
{
public:
    float radius = 1.f;
    Rayhit getRayHit(Ray &ray)
    {
        Rayhit hit;
        glm::vec3 rayOrigin = ray.origin;
        glm::vec3 rayDir = ray.dir;
        glm::vec3 sphereOrigin = this->position;
        glm::vec3 sphereDist = sphereOrigin - rayOrigin;
        // T == length
        // C == Sphere Origin
        // A == Angle
        float tca = glm::dot(sphereDist, rayDir);
        // Then point tca is behide rayDir
        if (tca < 0.0f)
        {
            return hit;
        }
        float d2 = glm::dot(sphereDist, sphereDist) - (tca * tca);

        // Out Radius
        if (d2 > radius * radius)
        {
            return hit;
        }
        float thc = glm::sqrt(radius * radius - d2);
        glm::vec3 pointIntersectionStart = rayOrigin + (rayDir * (tca - thc));
        glm::vec3 pointIntersectionEnd = rayOrigin + (rayDir * (tca + thc));
        glm::vec3 normalPointIStart = glm::normalize(pointIntersectionStart - sphereOrigin);
        hit.hit.point = pointIntersectionStart;
        hit.hit.normal = normalPointIStart;
        hit.distance = pointIntersectionStart - rayOrigin;
        hit.isHit = true;
        return hit;
    }
};