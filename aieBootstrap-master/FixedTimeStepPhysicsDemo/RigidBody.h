#pragma once
#include "PhysicsObject.h"
#include "Gizmos.h"

#define MIN_LINEAR_THRESHOLD 0.010f
#define MIN_ROTATION_THRESHOLD 0.01f


class RigidBody : public PhysicsObject {

public:

	RigidBody(ShapeType shapeID, glm::vec2 position,
		glm::vec2 velocity, float rotation, float mass); 

	~RigidBody();
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug() {};

	void applyForce(glm::vec2 force, glm::vec2 pos);

	//void applyForceToActor(RigidBody* actor2, glm::vec2 force);

	virtual bool checkCollision(PhysicsObject* pOther) = 0;

	void resolveCollision(RigidBody* actor2, glm::vec2 contact, glm::vec2* collisionNormal=nullptr);

	// Getter/Setter Position
	glm::vec2 getPosition() { return m_position; }
	void setPosition(glm::vec2 newPos) { m_position = newPos; }

	float getRotation() { return m_rotation; }

	float getMass() { return m_mass; }

	// Getter/Setter Velocity
	glm::vec2 getVelocity() { return m_velocity; }
	void setVelocity(glm::vec2 newVel) { m_velocity = newVel; }

	// Getter/Setter Linear Drag
	float getLinearDrag() { return m_linearDrag; };
	void setLinearDrag(float newLinDrag) { m_linearDrag = newLinDrag; }

	// Getter/Setter Angular Drag
	float getAngularDrag() { return m_angularDrag; }
	void setAngularDrag(float newAngDrag) { m_angularDrag = newAngDrag; }

	// Getter/Setter Elasticity
	float getElasticity() { return m_elasticity; }
	void setElasticity(float newElasticity) { m_elasticity = newElasticity; }
	
protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	float m_rotation; //2D so we only need a single float to represent our rotation
	float m_moment;
	float m_linearDrag;
	float m_angularDrag;
	float m_elasticity;
	float m_angularVelocity;

};

