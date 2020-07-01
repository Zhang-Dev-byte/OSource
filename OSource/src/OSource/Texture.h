#pragma once
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION

namespace OSource {
	class Texture {
	private:
		int width, height;
		int comp;
		unsigned int id;
		const char* path;

	public:
		Texture(const char* path);
		Texture();
		void Bind();
		void UnBind();
		unsigned int getID();
		int getWidth();
		int getHeight();
		const char* getPath();
	};
}