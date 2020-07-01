#include "InputManager.h"

namespace OSource{
    Input::Input(GLFWwindow* window){
        this->window = window;
    }

    bool Input::GetKey(int key){
        return (glfwGetKey(window, key) == GLFW_PRESS);
    }
}