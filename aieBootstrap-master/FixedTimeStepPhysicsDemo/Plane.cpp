#include "Plane.h"

Plane::Plane() : PhysicsObject(ShapeType::PLANE)
{
	m_distanceToOrigin = 0;
	m_normal = glm::vec2(0, 0);
	m_centrePoint = m_normal * m_distanceToOrigin;
}

Plane::Plane(glm::vec2 a_normal, float distance) : PhysicsObject(ShapeType::PLANE)
{
	//todo
	m_normal = a_normal;
	m_distanceToOrigin = distance;
}

Plane::~Plane()
{
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
}

void Plane::makeGizmo()
{
	float lineSegmentLength = 300;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	// easy to rotate normal through 90 degrees around z 
	glm::vec2 parallel(m_normal.y, -m_normal.x); 
	glm::vec4 colour(1, 0, 1, 1);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DLine(start, end, colour);
}

void Plane::resetPosition()
{
}

void Plane::resolveCollision(RigidBody* actor2, glm::vec2 contact)
{
	glm::vec2 normal = m_normal;
	glm::vec2 relativeVelocity = actor2->getVelocity();

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
		glm::dot(normal, normal * ((1 / actor2->getMass())));

	glm::vec2 force = normal * j;

	actor2->applyForce(force, contact - actor2->getPosition());
}
