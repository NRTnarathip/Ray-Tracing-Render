#include "renderer.hpp"
#include "world.hpp"
#include "camera.hpp"

#include "my_random.h"
Renderer *Renderer::instance = nullptr;
constexpr glm::vec3 BackgroundColor1{1.0f, 1.0f, 1.0f};
constexpr glm::vec3 BackgroundColor2{0.5f, 0.7f, 1.0f};

glm::vec3 Renderer::getRayColor(Ray &rayCamera, int bouncing)
{
    World *world = World::GetInstance();
    Rayhit rayHit = world->getRayHit(rayCamera);
    if (rayHit.isHit)
    {
        glm::vec3 lightDir = glm::normalize(glm::vec3(-0.5f, -1.f, 0.75f));
        glm::vec3 colorShadowRay = glm::vec3(1.f);
        float diff = glm::max(glm::dot(rayHit.hit.normal, -lightDir), 0.f);
        Ray rayHitToLight;
        rayHitToLight.dir = glm::normalize(-lightDir);
        rayHitToLight.origin = rayHit.hit.point;
        auto hitToLight = world->getRayHit(rayHitToLight);
        if (hitToLight.isHit)
        {
            colorShadowRay = glm::vec3(0.f);
        }

        auto objMaterial = rayHit.object->material;
        auto ambient = glm::vec3(0.05f);
        auto sunInsentity = 1.f;
        glm::vec3 attenuation;
        bool isShouldNextBouncing = objMaterial->scatter(rayCamera, rayHit, attenuation);
        attenuation = glm::min(attenuation + ambient, MAX_LIGHT);
        attenuation = attenuation * colorShadowRay * diff * sunInsentity;
        if (bouncing < maxDepthBouncing && isShouldNextBouncing)
        {
            attenuation *= getRayColor(rayCamera, bouncing + 1);
        }
        return attenuation;
    }
    const float t = rayCamera.dir.y + 0.5f;
    glm::vec3 distColor = BackgroundColor1 - BackgroundColor2;
    return BackgroundColor1 - distColor * t;
}
glm::vec3 Renderer::render(glm::vec2 pixelCoord)
{
    World *world = World::GetInstance();
    Camera *camera = Camera::GetCurrent();
    glm::vec3 colorPixel(0.f);
    auto x = pixelCoord.x;
    auto y = pixelCoord.y;
    auto width = resolution.x;
    auto height = resolution.y;
    for (int i = 0; i < samplePerPixel; i++)
    {
        Ray ray;
        ray.origin = camera->position;
        auto u = (float)((float)x + rand01()) / (width - 1) - 0.5f;
        auto v = (float)((float)y + rand01()) / (height - 1) - 0.5f;
        v /= camera->aspact;

        ray.dir = glm::normalize(glm::vec3(u, v, 1.f));
        auto rayColor = getRayColor(ray, 0);
        colorPixel += rayColor;
    }
    colorPixel = colorPixel / glm::vec3(samplePerPixel);
    colorPixel = glm::pow(colorPixel, glm::vec3(1.f / 2.2f));
    return colorPixel;
}