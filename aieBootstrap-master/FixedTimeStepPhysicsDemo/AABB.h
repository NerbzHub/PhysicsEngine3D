#pragma once
#include "Rigidbody.h"

class AABB : public RigidBody
{
public:
	AABB(glm::vec2 position, glm::vec2 extents, glm::vec2 velocity, float mass, glm::vec4 colour);
	~AABB();

	virtual void makeGizmo();
	glm::vec4 getColour() { return m_colour; }

	glm::vec2 getExtents();
	glm::vec2 getMinExtents();
	glm::vec2 getMaxExtents();

	virtual bool checkCollision(PhysicsObject* pOther) { return false; };

protected:
	glm::vec2 m_extents;
	glm::vec4 m_colour;
};
