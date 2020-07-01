#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include "Log.h"
#include "InputManager.h"

namespace OSource{
    extern Application* CreateApplication();
}

void ResizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
int main(){
    OSource::Log::Init();
    OS_CORE_INFO("Initalized Log!");
    auto app = OSource::CreateApplication();
    app->Run();


    if(!glfwInit()){
        OS_CORE_ERROR("Failed to initalize GLFW!");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "OSource Engine", NULL, NULL);
    if (window == NULL)
    {
        OS_CORE_ERROR("Failed to create window!");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        OS_CORE_ERROR("Failed to initialize GLAD!");
        return -1;
    }
    OSource::Input input = OSource::Input(window);   

    glViewport(0, 0, 1280, 720); 

    glfwSetFramebufferSizeCallback(window, ResizeCallback);  

    while(!glfwWindowShouldClose(window))
    {
        app->HandleInput(input);
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        app->Render();
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    glfwTerminate();
    return 0;
}