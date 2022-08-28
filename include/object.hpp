#pragma once
#include "glm/glm.hpp"
#include "material.hpp"
class Object
{
public:
    Material *material;
    glm::vec3 position;
};