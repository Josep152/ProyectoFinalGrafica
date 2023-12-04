#ifndef __MATH_H__
#define __MATH_H__

#include <vector>

#include "matrix4d.h"
#include "vector3d.h"

/* More Point Overloads */

Point operator + (const Point& _point, const Vector3D& _vector)
{
    Point to_return(_point);
    to_return += _vector.direction;
    return to_return;
}

Point operator - (const Point& _point, const Vector3D& _vector)
{
    Point to_return(_point);
    to_return -= _vector.direction;
    return to_return;
}

Point& operator -= (Point& _point, const Vector3D& _vector)
{
    _point -= _vector.direction;
    return _point;
}

Point& operator += (Point& _point, const Vector3D& _vector)
{
    _point += _vector.direction;
    return _point;
}

Point operator * (const Matrix4D& _matrix, const Point& _point)
{
    std::vector<float> modified_vertex = { _point.x, _point.y, _point.z, 1.0f };
    std::vector<float> ans = { 0.0f, 0.0f, 0.0f, 0.0f };

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            ans[i] += (_matrix.matrix[i][j] * modified_vertex[j]);
        }
    }

    ans.pop_back();
    Point to_return(ans[0], ans[1], ans[2]);

    return to_return;

}

Point& operator *= (Point& _point, const Matrix4D& _matrix)
{
    std::vector<float> modified_vertex = { _point.x, _point.y, _point.z, 0.0f };
    std::vector<float> ans = { 0.0f, 0.0f, 0.0f, 0.0f };

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            ans[i] += (_matrix.matrix[i][j] * modified_vertex[j]);
        }
    }

    ans.pop_back();
    
    _point.x = ans[0], _point.y = ans[1], _point.z = ans[2];

    return _point;
    
}

#endif // !__MATH_H__