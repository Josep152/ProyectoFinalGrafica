#include <iostream>

#include "directories.h"
#include "utils.h"

#include "rubik.h"


using namespace std;

void menu()
{
	cout << "Press: " << std::endl;
	cout << "1 -> Camada frontal" << endl;
	cout << "2 -> Camada trasera" << endl;
	cout << "3 -> Camada de Abajo" << endl;
	cout << "4 -> Camada de Arriba" << endl;
	cout << "5 -> Camada Izquierda" << endl;
	cout << "6 -> Camada Derecha " << endl;
	cout << "7 -> Camada MedioVertical " << endl;
	cout << "8 -> Camada MedioHorizontal " << endl;
	cout << "9 -> Respirar " << endl;
	cout << "0 -> Exhalar " << endl;

	cout << "Una vez que escriba todos los movimientos que desea hacer, presione ENTER para aplicarlos al cubo." << endl;


}

float diameter = 0.1f;

void framebuffer_size_callback(GLFWwindow*, int, int);
void key_callback(GLFWwindow*, int, int, int, int);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Point center(0.0f, 0.0f, 0.0f);
Point center_1(0.0f, 0.0f, -0.3f);
Point center_2(-0.3f, 0.0f, 0.0f);
Point center_3(0.3f, 0.3f, 0.0f);

Rubik* CuboRubick;
Cube* Cubo_1; Cube* Cubo_2; Cube* Cubo_3; //Cube* Cubo_proof;
	
int revers = 0;

int main()
{
	GLFWwindow* window;
	unsigned int width = SCR_WIDTH, height = SCR_HEIGHT;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, SCR_TITLE, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);


	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGL(glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;
		exit(-1);
	}

	glEnable(GL_DEPTH_TEST);
	
	CuboRubick = new Rubik(center, diameter);
	
	
	// = new Cube(center,diameter);
	/////////////////////////////////////
	Cubo_1 = new Cube(center_1, 0.025f, false); Cubo_2 = new Cube(center_2, 0.025f, false); Cubo_3 = new Cube(center_3, 0.025f, false);
	for (int i = 0; i < 6; i++) {
		Cubo_1->face_colors.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		Cubo_2->face_colors.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		Cubo_3->face_colors.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		//Cubo_proof->face_colors.push_back(RED_COLOR);
	}
	//->apply_color();
	Cubo_1->apply_color();
	Cubo_2->apply_color();
	Cubo_3->apply_color();
	/////////////////////////////////////
	//Cubo_proof->print();
	
	
	
	
	menu();
	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.482f, 0.655f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	
		CuboRubick->render();
		
		Cubo_1->render(false);
		Cubo_2->render(false);
		Cubo_3->render(false);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(FORWARD, 0.01);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(BACKWARD, 0.01);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(LEFT, 0.01);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(RIGHT, 0.01);
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)
	{
		revers++;
		revers %= 2;
		if (revers) std::cout << "Reverse Movements activated!" << std::endl;
		else std::cout << "Reverse Movements desactivated!" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		CuboRubick->enable();
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		CuboRubick->scramble();
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		CuboRubick->solve();
	}
	if (revers)
	{
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		{
			CuboRubick->read_moves(F_REVERSE_MOVEMENT);
			CuboRubick->append(F_REVERSE_MOVEMENT);
			CuboRubick->enable();
			
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		{
			CuboRubick->read_moves(B_REVERSE_MOVEMENT);
			CuboRubick->append(B_REVERSE_MOVEMENT);
			CuboRubick->enable();
		}
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		{
			CuboRubick->read_moves(U_REVERSE_MOVEMENT);
			CuboRubick->append(U_REVERSE_MOVEMENT);
			CuboRubick->enable();
		}
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		{
			CuboRubick->read_moves(D_REVERSE_MOVEMENT);
			CuboRubick->append(D_REVERSE_MOVEMENT);
			CuboRubick->enable();
		}
		if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		{
			CuboRubick->read_moves(R_REVERSE_MOVEMENT);
			CuboRubick->append(R_REVERSE_MOVEMENT);
			CuboRubick->enable();
		}
		if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		{
			CuboRubick->read_moves(L_REVERSE_MOVEMENT);
			CuboRubick->append(L_REVERSE_MOVEMENT);
			CuboRubick->enable();
		}
		if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		{
			CuboRubick->read_moves(B_MOVEMENT);
			CuboRubick->append(B_MOVEMENT);
			CuboRubick->enable();
			CuboRubick->render();
			Cubo_1->render(false);
			Cubo_2->render(false);
			Cubo_3->render(false);
			
			CuboRubick->read_moves(F_REVERSE_MOVEMENT);
			CuboRubick->append(F_REVERSE_MOVEMENT);
			CuboRubick->enable();
			CuboRubick->render();
			Cubo_1->render(false);
			Cubo_2->render(false);
			Cubo_3->render(false);
		}
		if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
		{
			CuboRubick->read_moves(D_MOVEMENT);
			CuboRubick->append(D_MOVEMENT);
			CuboRubick->enable();
			CuboRubick->render();
			Cubo_1->render(false);
			Cubo_2->render(false);
			Cubo_3->render(false);
			
			CuboRubick->read_moves(U_REVERSE_MOVEMENT);
			CuboRubick->append(U_REVERSE_MOVEMENT);
			CuboRubick->enable();
			CuboRubick->render();
			Cubo_1->render(false);
			Cubo_2->render(false);
			Cubo_3->render(false);
		}
	}
	else
	{
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		{
			CuboRubick->read_moves(F_MOVEMENT);
			CuboRubick->append(F_MOVEMENT);
			CuboRubick->enable();
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		{
			CuboRubick->read_moves(B_MOVEMENT);
			CuboRubick->append(B_MOVEMENT);
			CuboRubick->enable();
		}
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		{
			CuboRubick->read_moves(U_MOVEMENT);
			CuboRubick->append(U_MOVEMENT);
			CuboRubick->enable();
		}
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		{
			CuboRubick->read_moves(D_MOVEMENT);
			CuboRubick->append(D_MOVEMENT);
			CuboRubick->enable();
		}
		if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		{
			CuboRubick->read_moves(R_MOVEMENT);
			CuboRubick->append(R_MOVEMENT);
			CuboRubick->enable();
		}
		if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		{
			CuboRubick->read_moves(L_MOVEMENT);
			CuboRubick->append(L_MOVEMENT);
			CuboRubick->enable();
		}
		if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		{
			CuboRubick->read_moves(F_MOVEMENT);
			CuboRubick->append(F_MOVEMENT);
			CuboRubick->enable();
			CuboRubick->render();
			Cubo_1->render(false);
			Cubo_2->render(false);
			Cubo_3->render(false);
			
			CuboRubick->read_moves(B_REVERSE_MOVEMENT);
			CuboRubick->append(B_REVERSE_MOVEMENT);
			CuboRubick->enable();
			CuboRubick->render();
			Cubo_1->render(false);
			Cubo_2->render(false);
			Cubo_3->render(false);
		}
		if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
		{
			CuboRubick->enable();
			CuboRubick->read_moves(U_MOVEMENT);
			CuboRubick->append(U_MOVEMENT);
			CuboRubick->render();
			Cubo_1->render(false);
			Cubo_2->render(false);
			Cubo_3->render(false);
			
			CuboRubick->enable();
			CuboRubick->read_moves(D_REVERSE_MOVEMENT);
			CuboRubick->append(D_REVERSE_MOVEMENT);
			CuboRubick->render();
			Cubo_1->render(false);
			Cubo_2->render(false);
			Cubo_3->render(false);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		CuboRubick->enable();
		CuboRubick->set_expanding();
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		CuboRubick->enable();
		CuboRubick->set_retracting();
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	{
		CuboRubick->Respirar();
	}
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	if (process_Camera)
	{
		camera->ProcessMouseMovement(xoffset, yoffset);
		//cout << "x: " << xoffset << " y: " << yoffset << '\n';
	}
	//else
		//camera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}