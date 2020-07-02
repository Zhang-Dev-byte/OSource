#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

namespace OSource {
	class Camera {
	public:
		Camera(float left, float right, float bottom, float top);
		void Update();
		void SetPosition(vec2 value);
		void SetRotation(float value);
		vec2& GetPostion();
		float GetRotation();
		void Translate(vec2 value);
		void Rotate(float value);
		mat4& GetProjectionView();
	private:
		mat4 projection;
		mat4 view;
		mat4 viewProjection;

		float rotation;
		vec2 position;
	};
}