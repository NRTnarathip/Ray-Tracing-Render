#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <windows.h>
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

void writePixel(uint8_t *pixels, int x, int y, glm::ivec2 imgSize, int channelColor, glm::ivec3 color)
{
    int pixelIndex = (((imgSize.y - 1) - y) * imgSize.x) + x;
    pixelIndex *= channelColor;
    pixels[pixelIndex] = color.x;
    pixels[pixelIndex + 1] = color.y;
    pixels[pixelIndex + 2] = color.z;
}
glm::vec3 lerp(glm::vec3 x, glm::vec3 y, float t)
{
    return x * (1.f - t) + y * t;
}
float hit_sphere(const glm::vec3 &center, double radius, const Ray &r)
{
    glm::vec3 oc = r.origin - center;
    auto a = dot(r.dir, r.dir);
    auto b = 2.0 * dot(oc, r.dir);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0.f)
    {
        return -1.f;
    }
    return (-b - sqrt(discriminant) / 2 * a);
}
glm::vec3 rayColor(Ray ray)
{
    auto rayDir = ray.dir;
    float hitSphere = hit_sphere(glm::vec3(0, 0, 1), 0.5, ray);
    if (hitSphere > 0.f)
    {
        glm::vec3 hitNormal = glm::normalize(ray.at(hitSphere) + glm::vec3(0, 0, -1));
        return ((hitNormal + glm::vec3(1)) * 0.5f);
    }

    // sky simple gradient
    glm::vec3 colorPixel = glm::vec3(0.5, 0.7, 1.0);
    return colorPixel;
}

int main(int argc, char *argv[])
{
    World world;
    auto sphere = new Sphere();
    sphere->position.y = 1;
    auto plan = new Sphere();
    plan->position.y = -200;
    plan->radius = 200;
    world.shapes.push_back(sphere);
    world.shapes.push_back(plan);

    const float aspact = 16.f / 9.f; // == 1.77777777778
    const int width = 1920;
    const int height = static_cast<int>(width / aspact);

    const glm::ivec2 imgSize = {width,
                                height};
    const int channelColor = 3;
    uint8_t *pixels = new uint8_t[width * height * channelColor];
    glm::vec3 cameraPos = {0, 1, -6.5};
    int startTime = time(0);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            auto cameraRay = Ray(cameraPos, glm::vec3(0, 0, 1));
            glm::vec3 color(0.f);
            color = world.render(cameraRay, aspact, imgSize, {x, y});
            writePixel(pixels, x, y, imgSize, 3, color * glm::vec3(255));
        }
    }
    printf("end use time %d\n", time(0) - startTime);
    stbi_write_jpg("result.jpg", width, height, channelColor, pixels, 100);
    delete[] pixels;
    return 0;
}