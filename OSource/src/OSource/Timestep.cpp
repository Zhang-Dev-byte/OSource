#include "Timestep.h"

namespace OSource {
    void Timestep::Update()
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    float Timestep::GetDeltatime()
    {
        return deltaTime;
    }
}