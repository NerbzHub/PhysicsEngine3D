#pragma once
#include "glm\glm.hpp"
#include "glm\vec2.hpp"
#include "Application.h"
#include "Renderer2D.h"


class PhysicsScene;
class Plane;
class Sphere;
class AABB;

class FixedTimeStepPhysicsDemoApp : public aie::Application {
public:

	FixedTimeStepPhysicsDemoApp();
	virtual ~FixedTimeStepPhysicsDemoApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	PhysicsScene* m_physicsScene;
	virtual void setupContinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity);

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	Plane* plane;
	Sphere* ball;
	Sphere* ball1;
	AABB* aabb;
};