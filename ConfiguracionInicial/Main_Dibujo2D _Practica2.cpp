//Cecilia Torres Bravo
//Fecha de entrega: 20 de febrero del 2026
//Numero de cuenta: 421040214
//Practica 2

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 900, HEIGHT = 1100;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Cecilia Torres - Gato con Primitivas en 2D", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		//Cola 
		0.555f, 0.045f, 0.0f, 1.0f, 0.761f, 0.820f, // 0. 5,-0.5 
		0.889f, -0.409f, 0.0f, 1.0f, 0.761f, 0.820f, // 1. 8,-4.5 
		0.778f, -0.636f, 0.0f, 1.0f, 0.761f, 0.820f, // 2. 7,-7 
		0.667f, -0.733f, 0.0f, 1.0f, 0.761f, 0.820f, // 3. 6,-8.5 
		0.667f, -1.00f, 0.0f, 1.0f, 0.761f, 0.820f, // 4. 6,-11 
		0.889f, -0.818f, 0.0f, 1.0f, 0.761f, 0.820f, // 5. 8,-9 
		0.444f, -0.818f, 0.0f, 1.0f, 0.761f, 0.820f, // 6. 4,-9 
		0.444f, -1.00f, 0.0f, 1.0f, 0.761f, 0.820f, // 7. 4,-11 
		
		//Cuerpo 
		0.444f, -0.273f, 0.0f, 1.0f, 0.761f, 1.0f, // 8. 4,-3 
		0.000f, 0.000f, 0.0f, 1.0f, 0.761f, 1.0f, // 9. 0,0 
		-0.389f, 0.182f, 0.0f, 1.0f, 0.761f, 1.0f, // 10. -3.5,2 
		-0.389f, -0.545f, 0.0f, 1.0f, 0.761f, 1.0f, // 11. -3.5,-6 
		0.000f, -0.818f, 0.0f, 1.0f, 0.761f, 1.0f, // 12. 0,-9 
		0.000f, -0.909f, 0.0f, 1.0f, 0.761f, 1.0f, // 13. 0,-10 
		-0.278f, -1.000f, 0.0f, 1.0f, 0.761f, 1.0f, // 14. -2.5,-11 
		0.000f, -1.00f, 0.0f, 1.0f, 0.761f, 1.0f, // 15. 0,-11 
		
		//Patitas 
		-0.389f, 0.318f, 0.0f, 1.0f, 1.0f, 0.820f, // 16. -3.5,3.5 
		-0.389f, -1.000f, 0.0f, 1.0f, 1.0f, 0.820f, // 17. -3.5,-11 
		-0.556f, -0.545f, 0.0f, 1.0f, 1.0f, 0.820f, // 18. -5,-6 
		-0.611f, -1.000f, 0.0f, 1.0f, 1.0f, 0.820f, // 19. -5.5,-11 
		-0.675f, -0.350f, 0.0f, 1.0f, 1.0f, 0.820f, // 20. -6.8,-3 
		-0.889f, 0.000f, 0.0f, 1.0f, 1.0f, 0.820f, // 21. -8,0 
		-0.778f, 0.364f, 0.0f, 1.0f, 1.0f, 0.820f, // 22. -7,4 
		-0.667f, 0.318f, 0.0f, 1.0f, 1.0f, 0.820f, // 23. -6,3.5 
		-0.778f, 0.000f, 0.0f, 1.0f, 1.0f, 0.820f, // 24. -7,0 
		-0.556f, 0.273f, 0.0f, 1.0f, 1.0f, 0.820f, // 25. -5,3 
		
		//Cabeza 
		-0.222f, 0.364f, 0.0f, 0.500f, 0.761f, 0.820f, // 26. -2,4 
		-0.222f, 0.545f, 0.0f, 0.500f, 0.761f, 0.820f, // 27. -2,6 
		-0.222f, 0.727f, 0.0f, 0.500f, 0.761f, 0.820f, // 28. -2,8 
		-0.500f, 0.636f, 0.0f, 0.500f, 0.761f, 0.820f, // 29. -4.5,7 
		-0.833f, 0.773f, 0.0f, 0.500f, 0.761f, 0.820f, // 30. -7.5,8.5 
		-0.833f, 0.591f, 0.0f, 0.500f, 0.761f, 0.820f, // 31. -7.5,6.5 
		-0.889f, 0.455f, 0.0f, 0.500f, 0.761f, 0.820f, // 32. -8,5 
		-0.611f, 0.409f, 0.0f, 0.500f, 0.761f, 0.820f, // 33. -5.5,4.5 
		-0.500f, 0.409f, 0.0f, 0.500f, 0.761f, 0.820f, // 34. -4.5,4.5 
		-0.556f, 0.364f, 0.0f, 0.500f, 0.761f, 0.820f, // 35. -5,4

		//Puntitos nariz
		-0.565f, 0.385f, 0.0f, 1.0f, 1.0f, 1.0f, // 36.
		-0.545f, 0.385f, 0.0f, 1.0f, 1.0f, 1.0f, // 37.
	};
	unsigned int indices[] = {  // note that we start from 0!
		// Cola
		0,1,2, //A
		5,1,2, //B
		2,3,5, //C
		3,4,5, //C
		3,6,4, //D
		6,7,4, //E
		
		// Cuerpo
		7,8,15, //F
		8,9,15, //G
		9,10,12, //H
		10,11,12, //H
		13,14,15, //I

		// Patitas
		16,24,17, //J
		20,18,19, //K
		18,21,24, //L
		22,23,24, //l
		22,24,21, //L
		23,25,24, //M
		16,25,24, //M

		// Cabeza
		25,26,34, //N
		25,35,34, //N
		34,27,26, //O
		27,28,29, //P
		29,30,31, //Q
		27,29,31, //R
		31,33,34, //R
		31,27,34, //R
		31,32,33, //S
		22,32,33, //T
		22,33,25, //U
		25,33,35, //U
		33,34,35, //V

		//Puntitos nariz
		36, 37, 
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);

		// Figura con relleno
		glDrawElements(GL_TRIANGLES, 93, GL_UNSIGNED_INT, 0); 

		//Contorno de la figura
		/*
		glPointSize(3); //Puntitos nariz
		glDrawArrays(GL_POINTS, 36, 3);
	
		glLineWidth(5.0f); //Contorno
		for (int i = 0; i < 93; i += 3)
		{
			glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (void*)(i * sizeof(unsigned int)));
		}
		*/
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}