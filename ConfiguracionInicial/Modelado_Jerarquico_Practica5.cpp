// Cecilia Torres Bravo
// 421040214
// Practica 5
// 13/03/2026

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//For model
float	hombro = 0.0f;
float   codo = 0.0f;
float	munieca = 0.0f;
float	dedo1A = 0.0f;
float	dedo1B = 0.0f;
float	dedo1C = 0.0f;
float	dedo2A = 0.0f;
float	dedo2B = 0.0f;
float	dedo2C = 0.0f;
float	dedo3A = 0.0f;
float	dedo3B = 0.0f;
float	dedo3C = 0.0f;
float	dedo4A = 0.0f;
float	dedo4B = 0.0f;
float	dedo4C = 0.0f;
float	dedo5A = 0.0f;
float	dedo5B = 0.0f;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado jerarquico - Cecilia Torres - Practica 5", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection


	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 
		0.5f, -0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		-0.5f,  0.5f, 0.5f, 
		-0.5f, -0.5f, 0.5f, 
		
	    -0.5f, -0.5f,-0.5f, 
		 0.5f, -0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
	    -0.5f,  0.5f,-0.5f, 
	    -0.5f, -0.5f,-0.5f, 
		
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,
      
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		
		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color= glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp



		//View set up 
		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	

		glBindVertexArray(VAO);
		
		//Modelo bicep
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //hombro
		modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//A

		// Modelo antebrazo
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//B

		// Modelo munieca
		model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f)); //Checkpoint, regresamos al valor anterior
		model = glm::rotate(model, glm::radians(munieca), glm::vec3(1.0f, 0.0f, 0.0f));
		modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//C

		// Modelo dedo 1A
		model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, 0.375f));
		model = glm::rotate(model, glm::radians(dedo1A), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D

		// Modelo dedo 1B
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo1B), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		// Modelo dedo 1C
		model = glm::translate(modelTemp, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo1C), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//F

		// Modelo dedo 2A
		model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.35f, -0.375f)); //regresamos a la munieca
		model = glm::rotate(model, glm::radians(dedo2A), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//G

		// Modelo dedo 2B
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2B), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//H

		// Modelo dedo 2C
		model = glm::translate(modelTemp, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2C), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//I

		// Modelo dedo 3A
		model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.35f, 0.125f));
		model = glm::rotate(model, glm::radians(dedo3A), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//J

		// Modelo dedo 3B
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo3B), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//K

		// Modelo dedo 3C
		model = glm::translate(modelTemp, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo3C), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//L

		// Modelo dedo 4A
		model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.35f, -0.125f));
		model = glm::rotate(model, glm::radians(dedo4A), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//M

		// Modelo dedo 4B
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo4B), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//N

		// Modelo dedo 4C
		model = glm::translate(modelTemp, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo4C), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//O

		// Modelo dedo 5A
		model = glm::translate(modelTemp2, glm::vec3(0.25f, -0.35f, 0.375f));
		model = glm::rotate(model, glm::radians(dedo5A), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//P

		// Modelo dedo 5B
		model = glm::translate(modelTemp, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo5B), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//Q

		glBindVertexArray(0);

		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.08f;
	 if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.18f;

	 // Hombro
	 if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		 hombro += 0.18f;
		 hombro = glm::clamp(hombro, -180.0f, 45.0f);
	 if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		 hombro -= 0.18f;
		 hombro = glm::clamp(hombro, -180.0f, 45.0f);

	// Codo
	 if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		 codo += 0.18f;
		 codo = glm::clamp(codo, 0.0f, 145.0f);
	 if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		 codo -= 0.18f;
		 codo = glm::clamp(codo, 0.0f, 145.0f);
		 
	// Munieca
	 if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		 munieca += 0.18f;
		 munieca = glm::clamp(munieca, -80.0f, 70.0f);
	 if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		 munieca -= 0.18f;
		 munieca = glm::clamp(munieca, -80.0f, 70.0f);

	 // Dedo 1
	 if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		 dedo1A += 0.18f;
		 dedo1A = glm::clamp(dedo1A, -85.0f, 85.0f);
	 if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		 dedo1A -= 0.18f;
		 dedo1A = glm::clamp(dedo1A, -85.0f, 85.0f);
	 if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		 dedo1B += 0.18f;
		 dedo1B = glm::clamp(dedo1B, -100.0f, 100.0f);
	 if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		 dedo1B -= 0.18f;
		 dedo1B = glm::clamp(dedo1B, -100.0f, 100.0f);
	 if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		 dedo1C += 0.18f;
		 dedo1C = glm::clamp(dedo1C, -80.0f, 80.0f);
	 if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		 dedo1C -= 0.18f;
		 dedo1C = glm::clamp(dedo1C, -80.0f, 80.0f);

	 // Dedo 2
	 if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		 dedo2A += 0.18f;
		 dedo2A = glm::clamp(dedo2A, -85.0f, 85.0f);
	 if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		 dedo2A -= 0.18f;
		 dedo2A = glm::clamp(dedo2A, -85.0f, 85.0f);
	 if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		 dedo2B += 0.18f;
		 dedo2B = glm::clamp(dedo2B, -100.0f, 100.0f);
	 if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		 dedo2B -= 0.18f;
		 dedo2B = glm::clamp(dedo2B, -100.0f, 100.0f);
	 if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		 dedo2C += 0.18f;
		 dedo2C = glm::clamp(dedo2C, -80.0f, 80.0f);
	 if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		 dedo2C -= 0.18f;
		 dedo2C = glm::clamp(dedo2C, -80.0f, 80.0f);

	 // Dedo 3
	 if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		 dedo3A += 0.18f;
		 dedo3A = glm::clamp(dedo3A, -85.0f, 85.0f);
	 if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
		 dedo3A -= 0.18f;
		 dedo3A = glm::clamp(dedo3A, -85.0f, 85.0f);
	 if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
		 dedo3B += 0.18f;
		 dedo3B = glm::clamp(dedo3B, -100.0f, 100.0f);
	 if (glfwGetKey(window, GLFW_KEY_SLASH) == GLFW_PRESS)
		 dedo3B -= 0.18f;
		 dedo3B = glm::clamp(dedo3B, -100.0f, 100.0f);
	 if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		 dedo3C += 0.18f;
		 dedo3C = glm::clamp(dedo3C, -80.0f, 80.0f);
	 if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		 dedo3C -= 0.18f;
		 dedo3C = glm::clamp(dedo3C, -80.0f, 80.0f);

	 // Dedo 4
	 if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		 dedo4A += 0.18f;
		 dedo4A = glm::clamp(dedo4A, -85.0f, 85.0f);
	 if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		 dedo4A -= 0.18f;
		 dedo4A = glm::clamp(dedo4A, -85.0f, 85.0f);
	 if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		 dedo4B += 0.18f;
		 dedo4B = glm::clamp(dedo4B, -100.0f, 100.0f);
	 if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		 dedo4B -= 0.18f;
		 dedo4B = glm::clamp(dedo4B, -100.0f, 100.0f);
	 if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		 dedo4C += 0.18f;
		 dedo4C = glm::clamp(dedo4C, -80.0f, 80.0f);
	 if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
		 dedo4C -= 0.18f;
		 dedo4C = glm::clamp(dedo4C, -80.0f, 80.0f);

	 // Dedo 5
	 if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
		 dedo5A += 0.18f;
		 dedo5A = glm::clamp(dedo5A, -50.0f, 50.0f);
	 if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		 dedo5A -= 0.18f;
		 dedo5A = glm::clamp(dedo5A, -50.0f, 50.0f);
	 if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
		 dedo5B += 0.18f;
		 dedo5B = glm::clamp(dedo5B, -85.0f, 85.0f);
	 if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		 dedo5B -= 0.18f;
		 dedo5B = glm::clamp(dedo5B, -85.0f, 85.0f);

 }
 


