#pragma once
#include <iostream>
#include "ray.hpp"
#include "glm/glm.hpp"

class Renderer
{
public:
    static Renderer *instance;
    static Renderer *GetInstance()
    {
        return instance;
    }
    Renderer()
    {
        instance = this;
        setResolution({1280, 720});
    }

    void setResolution(glm::vec2 size)
    {
        resolution = size;
        aspact = resolution.x / resolution.y;
    }
    int samplePerPixel = 64;
    int maxDepthBouncing = 4;
    float aspact = 16.f / 9.f;
    glm::ivec2 resolution;
    glm::vec3 getRayColor(Ray &ray, int bouncing);
    glm::vec3 render(glm::vec2 pixelCoord);
};
