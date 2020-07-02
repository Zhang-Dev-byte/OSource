#pragma once
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include "Log.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

namespace OSource{
    class Shader
    {
    public:
        unsigned int ID;
        // constructor generates the shader on the fly
        // ------------------------------------------------------------------------
        Shader(const char* vertexPath, const char* fragmentPath);
        // activate the shader
        // ------------------------------------------------------------------------
        void Use();
        // utility uniform functions
        // ------------------------------------------------------------------------
        void SetBool(const std::string &name, bool value) const;
        // ------------------------------------------------------------------------
        void SetInt(const std::string &name, int value) const;
        // ------------------------------------------------------------------------
        void SetFloat(const std::string &name, float value) const;
        
        void SetMatrix4f(const std::string& name, mat4& value) const;

    private:
        // utility function for checking shader compilation/linking errors.
        // ------------------------------------------------------------------------
        void CheckCompileErrors(unsigned int shader, std::string type)
        {
            int success;
            char infoLog[1024];
            if (type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    OS_CORE_ERROR("Failed to compile shader of type {0}\n {1}\n -- --------------------------------------------------- -- ", type, infoLog);
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    OS_CORE_ERROR("Failed to link program of type {0}\n{1}\n -- --------------------------------------------------- -- ", type, infoLog);
                }
            }
        }
    };
}