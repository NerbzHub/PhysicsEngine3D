#pragma once
#include <glm\glm.hpp>
#include <glm\vec2.hpp>
#include <Gizmos.h>
#include <list>

enum ShapeType {
	PLANE = 0,
	SPHERE,
	ENUMAABB,
	BOX,
	SHAPE_COUNT,
};


class PhysicsObject
{
public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};
	virtual ShapeType getShapeID() {return m_shapeID;}


protected:
	PhysicsObject(ShapeType a_ShapeID) : m_shapeID(a_ShapeID) {}
	ShapeType m_shapeID;
};

