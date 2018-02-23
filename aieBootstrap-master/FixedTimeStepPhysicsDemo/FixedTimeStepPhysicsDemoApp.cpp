#include "FixedTimeStepPhysicsDemoApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "PhysicsScene.h"
#include <Gizmos.h>
#include <glm\ext.hpp>
#include <glm\glm.hpp>
#include <glm\vec2.hpp>
#include "Sphere.h"
#include "Plane.h"
#include "AABB.h"

// this is for imgui for glClear()
#include "gl_core_4_4.h"


#define M_PI 3.1415926

FixedTimeStepPhysicsDemoApp::FixedTimeStepPhysicsDemoApp()
{

}

FixedTimeStepPhysicsDemoApp::~FixedTimeStepPhysicsDemoApp()
{

}

bool FixedTimeStepPhysicsDemoApp::startup()
{


	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();


	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setTimeStep(0.01f);
	m_physicsScene->setGravity(glm::vec2(0.0f, -10.0f));


	//m_physicsScene = new PhysicsScene();
	//m_physicsScene->setTimeStep(0.05f);
	//m_physicsScene->setGravity(glm::vec2(0.0f, -10.0f));

	float radius = 1.0f;
	float speed = 30;
	glm::vec2 startPos(-40, 0);
	float inclination = (float)M_PI / 4.0f;

	//setupContinuousDemo(startPos, inclination, speed, -10);

	//m_physicsScene->addActor(new Sphere(startPos, inclination, speed, 1, radius, glm::vec4(1, 0, 0, 1)));

	/*Sphere* ball;
	Sphere* ball1;*/

	//>>>>>>> 7467d712ba543740a1cbe35e5d163f13de83a765

		/*ball = new Sphere(glm::vec2(10, 50), glm::vec2(0, 0), 10.0f, 1, glm::vec4(1, 0, 0, 1));
		m_physicsScene->addActor(ball);
		ball1 = new Sphere(glm::vec2(-10, 50), glm::vec2(0, 0), 10.0f, 1, glm::vec4(0, 1, 0, 1));
		m_physicsScene->addActor(ball1);*/
		//ball->applyForceToActor(ball1, glm::vec2(20, 20));

	ball = new Sphere(glm::vec2(-70, 20), glm::vec2(0, 0), 4.0f, 6, glm::vec4(1, 0, 0, 1));
	ball1 = new Sphere(glm::vec2(10, 10), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 0, 1));
	plane = new Plane(glm::vec2(0, 1), (-10));
	aabb = new AABB(glm::vec2(20, 10), glm::vec2(5, 5), glm::vec2(0, 0), 1, glm::vec4(1, 0, 1, 1));

	ball->applyForce(glm::vec2(70, 0), glm::vec2(0, 0));
	ball1->applyForce(glm::vec2(-50, 0), glm::vec2(0, 0));
	aabb->applyForce(glm::vec2(20, 0), glm::vec2(0, 0));

	m_physicsScene->addActor(ball);
	m_physicsScene->addActor(ball1);
	m_physicsScene->addActor(plane);
	m_physicsScene->addActor(aabb);

	//rocket = new Rocket(glm::vec2(0, -85), glm::vec2(0, 0), 4000.0f, 10, glm::vec4(0, 1, 0, 1));
	//m_physicsScene->addActor(rocket);

	/*Sphere* ball;
	ball = new Sphere(glm::vec2(-40, 0), glm::vec2(10, 30), 3.0f, 1, glm::vec4(1, 0, 0, 1));
	m_physicsScene->addActor(ball);*/

	return true;
}

void FixedTimeStepPhysicsDemoApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void FixedTimeStepPhysicsDemoApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();
	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void FixedTimeStepPhysicsDemoApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));



	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}


void FixedTimeStepPhysicsDemoApp::setupContinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity)
{
	float t = 0;
	float tStep = 0.5f;
	float radius = 1.0f;
	int segments = 12;
	glm::vec4 colour = glm::vec4(1, 1, 0, 1);

	while (t <= 5)
	{
		//calculate the x, y position of the projectile at time t
		glm::vec2 incl = glm::vec2(sin(inclination), cos(inclination));

		float x = startPos.x + (incl.x * speed * t);
		float y = startPos.y + (incl.y * speed * t) + ((gravity * t*t) / 2.0f);

		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, colour);
		t += tStep;
	}
}

