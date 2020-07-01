#include "Texture.h"
#include "stb_image.h"

namespace OSource {
    Texture::Texture(const char* path)
    {
        this->path = path;
        stbi_set_flip_vertically_on_load(true);

        unsigned char* data = stbi_load(path, &width, &height, &comp, 4);

        glGenTextures(1, &id);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    Texture::Texture()
    {
    }

    void Texture::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void Texture::UnBind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    unsigned int Texture::getID()
    {
        return id;
    }
    int Texture::getWidth()
    {
        return width;
    }
    int Texture::getHeight()
    {
        return height;
    }
    const char* Texture::getPath()
    {
        return path;
    }
}
