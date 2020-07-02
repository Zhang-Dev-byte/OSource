#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include "Log.h"
#include "Layer.h"
#include "InputManager.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>

namespace OSource{
    extern Application* CreateApplication();
    extern void OnLayersCreate();
    extern std::vector<Layer*> layers = std::vector<Layer*>();
    extern void AddLayer(Layer* layer) {
        layers.push_back(layer);
    }
    extern void RunLayers() {
        for (auto i = layers.begin(); i != layers.end(); i++) {
            auto layer = *i;
            layer->OnRun();
        }
    }
    extern void RenderLayers() {
        for (auto i = layers.begin(); i != layers.end(); i++) {
            auto layer = *i;
            layer->OnRender();
        }
    }
}

void ResizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
int main(){
    OSource::Log::Init();
    OS_CORE_INFO("Initalized Log!");


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
    OSource::OnLayersCreate();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImFont* pFont = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 16);
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(NULL);

    auto app = OSource::CreateApplication();
    app->Run();
    OSource::RunLayers();

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    OSource::Input input = OSource::Input(window);   

    glViewport(0, 0, 1280, 720); 

    glfwSetFramebufferSizeCallback(window, ResizeCallback);  

    while(!glfwWindowShouldClose(window))
    {
        app->HandleInput(input);
        for (auto i = OSource::layers.begin(); i != OSource::layers.end(); i++) {
            auto layer = *i;
            layer->HandleInput(input);
        }

        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        app->Render();
        OSource::RenderLayers();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    glfwTerminate();
    return 0;
}