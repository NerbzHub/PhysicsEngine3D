#pragma once
#include "RigidBody.h"

class Box : public RigidBody
{
public:
	Box(glm::vec2 position, glm::vec2 extents, glm::vec2 velocity, float mass, glm::vec4 colour);
	~Box();

	void fixedUpdate(glm::vec2 gravity, float timeStep);
	void makeGizmo();
	float getWidth() { return m_extents.x; };
	float getHeight() { return m_extents.y; };
	float getMoment() { return m_moment; };
	glm::vec2 getExtents() { return m_extents; };
	glm::vec2 getPosition() { return m_position; };
	glm::vec2 getLocalX() { return m_localX; };
	glm::vec2 getLocalY() { return m_localY; };



	

protected:
	glm::vec2 m_extents; // halfway lengths
	glm::vec4 m_colour;
	glm::vec2 m_position;

	// store the local x,y axes of the box based on its angle of rotation
	glm::vec2 m_localX;
	glm::vec2 m_localY;
};

