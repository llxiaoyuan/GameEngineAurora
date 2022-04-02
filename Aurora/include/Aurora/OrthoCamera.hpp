#pragma once

#ifndef _ORTHOCAMERA_HPP_
#define _ORTHOCAMERA_HPP_

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<glm/gtc/matrix_transform.hpp>

#include"Graphics.hpp"

class OrthoCamera
{
public:

	OrthoCamera(const float& x, const float& y);

	const glm::vec3& getPosition() const;

	const glm::vec2& getSize() const;

	void setPosition(const float& x,const float& y);

	void setPosition(const glm::vec3 pos);

	void setSize(const float& width, const float& height);

	void move(const float& dx, const float& dy);

	const glm::mat4& getProjectionMatrix() const;

	glm::vec3 screenToWorld(const glm::vec3& pos) const;

	glm::vec3 screenToWorld(const float& x,const float& y) const;

	void update();

private:

	glm::vec3 position;

	glm::vec2 size;

	glm::mat4 projMatrix;

};


#endif // !_ORTHOCAMERA_HPP_
