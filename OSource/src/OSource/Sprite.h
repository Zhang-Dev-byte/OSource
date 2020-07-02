#pragma once
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

namespace OSource {
    class Sprite {
    public:
        Sprite(Texture& texture, const char* name);
        void Render();
        void UpdateModel();
        void SetScale(vec2& value);
        void SetPosition(vec2& value);
        void SetRotation(float value);

        vec2& GetScale();
        vec2& GetPosition();
        float GetRotation();
        Texture& GetTexture();

        const char* GetName();

        void Scale(vec2& value);
        void Translate(vec2& value);
        void Rotate(float value);
    private:
        unsigned int VBO, VAO, EBO, TBO;
        Shader shader = Shader("res/vs.glsl", "res/fs.glsl");;
        Texture tex;
        mat4 model;
        vec2 position;
        vec2 scale;
        float rotation;
        const char* name;
    };
}