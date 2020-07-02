#include "Sprite.h"

namespace OSource {
    Sprite::Sprite(Texture& texture, const char* name)
    {
        this->name = name;
        tex = texture;
        position = vec2(0, 0);
        scale = vec2(1, 1);
        rotation = 0.0f;
        model = mat4(1.0f);
        UpdateModel();
        float vertices[] = {
             0.5f,  0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };
        float texCoords[] = {
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenBuffers(1, &TBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, TBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);


        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }
    void Sprite::Render()
    {
        shader.Use();
        shader.SetInt("t", tex.getID());
        shader.SetMatrix4f("model", model);
        tex.Bind();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    void Sprite::UpdateModel()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), vec3(position, 0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), glm::vec3(scale, 0));
        model = transform;
    }
    void Sprite::SetScale(vec2& value)
    {
        scale = value;
        UpdateModel();
    }
    void Sprite::SetPosition(vec2& value)
    {
        position = value;
        UpdateModel();
    }
    void Sprite::SetRotation(float value)
    {
        rotation = value;
        UpdateModel();
    }

    vec2& Sprite::GetScale()
    {
        return scale;
    }

    vec2& Sprite::GetPosition()
	{
        return position;
	}

    float Sprite::GetRotation()
    {
        return rotation;
    }

	Texture& Sprite::GetTexture()
	{
        return tex;
	}

    const char* Sprite::GetName()
    {

        return name;
    }

    void Sprite::Scale(vec2& value)
    {
        scale += value;
        UpdateModel();
    }
    void Sprite::Translate(vec2& value)
    {
        position += value;
        UpdateModel();
    }
    void Sprite::Rotate(float value)
    {
        rotation += value;
        UpdateModel();
    }
}