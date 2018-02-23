#pragma once
#include <glm\vec2.hpp>
#include <glm\ext.hpp>
#include <vector>
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include <iostream>


class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();
	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void debugScene();
	void checkForCollision();
	void update(float dt);
	void updateGizmos();
	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }
	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	// Plane
	static bool plane2Plane(PhysicsObject*, PhysicsObject*);
	static bool plane2Sphere(PhysicsObject*, PhysicsObject*);
	static bool plane2aabb(PhysicsObject*, PhysicsObject*);
	static bool plane2Box(PhysicsObject*, PhysicsObject*);

	// Sphere
	static bool sphere2Plane(PhysicsObject*, PhysicsObject*);
	static bool sphere2Sphere(PhysicsObject*, PhysicsObject*);
	static bool sphere2aabb(PhysicsObject*, PhysicsObject*);
	static bool sphere2Box(PhysicsObject*, PhysicsObject*);

	// AABB
	static bool aabb2Plane(PhysicsObject*, PhysicsObject*);
	static bool aabb2Sphere(PhysicsObject*, PhysicsObject*);
	static bool aabb2aabb(PhysicsObject*, PhysicsObject*);
	static bool aabb2Box(PhysicsObject*, PhysicsObject*);

	// Box
	static bool box2Plane(PhysicsObject * obj1, PhysicsObject * obj2);
	static bool box2Sphere(PhysicsObject*, PhysicsObject*);
	static bool box2aabb(PhysicsObject*, PhysicsObject*);
	static bool box2Box(PhysicsObject*, PhysicsObject*);

	static glm::vec2 distanceBetweenSpheres;


protected:
	std::vector<PhysicsObject*> m_actors;
	glm::vec2 m_gravity;
	float m_timeStep;
};


