#ifndef __VECTOR_3D__
#define __VECTOR_3D__

#include "point.h"
#include <math.h>

struct Vector3D
{
private:

public:

    Point direction;

    /* Constructors */

    Vector3D();
    Vector3D(float, float, float);
    Vector3D(Point&, Point&);
    Vector3D(const Point&);
    Vector3D(const Vector3D&);

    /* Overloads */

    bool operator == (const Vector3D&);
    bool operator != (const Vector3D&);
    Vector3D& operator = (const Vector3D&);
    Vector3D operator - (const Vector3D&);
    Vector3D operator + (const Vector3D&);
    Vector3D& operator += (const Vector3D&);
    Vector3D& operator -= (const Vector3D&);
    
    /* Getters */

    Vector3D unit();
    float norm();

    /* Auxiliar Functions */
    void print();
    
};

Vector3D::Vector3D()
{
    direction = Point();
}

Vector3D::Vector3D(float _x, float _y, float _z = 0.0f)
{
    Point temporal_point(_x, _y, _z);
    direction = temporal_point;
}

Vector3D::Vector3D(Point& start, Point& end) : direction(end - start)
{}

Vector3D::Vector3D(const Point& _direction) : direction(_direction)
{}

Vector3D::Vector3D(const Vector3D& _vector)
{
    *this = _vector;
}

bool Vector3D::operator == (const Vector3D& one)
{
    if (this->direction != one.direction) return false;
    return true;
}

bool Vector3D::operator != (const Vector3D& one)
{
    return !((*this) == one);
}

Vector3D& Vector3D::operator = (const Vector3D& _vector)
{
    this->direction = _vector.direction;
    return *this;
}

Vector3D Vector3D::operator - (const Vector3D& _vector)
{
    Vector3D temporal_vector((*this));
    temporal_vector.direction -= _vector.direction;
    return temporal_vector;
}

Vector3D Vector3D::operator + (const Vector3D& _vector)
{
    Vector3D temporal_vector((*this));
    temporal_vector.direction += _vector.direction;
    return temporal_vector;
}

Vector3D& Vector3D::operator += (const Vector3D& _vector)
{
    this->direction += _vector.direction;
    return *this;
}

Vector3D& Vector3D::operator -= (const Vector3D& _vector)
{
    this->direction -= _vector.direction;
    return *this;
}

Vector3D Vector3D::unit()
{
    Vector3D to_return(*this);
    to_return.direction.x /= this->norm();
    to_return.direction.y /= this->norm();
    to_return.direction.z /= this->norm();
    return to_return;
}

float Vector3D::norm()
{
    float ans = (this->direction.x * this->direction.x) + (this->direction.y * this->direction.y) + (this->direction.z * this->direction.z);
    ans = sqrt(ans);
    return ans;
}

void Vector3D::print()
{
    this->direction.print();
}


/* More Point Overloads */



#endif // __VECTOR_3D__