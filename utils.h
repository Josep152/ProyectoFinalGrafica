#ifndef __UTILS_H__
#define __UTILS_H__

#define SCR_TITLE							"Cubo_Rubick_Muevete"
#define SCR_WIDTH							800
#define SCR_HEIGHT							600

#define X_AXIS								0
#define Y_AXIS								1
#define Z_AXIS								2

#define PI									3.14159265359
#define to_radians(x)						(x * (float) PI ) / 180.0f

#define CUBE_FRAGMENT_SHADER_PATH			"D:\\Programacion\\Computacion_Grafica\\Environment\\LabCompiler2023_II_CG\\glfw-master\\OwnProjects\\Project_CuboRubick\\shaders\\fShader.txt"
#define FRAGMENT_SHADER_PATH				"D:\\Programacion\\Computacion_Grafica\\Environment\\LabCompiler2023_II_CG\\glfw-master\\OwnProjects\\Project_CuboRubick\\shaders\\fragment_shader.txt"
#define VERTEX_SHADER_PATH					"D:\\Programacion\\Computacion_Grafica\\Environment\\LabCompiler2023_II_CG\\glfw-master\\OwnProjects\\Project_CuboRubick\\shaders\\vertex_shader.txt"
#define LIGHT_V_SHADER_PATH					"D:\\Programacion\\Computacion_Grafica\\Environment\\LabCompiler2023_II_CG\\glfw-master\\OwnProjects\\Project_CuboRubick\\shaders\\vs_basic_light_shader.txt"
#define LIGHT_F_SHADER_PATH					"D:\\Programacion\\Computacion_Grafica\\Environment\\LabCompiler2023_II_CG\\glfw-master\\OwnProjects\\Project_CuboRubick\\shaders\\fg_basic_light_shader.txt"


#define F_MOVEMENT							'F'
#define D_MOVEMENT							'D'
#define U_MOVEMENT							'U'
#define B_MOVEMENT							'B'
#define R_MOVEMENT							'R'
#define L_MOVEMENT							'L'
#define M_MOVEMENT							'M'
#define E_MOVEMENT							'E'
#define S_MOVEMENT							'S'

#define F_REVERSE_MOVEMENT					'f'
#define D_REVERSE_MOVEMENT					'd'
#define U_REVERSE_MOVEMENT					'u'
#define B_REVERSE_MOVEMENT					'b'
#define R_REVERSE_MOVEMENT					'r'
#define L_REVERSE_MOVEMENT					'l'

#define BLUE_COLOR							glm::vec4(0.2156f, 0.3215f, 0.5725f, 1.0f)
#define RED_COLOR							glm::vec4(0.6509f, 0.2705f, 0.1843f, 1.0f)
#define YELLOW_COLOR						glm::vec4(0.6941f, 0.6823f, 0.2470f, 1.0f) // 249 224 118   glm::vec4(1.0000f, 0.9921f, 0.3254f, 1.0f)
#define LIGH_YELLOW_COLOR					glm::vec4(0.6941f, 0.6549f, 0.1568f, 1.0f)
#define ORANGE_COLOR						glm::vec4(0.6862f, 0.4156f, 0.1607f, 1.0f)
#define GREEN_COLOR							glm::vec4(0.2705f, 0.5098f, 0.1372f, 1.0f)
#define WHITE_COLOR							glm::vec4(0.7176f, 0.7137f, 0.7294f, 1.0f) // 224 221 229
#define BLACK_COLOR							glm::vec4(0.1215f, 0.1254f, 0.1254f, 1.0f)

/* Camera */
#include "./camera.h"

static Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
static float lastX = SCR_WIDTH / 2.0f;
static float lastY = SCR_HEIGHT / 2.0f;
static bool firstMouse = true;

// Camera timing
static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

// Enable Camera
static bool process_Camera = true;

const char valid_moves[] = { F_MOVEMENT, D_MOVEMENT, U_MOVEMENT, B_MOVEMENT, R_MOVEMENT, L_MOVEMENT,
							 F_REVERSE_MOVEMENT, D_REVERSE_MOVEMENT, U_REVERSE_MOVEMENT, B_REVERSE_MOVEMENT, R_REVERSE_MOVEMENT, L_REVERSE_MOVEMENT };

const unsigned int prime_pattern[]		= { 2, 5, 8, 1, 4, 7, 0, 3, 6};
const unsigned int non_prime_pattern[]	= { 6, 3, 0 , 7, 4, 1, 8, 5, 2};

const unsigned int frontal_litter_idx[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
const unsigned int back_litter_idx[]	= { 20, 19, 18, 23, 22, 21, 26, 25, 24 };
const unsigned int up_litter_idx[]		= { 6, 7, 8, 15, 16, 17, 24, 25, 26 };
const unsigned int down_litter_idx[]	= { 18, 19, 20, 9, 10, 11, 0, 1, 2 };
const unsigned int left_litter_idx[]	= { 2, 11, 20, 5, 14, 23, 8, 17, 26 };
const unsigned int right_litter_idx[]	= { 0, 3, 6, 9, 12, 15, 18, 21, 24 };

const unsigned int clockwise_rotation_idx[] = { 18, 19, 20, 9, 10, 11, 0, 1, 2, 21, 22, 23, 12, 13, 14, 3, 4, 5, 24, 25, 26, 15, 16, 17, 6, 7, 8 };
const unsigned int non_clockwise_rotation_idx[] = { 6, 7, 8, 15, 16, 17, 24, 25, 26, 3, 4, 5, 12, 13, 14, 21, 22, 23, 0, 1, 2, 9, 10, 11, 18, 19, 20 };
const unsigned int x_view_idx[] = { 18, 9, 0, 21, 12, 3, 24, 15, 6, 19, 10, 1, 22, 13, 4, 25, 16, 7, 20, 11, 2, 23, 14, 5, 26, 17 ,8 };
const unsigned int y_view_idx[] = { 6, 3, 0, 7, 4, 1, 8, 5, 2, 15, 12, 9, 16, 13, 10, 17, 14, 11, 24, 21, 18, 25, 22, 19, 26, 23, 20 };
const unsigned int z_view_idx[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };


#endif // __UTILS_H__