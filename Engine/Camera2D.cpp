#include "Camera2D.h"

Camera2D::Camera2D() :
	_position(0.0f, 0.0f),
	_orthoMatrix(1.0f),
	_cameraMatrix(1.0f),
	_scale(1.0f), 
	_needsMatrixUpdate(true), 
	_screenWidth(800), 
	_screenHeight(600) 
{}

Camera2D::~Camera2D() {}

void Camera2D::init(int a_screenWidth, int a_screenHeight) {
	_screenWidth = a_screenWidth;
	_screenHeight = a_screenHeight;
	_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
}

void Camera2D::update() {
	if (_needsMatrixUpdate) {
		glm::vec3 
			translate(-_position.x + _screenWidth/2, -_position.y + _screenHeight/2, 0.0f),
			scale(_scale, _scale, 0.0f);
		// UPDATE TRANSLATION
		_cameraMatrix = glm::translate(_orthoMatrix, translate);
		// UPDATE SCALE
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
		// RESET THE UPDATE FLAG
		_needsMatrixUpdate = false;
	}
}

bool Camera2D::isBoxInView(const glm::vec2 & a_pos, const glm::vec2 & a_dims) {
	glm::vec2 
		centerPos = a_pos + a_dims / 2.0f,
		centerCameraPos = _position,
		distVec = centerPos - centerCameraPos,
		scaledScreenDimensions = glm::vec2(_screenWidth, _screenHeight) / (_scale * 2.0f);
	const float
		MIN_DISTANCE_X = a_dims.x / 2.0f + scaledScreenDimensions.x / 2.0f,
		MIN_DISTANCE_Y = a_dims.y / 2.0f + scaledScreenDimensions.y / 2.0f;
	float 
		xDepth = MIN_DISTANCE_X - abs(distVec.x),
		yDepth = MIN_DISTANCE_Y - abs(distVec.y);
	return (xDepth > 0 && yDepth < 0) ? true : false;
}

void Camera2D::setPosition(const glm::vec2 & a_pos) {
	_position = a_pos;
	_needsMatrixUpdate = true;
}

void Camera2D::translate(const glm::vec2 & a_translation) {
	setPosition(_position + a_translation);
}

void Camera2D::setScale(float a_scale) {
	_scale = a_scale;
	_needsMatrixUpdate = true;
}

void Camera2D::zoom(float a_zoomValue) {
	setScale(_scale + a_zoomValue);
}



