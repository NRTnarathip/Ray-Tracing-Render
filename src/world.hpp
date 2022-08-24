#pragma once
#include "glm/glm.hpp"
#include "shape.hpp"
#include <vector>
#include "time.h"
#define MIN_LIGHT 0.02f
#define MAX_LIGHT 0.98f
float rand01()
{
    float randValue = rand() / float(RAND_MAX);
    return randValue;
}
float randMinMax(float min, float max)
{
    return min + (max - min) * rand01();
}
glm::vec3 randomInSpere()
{
    auto p = glm::vec3(randMinMax(-1, 1), randMinMax(-1, 1), randMinMax(-1, 1));
    return glm::normalize(p);
}
constexpr glm::vec3 BackgroundColor1{1.0f, 1.0f, 1.0f};
constexpr glm::vec3 BackgroundColor2{0.5f, 0.7f, 1.0f};

class World
{
public:
    World()
    {
        srand(time(0));
    }
    int samplePerPixel = 32;
    int maxDepthBouncing = 1024;
    std::vector<Shape *> shapes;
    Rayhit getRayHit(Ray ray)
    {
        auto hit = Rayhit();
        for (auto shape : shapes)
        {
            auto hitObject = shape->getRayHit(ray);
            if (hitObject.isHit)
            {
                if (hitObject.getLength() < hit.getLength())
                {
                    hit = hitObject;
                }
            }
        }
        return hit;
    }
    glm::vec3 getRayColor(Ray ray, int bouncing)
    {
        auto rayHit = getRayHit(ray);
        if (rayHit.isHit)
        {
            glm::vec3 ambient = glm::vec3(0.1f);
            glm::vec3 lightDir = glm::vec3(0, -1, 0);
            glm::vec3 albedo(.85f);
            auto hitPoint = rayHit.hit.point;
            auto hitNormal = rayHit.hit.normal;
            float diff = glm::max(glm::dot(hitNormal, -lightDir), MIN_LIGHT);
            glm::vec3 attenuation = albedo * diff;
            attenuation = glm::min(glm::vec3(MAX_LIGHT), attenuation + ambient);
            Ray newRayBouncing;
            newRayBouncing.origin = hitPoint;
            auto newDirBouncing = hitPoint + hitNormal + randomInSpere();
            newRayBouncing.dir = glm::normalize(newDirBouncing - hitPoint);
            if (bouncing < maxDepthBouncing)
            {
                attenuation *= getRayColor(newRayBouncing, bouncing + 1);
            }
            return attenuation;
        }
        const float t = ray.dir.y + 0.5f;
        glm::vec3 distColor = BackgroundColor1 - BackgroundColor2;
        return BackgroundColor1 - distColor * t;
    }
    glm::vec3 render(Ray &rayRender, float aspact, glm::vec2 imgSize, glm::vec2 pixelCoord)
    {
        glm::vec3 colorPixel(0.f);
        auto x = pixelCoord.x;
        auto y = pixelCoord.y;
        auto width = imgSize.x;
        auto height = imgSize.y;
        for (int i = 0; i < samplePerPixel; i++)
        {
            Ray ray;
            ray.origin = rayRender.origin;
            auto u = (float)((float)x + rand01()) / (width - 1) - 0.5f;
            auto v = (float)((float)y + rand01()) / (height - 1) - 0.5f;
            v /= aspact;

            ray.dir = normalize(glm::vec3(u, v, rayRender.dir.z));
            auto rayColor = getRayColor(ray, 0);
            colorPixel += rayColor;
        }
        colorPixel = colorPixel / glm::vec3(samplePerPixel);
        colorPixel = glm::pow(colorPixel, glm::vec3(1.f / 2.2f));
        return colorPixel;
    }
};