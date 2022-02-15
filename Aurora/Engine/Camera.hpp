#pragma once

#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<glm/gtc/matrix_transform.hpp>

#include"SpriteRenderer.hpp"

class Camera
{
public:

	Camera(Shader& shader, const float& x, const float& y);

	const glm::vec3& getPosition() const;

	void setPosition(const float& x,const float& y);

private:

	Shader& shader;

	glm::vec3 position;

};


#endif // !_CAMERA_HPP_
