#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace OSource{
    class Input{
    public:
        Input(GLFWwindow* window);
        bool GetKey(int key);
    private:
        GLFWwindow* window;
    };
}