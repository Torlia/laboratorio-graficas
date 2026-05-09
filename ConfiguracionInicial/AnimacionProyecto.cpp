// Animacion flujo personas

#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"

// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void Animation();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f, 2.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

glm::vec3 Light1 = glm::vec3(0);

// Bezier trayectory
struct BezierSegment {
	glm::vec3 P0, P1, P2, P3;
};

const int NUM_SEGMENTS = 3;
BezierSegment path[NUM_SEGMENTS] = {
	// Segment 0: Entrada -> Escaleras
	// P1/P2 desviados para rodear la trab circular (A)
	{
		glm::vec3(-5.0f, 0.0f,  5.0f),
		glm::vec3(-4.5f, 0.0f,  1.0f),
		glm::vec3(-1.5f, 0.0f, -1.5f),
		glm::vec3(0.0f, 0.0f, -4.0f)
	},
	// Segment 1: Escaleras -> Auditorio
	{
		glm::vec3(0.0f, 0.0f, -4.0f),
		glm::vec3(1.0f, 0.0f, -2.0f),
		glm::vec3(3.5f, 0.0f,  0.5f),
		glm::vec3(5.0f, 0.0f,  3.0f)
	},
	// Segment 2: Auditorio -> Stands -> Entrada (loop)
	{
		glm::vec3(5.0f, 0.0f,  3.0f),
		glm::vec3(3.0f, 0.0f,  7.0f),
		glm::vec3(-2.0f, 0.0f,  7.0f),
		glm::vec3(-5.0f, 0.0f,  5.0f)
	}
};

glm::vec3 CubicBezier(const BezierSegment& s, float t) {
	float u = 1.0f - t;
	return u * u * u * s.P0
		+ 3 * u * u * t * s.P1
		+ 3 * u * t * t * s.P2
		+ t * t * t * s.P3;
}

glm::vec3 CubicBezierTangent(const BezierSegment& s, float t) {
	float u = 1.0f - t;
	return 3.0f * (u * u * (s.P1 - s.P0) + 2 * u * t * (s.P2 - s.P1) + t * t * (s.P3 - s.P2));
}

// Woman anim var
float womanT = 0.0f;
int   womanSegment = 0;
float womanSpeed = 0.12f;

// Man anim var
float manT = 1.0f;
int   manSegment = 2;
float manSpeed = 0.10f;

glm::vec3 womanPos(0.0f, 0.0f, 0.0f);
float womanRot = 0.0f;
glm::vec3 manPos(0.0f);
float manRot = 0.0f;

float RightLeg = 0.0f;
float LeftLeg = 0.0f;
float RightArm = 0.0f;
float LeftArm = 0.0f;
bool  step = false;
float manRightLeg = 0.0f;
float manLeftLeg = 0.0f;
float manRightArm = 0.0f;
float manLeftArm = 0.0f;
bool  manStep = false;

// Deltatime
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Animacion flujo personas - Cecilia Torres", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

	// Models
	Model BodyWoman((char*)"Models/woman_torso.obj");
	Model HeadWoman((char*)"Models/woman_head.obj");
	Model W_RightLeg((char*)"Models/woman_right_leg.obj");
	Model W_LeftLeg((char*)"Models/woman_left_leg.obj");
	Model W_RightArm((char*)"Models/woman_right_arm.obj");
	Model W_LeftArm((char*)"Models/woman_left_arm.obj");
	Model BodyMan((char*)"Models/man_torso.obj");
	Model HeadMan((char*)"Models/man_head.obj");
	Model M_RightLeg((char*)"Models/man_right_foot.obj");
	Model M_LeftLeg((char*)"Models/man_left_foot.obj");
	Model M_RightArm((char*)"Models/man_right_hand.obj");
	Model M_LeftArm((char*)"Models/man_left_hand.obj");
	Model Piso((char*)"Models/piso.obj");

	// VAO / VBO
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		DoMovement();
		Animation();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp

		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);

		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));

		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

		glm::mat4 view;
		view = camera.GetViewMatrix();

		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model(1);

		// Floor
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);

		// Body (torso) — root bone, placed at the Bezier position
		// and rotated to face the walking direction
		model = glm::translate(glm::mat4(1.0f), womanPos);
		modelTemp = model = glm::rotate(model, glm::radians(womanRot), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BodyWoman.Draw(lightingShader);

		// Head — attached to torso, NO rotation (fixed, does not move)
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		HeadWoman.Draw(lightingShader);

		// Right Arm
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.05f, 0.8f, 0.0f));
		model = glm::rotate(model, glm::radians(RightArm), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		W_RightArm.Draw(lightingShader);

		// Left Arm
		model = modelTemp;
		model = glm::translate(model, glm::vec3(-0.05f, 0.8f, 0.0f));
		model = glm::rotate(model, glm::radians(LeftArm), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		W_LeftArm.Draw(lightingShader);

		// Right Leg
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.15f, 0.8f, 0.0f));
		model = glm::rotate(model, glm::radians(RightLeg), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		W_RightLeg.Draw(lightingShader);

		// Left Leg
		model = modelTemp;
		model = glm::translate(model, glm::vec3(-0.15f, 0.8f, 0.0f));
		model = glm::rotate(model, glm::radians(LeftLeg), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		W_LeftLeg.Draw(lightingShader);

		// --- CUERPO HOMBRE ---
		manPos.x += 1.0f;
		model = glm::translate(glm::mat4(1.0f), manPos);
		modelTemp = model = glm::rotate(model, glm::radians(manRot), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BodyMan.Draw(lightingShader);

		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		HeadMan.Draw(lightingShader);

		// Brazo Derecho Hombre (Forzando rotación)
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.005f, 0.7f, 0.0f)); // Posición hombro
		model = glm::rotate(model, glm::radians(manLeftArm), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.7f, 0.0f)); // Compensación eje
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		M_LeftArm.Draw(lightingShader);

		model = modelTemp;
		model = glm::translate(model, glm::vec3(-0.005f, 0.7f, 0.0f)); // Posición hombro
		model = glm::rotate(model, glm::radians(manRightArm), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.7f, 0.0f)); // Compensación eje
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		M_RightArm.Draw(lightingShader);

		// Pierna Derecha Hombre (Forzando rotación)
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.25f, 0.8f, 0.0f)); // Posición cadera
		model = glm::rotate(model, glm::radians(manRightLeg), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, 0.0f)); // Compensación eje
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		M_RightLeg.Draw(lightingShader);


		model = modelTemp;
		model = glm::translate(model, glm::vec3(-0.25f, 0.8f, 0.0f)); // Posición cadera
		model = glm::rotate(model, glm::radians(manLeftLeg), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, 0.0f)); // Compensación eje
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		M_LeftLeg.Draw(lightingShader);


		// Lamp cube
		lampShader.Use();
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		model = glm::mat4(1);
		model = glm::translate(model, pointLightPositions[0]);
		model = glm::scale(model, glm::vec3(0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void Animation()
{
	// --- Bezier path: advance t, roll over to next segment ---
	womanT += womanSpeed * deltaTime;

	if (womanT >= 1.0f) {
		womanT -= 1.0f;
		womanSegment = (womanSegment + 1) % NUM_SEGMENTS;
	}

	// Position from Bezier
	womanPos = CubicBezier(path[womanSegment], womanT);

	// Rotation from tangent so she faces her walking direction
	glm::vec3 tangent = CubicBezierTangent(path[womanSegment], womanT);
	if (glm::length(tangent) > 0.001f) {
		tangent = glm::normalize(tangent);
		womanRot = glm::degrees(atan2(tangent.x, tangent.z));
	}

	// --- Limb state machine: identical to original dog step logic ---
	// Right and Left always move in opposite phases (natural walk).
	// Arms oppose legs (right arm swings back when right leg goes forward).
	if (!step) { // State 1: swinging forward
		RightLeg += 0.2f;
		LeftLeg -= 0.2f;
		RightArm -= 0.2f;
		LeftArm += 0.2f;
		if (RightLeg > 5.0f) { // max angle reached, reverse
			step = true;
		}
	}
	else { // State 2: swinging backward
		RightLeg -= 0.2f;
		LeftLeg += 0.2f;
		RightArm += 0.2f;
		LeftArm -= 0.2f;
		if (RightLeg < -5.0f) { // max angle reached, go forward again
			step = false;
		}
	}

	// --- Lógica Hombre (Sentido opuesto) ---
	manT -= manSpeed * deltaTime; // Restamos t para ir hacia atrás

	if (manT <= 0.0f) {
		manT = 1.0f;
		manSegment = (manSegment - 1 + NUM_SEGMENTS) % NUM_SEGMENTS;
	}

	manPos = CubicBezier(path[manSegment], manT);

	// Tangente invertida para que mire al frente
	glm::vec3 manTangent = CubicBezierTangent(path[manSegment], manT);
	if (glm::length(manTangent) > 0.001f) {
		manTangent = glm::normalize(manTangent);
		// + 180 porque recorre la curva al revés
		manRot = glm::degrees(atan2(manTangent.x, manTangent.z)) + 180.0f;
	}

	// --- Movimiento de brazos/piernas del hombre ---
	if (!manStep) {
		manRightLeg += 0.2f; 
		manLeftLeg -= 0.2f;
		manRightArm -= 0.2f; 
		manLeftArm += 0.2f;
		if (manRightLeg > 5.0f) manStep = true;
	}
	else {
		manRightLeg -= 0.2f; 
		manLeftLeg += 0.2f;
		manRightArm += 0.2f; 
		manLeftArm -= 0.2f;
		if (manRightLeg < -5.0f) manStep = false;
	}
}

void DoMovement()
{
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (keys[GLFW_KEY_T]) pointLightPositions[0].x += 0.01f;
	if (keys[GLFW_KEY_G]) pointLightPositions[0].x -= 0.01f;
	if (keys[GLFW_KEY_Y]) pointLightPositions[0].y += 0.01f;
	if (keys[GLFW_KEY_H]) pointLightPositions[0].y -= 0.01f;
	if (keys[GLFW_KEY_U]) pointLightPositions[0].z -= 0.1f;
	if (keys[GLFW_KEY_J]) pointLightPositions[0].z += 0.01f;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)   keys[key] = true;
		else if (action == GLFW_RELEASE) keys[key] = false;
	}

	if (keys[GLFW_KEY_SPACE]) {
		active = !active;
		if (active)
			Light1 = glm::vec3(0.2f, 0.8f, 1.0f);
		else
			Light1 = glm::vec3(0);
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}