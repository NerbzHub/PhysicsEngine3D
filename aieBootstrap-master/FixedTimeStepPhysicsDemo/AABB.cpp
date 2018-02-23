#include "AABB.h"

AABB::AABB(glm::vec2 position, glm::vec2 extents, glm::vec2 velocity, float mass, glm::vec4 colour) : RigidBody(ENUMAABB, position, velocity, 0, mass)
{
	m_extents = extents;
	m_colour = colour;
}

AABB::~AABB()
{
}

void AABB::makeGizmo()
{
	aie::Gizmos::add2DAABBFilled(m_position, m_extents, m_colour);
}

glm::vec2 AABB::getExtents()
{
	return m_extents;
}

glm::vec2 AABB::getMinExtents()
{
	return m_position - m_extents;
}

glm::vec2 AABB::getMaxExtents()
{
	return m_position + m_extents;
}