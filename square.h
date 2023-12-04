#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "./object.h"
#include "./utils.h"
#include "./directories.h"

class Square : public Object
{
public:
	
	/* Constructors & Destructors */
	Square();
	Square(const Point&, float, const unsigned int& = Z_AXIS, float = 1.0);
	~Square();

	/* Auxiliar Methods */

	void setUp();
	void render();
	void update();
	void print();
	
	/* Getters */
	
	Point get_center();

	unsigned int VAO, VBO[2], EBO; /* (VBO[0]->vertices) | (VBO[1]->textures) */ 

private:

};

Square::Square()
{
	VAO = EBO = VBO[0] = VBO[1] = 0;
}

Square::Square(const Point& center, float separation, const unsigned int& axis, float up_)
{

	Point top_right(center), top_left(center), down_right(center), down_left(center);
	Point normal_;						 /////////////////////
	Vector3D top_right_direction, top_left_direction, down_right_direction, down_left_direction;

	if (axis == X_AXIS)
	{
		top_right_direction = Vector3D(0.0f, separation, separation), top_left_direction = Vector3D(0.0f, -separation, separation),
		down_right_direction = Vector3D(0.0f, separation, -separation), down_left_direction = Vector3D(0.0f, -separation, -separation);
		normal_.x = up_*1.0f;
		normal_.y = 0.0f;
		normal_.z = 0.0f;
	}

	else if (axis == Y_AXIS)
	{
		top_right_direction = Vector3D(separation, 0.0f, separation), top_left_direction = Vector3D(-separation, 0.0f, separation),
		down_right_direction = Vector3D(separation, 0.0f, -separation), down_left_direction = Vector3D(-separation, 0.0f, -separation);
		normal_.x = 0.0f;
		normal_.y = up_*1.0f;
		normal_.z = 0.0f;
	}

	else if (axis == Z_AXIS)
	{
		top_right_direction = Vector3D(separation, separation, 0.0f), top_left_direction = Vector3D(-separation, separation, 0.0f),
		down_right_direction = Vector3D(separation, -separation, 0.0f), down_left_direction = Vector3D(-separation, -separation, 0.0f);
		normal_.x = 0.0f;
		normal_.y = 0.0f;
		normal_.z = up_*1.0f;
	}

	top_right += top_right_direction;
	top_left += top_left_direction;
	down_right += down_right_direction;
	down_left += down_left_direction;

	push(top_left);
	push(normal_);
	push(top_right);
	push(normal_);
	push(down_right);
	push(normal_);
	push(down_left);
	push(normal_);

	this->indices = { 0, 1, 2, 2, 3, 0 };
	this->textureCoords = { 0.0f, 1.0f,
							1.0f, 1.0f,
							1.0f, 0.0f,
							1.0f, 0.0f,
							0.0f, 0.0f,
							0.0f, 1.0f	};

	setUp();
}

Square::~Square()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(2, this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

void Square::setUp()
{
	/* Buffer Generators */
	
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO[0]);
	glGenBuffers(1, &this->EBO);

	/* Setting Up Buffers*/

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO[0]); /* Vertices */
	glBufferData(GL_ARRAY_BUFFER, this->size() * sizeof(this->front()), &this->front(), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * (sizeof(Point)), (void*)0);
	glEnableVertexAttribArray(0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * (sizeof(Point)), (void*)(sizeof(Point)));
	
	/* Bind Texture (missing) */
	
	/* Binding Element Buffer Object */

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(this->indices.front()), &this->indices.front(), GL_STATIC_DRAW);

	/* Unbinding Buffers */

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Square::render()
{
	this->update();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Square::update()
{
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, this->size() * sizeof(this->front()), &this->front(), GL_STATIC_DRAW);
}

Point Square::get_center()
{
	Point one = vertices[0] + vertices[2];
	Point two = vertices[4] + vertices[6];
	one /= 4, two /= 4;
	one += two;
	return one;
}

void Square::print()
{
    for(int i = 0; i < vertices.size(); i++) {
		vertices[i].print();
	}
}

#endif // !__SQUARE_H__