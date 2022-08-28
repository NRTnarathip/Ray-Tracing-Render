#pragma once
#include "object.hpp"

class Camera : public Object
{
public:
    static Camera *instance;
    static Camera *GetInstance()
    {
        return instance;
    };
    Camera()
    {
        instance = this;
        if (!current)
        {
            current = this;
        }
    }
    Camera *current = nullptr;
    static Camera *GetCurrent()
    {
        return instance->current;
    }

    float aspact = 16.f / 9.f;
};