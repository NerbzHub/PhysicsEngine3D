#include "Sphere.h"



Sphere::Sphere(glm::vec2 position, glm::vec2 velocity,
	float mass, float radius, glm::vec4 colour) : RigidBody(SPHERE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_colour = colour;
	m_moment = 0.5f * mass * radius * radius;
}

Sphere::Sphere(glm::vec2 position, float inclination, float speed, float mass, float radius, glm::vec4 colour) 
	: Sphere(position, glm::vec2(sin(inclination), cos(inclination)) * speed, mass, radius, colour)
{
	m_radius = radius;
	m_colour = colour;
}


Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	glm::vec2 end = glm::vec2(std::cos(m_rotation), std::sin(m_rotation)) * m_radius;

	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
	aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1, 1, 1, 1));
}

bool Sphere::checkCollision(PhysicsObject* pOther)
{
	Sphere* other = dynamic_cast<Sphere*>(pOther);
		if(other)
		{
			return((other->m_radius + this->m_radius) >
				glm::distance(other->m_position, this->m_position));
		}
		return false;
}
