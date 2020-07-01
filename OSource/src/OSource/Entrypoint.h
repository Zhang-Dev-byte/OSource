#pragma once
#include "Application.h"
#include "Log.cpp"

namespace OSource{
    extern Application* CreateApplication();
}

int main(){
    OSource::Log::Init();
    OS_CORE_INFO("Initalized Log!");
    auto app = OSource::CreateApplication();
    app->Run();
    while(true);
}