#ifndef __MATRIX_4D_H__
#define __MATRIX_4D_H__

#include "utils.h"
#include "vector3d.h"

class Matrix4D
{
public:
	
	/* Constructors & Destructor */

	Matrix4D();
	Matrix4D(const float&);
	Matrix4D(const std::vector<std::vector<float>>&);
	Matrix4D(const Matrix4D&);
	~Matrix4D();

	/* Auxiliar Methods */

	void rotate(float, const unsigned int&);
	void translate(const float&, const float&, const float&);
	void translate(const Vector3D&, bool invert);
	void scale(const float&, const float&, const float&);
	void print();

	/* Overloads */

	Matrix4D operator * (const Matrix4D&);
	Matrix4D& operator *= (const Matrix4D&);
	
	float matrix[4][4];

private:
	
};

Matrix4D::Matrix4D()
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

Matrix4D::Matrix4D(const float& diagonal)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (i == j) matrix[i][j] = diagonal;
			else matrix[i][j] = 0;
		}
	}
}

Matrix4D::Matrix4D(const std::vector<std::vector<float>>& one)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			matrix[i][j] = one[i][j];
		}
	}
}

Matrix4D::Matrix4D(const Matrix4D& one)
{
	*this = one;
}

Matrix4D::~Matrix4D()
{
}

void Matrix4D::rotate(float angle, const unsigned int& axis)
{
	float angle_in_radians = to_radians(angle);
	Matrix4D rotation;
	if (axis == X_AXIS)
	{
		std::vector<std::vector<float>> skeleton = {		{1,	0,						0,							0},
															{0, cosf(angle_in_radians), -sinf(angle_in_radians),	0},
															{0, sinf(angle_in_radians), cosf(angle_in_radians),		0},
															{0,	0,						0,							1}
		};

		rotation = Matrix4D(skeleton);
	}
	else if (axis == Y_AXIS)
	{
		std::vector<std::vector<float>> skeleton = {		{cosf(angle_in_radians),	0,	sinf(angle_in_radians),	0},
															{0,							1,	0,						0},
															{-sinf(angle_in_radians),	0,	cosf(angle_in_radians), 0},
															{0,							0,	0,						1}
		};
		rotation = Matrix4D(skeleton);
	}
	else if (axis == Z_AXIS)
	{
		std::vector<std::vector<float>> skeleton = {		{cosf(angle_in_radians),	-sinf(angle_in_radians),	0,	0},
															{sinf(angle_in_radians),	cosf(angle_in_radians),		0,	0},
															{0,							0,							1,	0},
															{0,							0,							0,	1}
		};
		rotation = Matrix4D(skeleton);
	}

	*this = (*this) * rotation;
}

void Matrix4D::translate(const float& x_translate, const float& y_translate, const float& z_translate)
{
	Matrix4D translation(1.0f);
	translation.matrix[X_AXIS][3] = x_translate;
	translation.matrix[Y_AXIS][3] = y_translate;
	translation.matrix[Z_AXIS][3] = z_translate;

	*this = (*this) * translation;
}

void Matrix4D::translate(const Vector3D& direction, bool invert = false)
{
	Matrix4D translation(1.0f);
	translation.matrix[X_AXIS][3] = direction.direction.x;
	translation.matrix[Y_AXIS][3] = direction.direction.y;
	translation.matrix[Z_AXIS][3] = direction.direction.z;
	
	if (invert == true)
	{
		translation.matrix[X_AXIS][3] = -direction.direction.x;
		translation.matrix[Y_AXIS][3] = -direction.direction.y;
		translation.matrix[Z_AXIS][3] = -direction.direction.z;
	}

	*this = (*this) * translation;
}


void Matrix4D::scale(const float& x_scale, const float& y_scale, const float& z_scale)
{
	Matrix4D scalation(1.0f);
	scalation.matrix[X_AXIS][X_AXIS] = x_scale;
	scalation.matrix[Y_AXIS][Y_AXIS] = y_scale;
	scalation.matrix[Z_AXIS][Z_AXIS] = z_scale;

	*this = (*this) * scalation;
}

void Matrix4D::print()
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			std::cout << matrix[i][j] << "\t ";
		}
		std::cout << "\n";
	}
}

Matrix4D Matrix4D::operator * (const Matrix4D& one)
{
	Matrix4D temporal_matrix;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				temporal_matrix.matrix[i][j] += this->matrix[i][k] * one.matrix[k][j];
			}
		}
	}
	return temporal_matrix;
}

Matrix4D& Matrix4D::operator *= (const Matrix4D& one)
{
	Matrix4D temporal_matrix;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				temporal_matrix.matrix[i][j] += this->matrix[i][k] * one.matrix[k][j];
			}
		}
	}
	*this = temporal_matrix;

	return *this;
}

#endif // !__MATRIX_H__