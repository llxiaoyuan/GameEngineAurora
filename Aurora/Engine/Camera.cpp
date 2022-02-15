#include"Camera.hpp"

Camera::Camera(Shader& shader, const float& x, const float& y):
	shader(shader)
{
	position[2] = 0;
	setPosition(x, y);
}

const glm::vec3& Camera::getPosition() const
{
	return position;
}

void Camera::setPosition(const float& x, const float& y)
{
	position[0] = x;
	position[1] = y;
	glm::mat4 view = glm::translate(glm::mat4(1.f), position);
	shader.bind();
	shader.setMatrix4fv("view", view);
	shader.unbind();
}