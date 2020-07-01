#pragma once
#include "InputManager.h"
namespace OSource{
    class Application{
    public:
        virtual void Run() = 0;
        virtual void HandleInput(OSource::Input& input) = 0;
    };
}