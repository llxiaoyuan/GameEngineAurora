#include<Aurora/OrthoCamera.hpp>

OrthoCamera::OrthoCamera(const float& x, const float& y) :
	position(x, y, 0), size((float)Graphics::getWidth(), (float)Graphics::getHeight())
{
	update();
}

const glm::vec3& OrthoCamera::getPosition() const
{
	return position;
}

const glm::vec2& OrthoCamera::getSize() const
{
	return size;
}

void OrthoCamera::setPosition(const float& x, const float& y)
{
	position.x = x;
	position.y = y;
}

void OrthoCamera::setPosition(const glm::vec3 pos)
{
	position = pos;
}

void OrthoCamera::setSize(const float& width, const float& height)
{
	size.x = width;
	size.y = height;
}

void OrthoCamera::move(const float& dx, const float& dy)
{
	position.x += dx;
	position.y += dy;
}

const glm::mat4& OrthoCamera::getProjectionMatrix() const
{
	return projMatrix;
}

glm::vec3 OrthoCamera::screenToWorld(const glm::vec3& pos) const
{
	const glm::vec3 worldPos = pos + position;
	return worldPos;
}

glm::vec3 OrthoCamera::screenToWorld(const float& x, const float& y) const
{
	const glm::vec3 worldPos = glm::vec3(x, y, 0) + position;
	return worldPos;
}

void OrthoCamera::update()
{
	projMatrix = glm::ortho(0.f, size.x, 0.f, size.y, -1.f, 1.f);
	projMatrix = glm::translate(projMatrix, -position);
}
