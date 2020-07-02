#pragma once
#include "InputManager.h"
namespace OSource {
    class Layer {
    public:
        virtual void OnRun() = 0;
        virtual void HandleInput(OSource::Input& input) = 0;
        virtual void OnRender() = 0;
    };
}