#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>

struct Point {

private:

public:

    float x, y, z;

    /* Constructors */

    Point();
    Point(const Point&);
    Point(float, float, float);

    /* Overloads */

    bool operator == (const Point&);
    bool operator != (const Point&);
    Point& operator = (const Point&);
    Point& operator += (const Point&);
    Point& operator -= (const Point&);
    Point& operator /= (const int&);
    Point operator / (const int&);
    Point operator - (const Point&);
    Point operator + (const Point&);
    

    /* Auxiliar Functions s*/
    void print();
};

Point::Point() : x(0.0f), y(0.0f), z(0.0f)
{}

Point::Point(const Point& one)
{
    *this = one;
}

Point::Point(float _x, float _y, float _z = 0.0f) : x(_x), y(_y), z(_z)
{}

bool Point::operator == (const Point& one)
{
    if (this->x != one.x) return false;
    if (this->y != one.y) return false;
    if (this->z != one.z) return false;
    return true;
}

bool Point::operator != (const Point& one)
{
    return !((*this) == one);
}

Point& Point::operator = (const Point& one)
{
    this->x = one.x;
    this->y = one.y;
    this->z = one.z;
    return *this;
}

Point Point::operator - (const Point& one)
{
    Point temporal_point((*this));
    temporal_point.x -= one.x;
    temporal_point.y -= one.y;
    temporal_point.z -= one.z;
    return temporal_point;
}

Point Point::operator + (const Point& one)
{
    Point temporal_point((*this));
    temporal_point.x += one.x;
    temporal_point.y += one.y;
    temporal_point.z += one.z;
    return temporal_point;
}

Point& Point::operator += (const Point& one)
{
    this->x += one.x;
    this->y += one.y;
    this->z += one.z;
    return *this;
}

Point& Point::operator -= (const Point& one)
{
    this->x -= one.x;
    this->y -= one.y;
    this->z -= one.z;
    return *this;
}

Point& Point::operator /= (const int& divider)
{
    this->x /= divider;
    this->y /= divider;
    this->z /= divider;
    return *this;
}

Point Point::operator / (const int& divider)
{
    Point temporal_point(*this);
    temporal_point.x /= divider;
    temporal_point.y /= divider;
    temporal_point.z /= divider;
    return temporal_point;
}

void Point::print()
{
    std::cout << "(" << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
}

#endif // !__POINT_H__