#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <thread>
#include <functional>
#include <algorithm>
#include <glm/glm.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "ray.hpp"
#include "world.hpp"
#include "allshape.hpp"
#include "renderer.hpp"
#include "camera.hpp"
#include "material/refraction.hpp"

void writePixel(uint8_t *pixels, int x, int y, glm::ivec2 imgSize, int channelColor, glm::ivec3 color)
{
    int pixelIndex = (((imgSize.y - 1) - y) * imgSize.x) + x;
    pixelIndex *= channelColor;
    pixels[pixelIndex] = color.x;
    pixels[pixelIndex + 1] = color.y;
    pixels[pixelIndex + 2] = color.z;
}
int main(int argc, char *argv[])
{
    int saveLastTime = time(0);
    Renderer renderer;
    renderer.maxDepthBouncing = 4;
    renderer.samplePerPixel = 64;
    World world;
    Camera camera;
    camera.position = {0, 1, -5};
    auto sphere = world.createShapeObject<Sphere>();
    sphere->material = new Lambertian();
    sphere->material->albedo = {0.2f, 1.0f, .2f};
    {

        auto plan = world.createShapeObject<Sphere>();
        plan->material = new Lambertian();
        sphere->position.y = 1;
        sphere->position.x = -1.2f;
        plan->position.y = -200;
        plan->radius = 200;
    }
    {
        auto sphereMirror = world.createShapeObject<Sphere>();
        sphereMirror->material = new Metal();
        sphereMirror->position.y = 1.f;
        sphereMirror->position.x = 1.2f;
        auto metal = (Metal *)sphereMirror->material;
        metal->fuzzy = 0.1f;
    }
    {
        // auto sphereGlass = world.createShapeObject<Sphere>();
        // sphereGlass->position.y = 0.5f;
        // sphereGlass->radius = 0.5f;
        // Reflaction *matGlass = new Reflaction();
        // sphereGlass->material = matGlass;
    }
    const int channelColor = 3;
    auto resolution = renderer.resolution;
    uint8_t *pixels = new uint8_t[resolution.x * resolution.y * channelColor];
    int startTime = time(0);
    int allPixel = resolution.x * resolution.y;
    float notifyLastTime = 0.f;
    for (int y = 0; y < resolution.y; y++)
    {
        for (int x = 0; x < resolution.x; x++)
        {
            auto color = renderer.render({x, y});
            writePixel(pixels, x, y, renderer.resolution, 3, color * glm::vec3(255));
            auto processPercent = (x + y * resolution.x) / (float)allPixel;
            processPercent *= 100;
            if (processPercent - notifyLastTime > 1.f)
            {
                notifyLastTime = processPercent;
                printf("render process %0.2f / 100%\n", processPercent);
            }
            if (time(0) - saveLastTime > 1)
            {
                saveLastTime = time(0);
                stbi_write_jpg("result.jpg", resolution.x, resolution.y, channelColor, pixels, 100);
            }
        }
    }
    printf("Render use time %d\n", time(0) - startTime);
    stbi_write_jpg("result.jpg", resolution.x, resolution.y, channelColor, pixels, 100);
    delete[] pixels;
    return 0;
}