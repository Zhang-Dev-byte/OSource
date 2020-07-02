#pragma once
#include <GLFW/glfw3.h>

namespace OSource {
	class Timestep {
	public:
		void Update();
		float GetDeltatime();
	private:
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		float currentFrame = 0.0f;
	};
}