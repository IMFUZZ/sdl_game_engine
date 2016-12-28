#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

	class Camera2D {
	public:
		Camera2D();
		~Camera2D();

		void init(int a_screenWidth, int a_screenHeight);
		void update();

		bool isBoxInView(const glm::vec2& a_pos, const glm::vec2& a_dims);

		void setPosition(const glm::vec2& a_pos);
		void translate(const glm::vec2& a_translation);
		void setScale(float a_scale);
		void zoom(float a_zoomValue);


		glm::vec2 convertScreenToWorld(glm::vec2);

		//getters
		glm::vec2 getPosition() { return _position; }
		float getScale() { return _scale; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

	private:
		int _screenWidth, _screenHeight;
		bool _needsMatrixUpdate;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
	};

}