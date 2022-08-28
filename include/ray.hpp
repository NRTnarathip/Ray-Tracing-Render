#pragma once
#include "glm/glm.hpp"
#include <vector>
class Object;

class Ray
{
public:
    Ray() {}
    Ray(const glm::vec3 _origin, const glm::vec3 _dir) : origin(_origin), dir(_dir)
    {
    }
    glm::vec3 at(float t)
    {
        return origin + t * dir;
    }
    glm::vec3 origin;
    glm::vec3 dir;
};

class Rayhit
{
public:
    struct Hit
    {
        Hit(glm::vec3 p, glm::vec3 n) : point(p), normal(n)
        {
        }
        Hit() {}
        glm::vec3 point;
        glm::vec3 normal;
    };
    float getLength()
    {
        return glm::length(distance);
    }
    Object *object;
    glm::vec3 distance = glm::vec3(10000.f);
    bool isHit = false;
    Hit hit;
};
