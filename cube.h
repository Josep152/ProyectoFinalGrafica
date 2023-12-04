#ifndef __CUBE_H__
#define __CUBE_H__

#include "square.h"
#include "shader.h"

class Cube
{
public:

	/* Constructors & Destructors */

	Cube();
	Cube(const Point&, const float&, bool kind = true);
	~Cube();

	/* Auxiliar Methods */

	void setUp();
	void render(bool light = true);
	void transform(const Matrix4D&);

	void apply_color();
	void insert_colors();
	void print();

	/* Getters */

	Point get_center();

	std::vector<Square*> squares;
	std::vector<glm::vec4> face_colors;
	
private:
	Shader cube_colors;
};

Cube::Cube()
{
}

Cube::Cube(const Point& center, const float& separation, bool kind)
{
	if (kind) { 
		cube_colors = Shader(LIGHT_V_SHADER_PATH, LIGHT_F_SHADER_PATH);
	}
	else {
		std::cout << "creating diferent \n";
		cube_colors = Shader(VERTEX_SHADER_PATH, CUBE_FRAGMENT_SHADER_PATH);
	}
	
	std::vector<Point> centers(6);

	centers[0] = Point(center.x, center.y, center.z);								/*	Front Face	*/
	centers[5] = Point(center.x, center.y, center.z + (separation * 2));			/*	Back Face	*/

	centers[1] = Point(center.x, center.y + separation, center.z + separation);		/*	Top Face	*/
	centers[4] = Point(center.x, center.y - separation, center.z + separation);		/*	Bottom Face	*/

	centers[2] = Point(center.x + separation, center.y, center.z + separation);		/*	Right Face	*/
	centers[3] = Point(center.x - separation, center.y, center.z + separation);		/*	Left Face	*/

	squares = std::vector<Square*>(6);

	squares[0] = new Square(centers[0], separation, Z_AXIS, -1);
	squares[5] = new Square(centers[5], separation, Z_AXIS, 1);

	squares[1] = new Square(centers[1], separation, Y_AXIS, 1);
	squares[4] = new Square(centers[4], separation, Y_AXIS, -1);

	squares[2] = new Square(centers[2], separation, X_AXIS, 1);
	squares[3] = new Square(centers[3], separation, X_AXIS, -1);

	setUp();

}
 
Cube::~Cube()
{
	for (int i = 0; i < squares.size(); i++)
	{
		delete squares[i];
	}
}

void Cube::setUp()
{
	for (size_t i = 0; i < squares.size(); i++)
	{
		squares[i]->setUp();
	}
}

void Cube::render(bool light)
{
	cube_colors.use();
	cube_colors.classical_movement();

	cube_colors.setInt("material.diffuse", 0);
    cube_colors.setInt("material.specular", 1);
	
	cube_colors.setVec3("viewPos", camera->Position);
	cube_colors.setFloat("material.shininess", 32.0f);
	cube_colors.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    cube_colors.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    cube_colors.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    cube_colors.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	cube_colors.setVec3("dirLight.lightColor", 1.0f, 1.0f, 1.0f);
	// point light 1
	cube_colors.setVec3("pointLights[0].position", 0.0f, 0.0f, -0.3f);
	cube_colors.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	cube_colors.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	cube_colors.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	cube_colors.setFloat("pointLights[0].constant", 1.0f);
	cube_colors.setFloat("pointLights[0].linear", 0.09f);
	cube_colors.setFloat("pointLights[0].quadratic", 0.032f);
	cube_colors.setVec3("pointLights[0].lightColor", 1.0f, 1.0f, 1.0f);
	// point light 2
	cube_colors.setVec3("pointLights[1].position", -0.3f, 0.0f, 0.0f);
	cube_colors.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	cube_colors.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	cube_colors.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	cube_colors.setFloat("pointLights[1].constant", 1.0f);
	cube_colors.setFloat("pointLights[1].linear", 0.09f);
	cube_colors.setFloat("pointLights[1].quadratic", 0.032f);
	cube_colors.setVec3("pointLights[1].lightColor", 0.0f, 1.0f, 0.0f);
	// point light 3
	cube_colors.setVec3("pointLights[2].position", 0.3f, 0.3f, 0.0f);
	cube_colors.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	cube_colors.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	cube_colors.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	cube_colors.setFloat("pointLights[2].constant", 1.0f);
	cube_colors.setFloat("pointLights[2].linear", 0.09f);
	cube_colors.setFloat("pointLights[2].quadratic", 0.032f);
	cube_colors.setVec3("pointLights[2].lightColor", 0.5f, 1.0f, 1.0f);
	// spotLight
	cube_colors.setVec3("spotLight.position", camera->Position);
	cube_colors.setVec3("spotLight.direction", camera->Front);
	cube_colors.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	cube_colors.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	cube_colors.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	cube_colors.setVec3("spotLight.lightColor", 1.0f, 1.0f, 1.0f);
	cube_colors.setFloat("spotLight.constant", 1.0f);
	cube_colors.setFloat("spotLight.linear", 0.09f);
	cube_colors.setFloat("spotLight.quadratic", 0.032f);
	cube_colors.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	cube_colors.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));  

	cube_colors.setVec4Color("ourColor", face_colors[0]);
	this->squares[0]->render();

	cube_colors.setVec4Color("ourColor", face_colors[1]);
	this->squares[1]->render();

	cube_colors.setVec4Color("ourColor", face_colors[2]);
	this->squares[2]->render();

	cube_colors.setVec4Color("ourColor", face_colors[3]);
	this->squares[3]->render();

	cube_colors.setVec4Color("ourColor", face_colors[4]);
	this->squares[4]->render();
		
	cube_colors.setVec4Color("ourColor", face_colors[5]);
	this->squares[5]->render();

}

void Cube::apply_color()
{
	cube_colors.use();
	cube_colors.classical_movement();

	cube_colors.setVec4Color("ourColor", glm::vec4(2.0f, 2.0f, 2.0f, 1.0f) * face_colors[0]);
	this->squares[0]->render();

	cube_colors.setVec4Color("ourColor", glm::vec4(2.0f, 2.0f, 2.0f, 1.0f) * face_colors[1]);
	this->squares[1]->render();

	cube_colors.setVec4Color("ourColor", glm::vec4(2.0f, 2.0f, 2.0f, 1.0f) * face_colors[2]);
	this->squares[2]->render();

	cube_colors.setVec4Color("ourColor", glm::vec4(2.0f, 2.0f, 2.0f, 1.0f) * face_colors[3]);
	this->squares[3]->render();

	cube_colors.setVec4Color("ourColor", glm::vec4(2.0f, 2.0f, 2.0f, 1.0f) * face_colors[4]);
	this->squares[4]->render();

	cube_colors.setVec4Color("ourColor", glm::vec4(2.0f, 2.0f, 2.0f, 1.0f) * face_colors[5]);
	this->squares[5]->render();
}

void Cube::insert_colors()
{

}

void Cube::transform(const Matrix4D& transformation)
{
	for (size_t i = 0; i < squares.size(); i++)
	{
		squares[i]->transform(transformation);
	}
}

Point Cube::get_center()
{
	Point first_center = squares[0]->get_center();
	Point second_center = squares[5]->get_center();

	first_center /= 2, second_center /= 2;
	first_center += second_center;
	return first_center;
}

void Cube::print()
{
    for(int i = 0; i < squares.size(); i++) {
		std::cout << "Faces:\n";
		squares[i]->print();
	}
}

#endif // !__CUBE_H__