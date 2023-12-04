#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>

#include "math.h"

class Object
{
public:
	
	/* Constructors */
	Object();
	~Object();

	/* Getters */

	std::vector<Point> get_vertices();
	size_t size();
	Point& front();

	/* Auxiliar methods */
	void print();
	void push(const Point&);
	void move(const Vector3D&);
	void transform(const Matrix4D&);
	void rotate(float, const unsigned int&);

	std::vector<unsigned int> indices;
	std::vector<float> textureCoords;

	std::vector<Point> vertices;

private:
};

Object::Object()
{
}

Object::~Object()
{
}

std::vector<Point> Object::get_vertices()
{
	return this->vertices;
}

size_t Object::size()
{
	return this->vertices.size();
}

Point& Object::front()
{
	return this->vertices.front();
}

void Object::print()
{
	for (size_t i = 0; i < this->size(); i++)
	{
		this->vertices[i].print();
	}
}

void Object::push(const Point& to_push)
{
	this->vertices.emplace_back(to_push);
}

void Object::move(const Vector3D& direction)
{
	for (size_t i = 0; i < this->size(); i++)
	{
		vertices[i] += direction;
	}
}

void Object::transform(const Matrix4D& transformation)
{
	for (int i = 0; i < size(); i++)
	{
		vertices[i] = transformation * vertices[i];
	}
}

void Object::rotate(float angle, const unsigned int& axis)
{
	for (int i = 0; i < this->size(); i++)
	{
		Matrix4D transformation(1.0f);
		transformation.translate(0.2f, 0.2f, 0.0f);
		transformation.rotate(angle, axis);
		transformation.translate(-0.2f, -0.2f, 0.0f);
		vertices[i] = transformation * vertices[i]; 
	}
}

#endif // !__OBJECT_H__