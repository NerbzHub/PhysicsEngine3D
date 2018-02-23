#include "PhysicsScene.h"


PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
}

void PhysicsScene::update(float dt)
{
	static std::list<PhysicsObject*> dirty;

	// update physics at a fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;
	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;
		checkForCollision();
		// check for collisions (ideally you'd want to have some sort of
		// scene management in place)
		/*for (auto pActor : m_actors)
		{
			for (auto pOther : m_actors)
			{*/


			//if (pActor == pOther)
				//continue;
			//if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
				//std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
				//continue;

			/*RigidBody* pRigid = dynamic_cast<RigidBody*>(pActor);
			if (pRigid->checkCollision(pOther) == true)
			{
				pRigid->applyForceToActor(dynamic_cast<RigidBody*>(pOther),
					pRigid->getVelocity() * pRigid->getMass());
				dirty.push_back(pRigid);
				dirty.push_back(pOther);
			}*/


			/*	}
			}
			dirty.clear();*/

	}
}
void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{

}

void PhysicsScene::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors) {
		std::cout << count << " : ";
		pActor->debug();
		count++;
	}
}

// function pointer array for doing our collisions 
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] = {
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere, PhysicsScene::plane2aabb, PhysicsScene::plane2Box, 
	PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere, PhysicsScene::sphere2aabb, PhysicsScene::sphere2Box,
	PhysicsScene::aabb2Plane, PhysicsScene::aabb2Sphere, PhysicsScene::aabb2aabb, PhysicsScene::aabb2Box, 
	PhysicsScene::box2Plane, PhysicsScene::box2Sphere, PhysicsScene::box2aabb, PhysicsScene::box2Box };

void PhysicsScene::checkForCollision() {
	int actorCount = m_actors.size();
	//need to check for collisions against all objects except this one. 
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeId1 = object1->getShapeID();
			int shapeId2 = object2->getShapeID();
			// using function pointers 
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				// did a collision occur? 
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

bool PhysicsScene::plane2Plane(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::plane2aabb(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::plane2Box(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere *sphere = dynamic_cast<Sphere*>(obj1);
	Plane *plane = dynamic_cast<Plane*>(obj2);

	//if we are successful then test for collision 
	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->getNormal();
		glm::vec2 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());
		float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();
		// if we are behind plane then we flip the normal 
		if (sphereToPlane < 0)
		{
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}
		float intersection = sphere->getRadius() - sphereToPlane;
		if (intersection > 0)
		{
			glm::vec2 nullVec2(0, 0);

			//set sphere velocity to zero here 
			//sphere->setVelocity(nullVec2);
			plane->resolveCollision(sphere, contact);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	//try to cast objects to sphere and sphere 
	Sphere *sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere *sphere2 = dynamic_cast<Sphere*>(obj2);


	//if we are successful then test for collision 

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		glm::vec2 contact = 0.5f * (sphere1->getPosition() + sphere2->getPosition());

		glm::vec2 displacement = sphere1->getPosition() - sphere2->getPosition();

		glm::vec2 collNormal = normalize(displacement);

		float deltaXSquared;
		float deltaYSquared;
		float sumRadiiSquared;

		deltaXSquared = sphere1->getPosition().x - sphere2->getPosition().x;
		deltaXSquared *= deltaXSquared;

		deltaYSquared = sphere1->getPosition().y - sphere2->getPosition().y;
		deltaYSquared *= deltaYSquared;

		sumRadiiSquared = sphere1->getRadius() + sphere2->getRadius();
		sumRadiiSquared *= sumRadiiSquared;

		if (deltaXSquared + deltaYSquared <= sumRadiiSquared)
		{
			glm::vec2 nullVec2(0, 0);
			//Collision
			//sphere1->setVelocity(nullVec2);
			//sphere2->setVelocity(nullVec2);
			sphere1->resolveCollision(sphere2, contact, &collNormal);
			return true;
		}

		







		//this is where the collision detection happens 
		//you need code which sets the velocity of the two spheres to zero 
		//if they are overlapping 



		// get distance between 2 spheres 
		//distanceBetweenSpheres = sphere2->getPosition() - sphere1->getPosition();

		// if distance is less than the combined radius of 
		// both spheres, then a collision occurred so set the 
		// velocity of both spheres to 0 (we will add collision resolution later)
		//if (distanceBetweenSpheres < )
		//{
		//	//velocity = 0
		//}
	}

	return false;
}

bool PhysicsScene::sphere2aabb(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::sphere2Box(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::aabb2Plane(PhysicsObject *, PhysicsObject *)
{

	return false;
}

bool PhysicsScene::aabb2Sphere(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::aabb2aabb(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::aabb2Box(PhysicsObject *, PhysicsObject *)
{
	return false;
}



bool PhysicsScene::box2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box *box = dynamic_cast<Box*>(obj1);
	Plane *plane = dynamic_cast<Plane*>(obj2);
	//if we are successful then test for collision
	if (box != nullptr && plane != nullptr)
	{
		int numContacts = 0;
		glm::vec2 contact(0, 0);
		float contactV = 0;
		float radius = 0.5f * std::fminf(box->getWidth(), box->getHeight());
		// which side is the centre of mass on?
		glm::vec2 planeOrigin = plane->getNormal() * plane->getDistance();
		float comFromPlane = glm::dot(box->getPosition() - planeOrigin, plane->getNormal());
		// check all four corners to see if we've hit the plane
		for (float x = -box->getExtents().x;
			x < box->getWidth();
			x += box->getWidth())
		{
			for (float y = -box->getExtents().y; y < box->getHeight(); y += box->getHeight())
			{
				// get the position of the corner in world space
				glm::vec2 p = box->getPosition() + x * box->getLocalX() + y * box->getLocalY();
				float distFromPlane = glm::dot(p - planeOrigin, plane->getNormal());
				// this is the total velocity of the point
				float velocityIntoPlane = glm::dot(box->getVelocity() + box->getRotation() *
					(-y * box->getLocalX() + x * box->getLocalY()), plane->getNormal());
				// if this corner is on the opposite side from the COM,
				// and moving further in, we need to resolve the collision
				if ((distFromPlane > 0 && comFromPlane < 0 && velocityIntoPlane > 0) ||
					(distFromPlane < 0 && comFromPlane > 0 && velocityIntoPlane < 0))
				{
					numContacts++;
					contact += p;
					contactV += velocityIntoPlane;
				}
			}
		}

		// we've had a hit - typically only two corners can contact
		if (numContacts > 0)
		{
			// get the average collision velocity into the plane
			// (covers linear and rotational velocity of all corners involved)
			float collisionV = contactV / (float)numContacts;
			// get the acceleration required to stop (restitution = 0) or reverse
			// (restitution = 1) the average velocity into the plane
			glm::vec2 acceleration = -plane->getNormal() * ((1.0f + box->getElasticity()) * collisionV);
			// and the average position at which we'll apply the force
			// (corner or edge centre) 
			glm::vec2 localContact = (contact / (float)numContacts) - box->getPosition();
			// this is the perpendicular distance we apply the force at relative to
			// the COM, so Torque = F*r
			float r = glm::dot(localContact, glm::vec2(plane->getNormal().y, -plane->getNormal().x));
			// work out the "effective mass" - this is a combination of moment of
			// inertia and mass, and tells us how much the contact point velocity
			// will change with the force we're applying
			float mass0 = 1.0f / (1.0f / box->getMass() + (r*r) / box->getMoment());
			// and apply the force 
			box->applyForce(acceleration * mass0, localContact);
		}
	}
	return false;
}

bool PhysicsScene::box2Sphere(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::box2aabb(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::box2Box(PhysicsObject *, PhysicsObject *)
{
	return false;
}

// this helped me with the aabb https://www.gamasutra.com/view/feature/3015/pool_hall_lessons_fast_accurate_.php