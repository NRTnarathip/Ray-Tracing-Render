#pragma once
#include "glm/glm.hpp"
#include "shape.hpp"
#include <vector>
#include "time.h"
#define MIN_LIGHT 0.02f
#define MAX_LIGHT 0.98f
class World
{
public:
    static World *instance;
    static World *GetInstance()
    {
        return instance;
    }
    World()
    {
        srand(time(0));
        instance = this;
    }

    std::vector<Shape *> shapes;
    template <class ShapeType>
    ShapeType *createShapeObject()
    {
        auto newShape = new ShapeType();
        shapes.push_back(newShape);
        return newShape;
    }
    Rayhit getRayHit(const Ray &ray)
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
};