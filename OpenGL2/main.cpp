// OpenGL2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "GL\glew.h"
#include "GL\glut.h"
#include "GLFW\glfw3.h"
#include "Init_Window.h"
#include "Triangle.h"
#include "LoadShaders.h"
#include "glm\glm.hpp"
#include "Transform.h"
#include "MVP.h"
#include "Cube.h"
#include "Color.h"

using namespace INIT_WINDOW;

//Nicht verzagen - nach pointer fragen
static GLfloat* color_change_buffer[12*3*3];



int main()
{
	Init_Window* window = new Init_Window;
	window->SetGLFWHints(4, 4, 3, GL_TRUE);
	window->CheckInitGLFW();
	GLFWwindow* windowLive = window->SetWindowProperties(1920, 1080, "Test", NULL, NULL);

	Triangle* triangle = new Triangle();
	Cube* cube = new Cube();
	Color* color = new Color();

	GLuint VertexArrayID;				
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("Vertex_Shader.glsl", "Fragment_Shader.glsl");
	
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, triangle->GetTriangleSize(), triangle->GetTriangleData(), GL_DYNAMIC_DRAW);
	

	GLuint vertexbuffer2;
	glGenBuffers(1, &vertexbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	glBufferData(GL_ARRAY_BUFFER, cube->GetCubeSize(), cube->GetCubeData(), GL_DYNAMIC_DRAW);
	
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, color->GetColorSize(), color->GetColorData(), GL_DYNAMIC_DRAW);
	
	glClearColor(0.02f, 0.2f, 0.4f, 0.0f);
	MVP* mvp = new MVP;
	
	GLuint MatrixID = glGetUniformLocation(programID, "mvp");
	GLuint TransformationID = glGetUniformLocation(programID, "transformation");
	Transform Transformation;
	glm::mat4 Hello = mvp->CreateMVPMatrix(45, 1920, 1080);

	float Red = 0.00f;
	float Blue = 0.00f;
	float Green = 0.00f;
	float xPos = 0.00f;
	float yPos = 0.00f;
	float xRot = 0.00f;
	float yRot = 0.0f;
	float zRot = 0.00f;

	glEnable(GL_CULL_FACE);
	//DISPLAY LOOP - DONT TOUCH THIS SCARY PIECE OF CODE
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
	
		Transformation.SetPos(glm::vec3(xPos, yPos, 1.0f));
		Transformation.SetRotation(glm::vec3(zRot, yRot, xRot));
		Transformation.SetScale(glm::vec3(0.8f));
		glm::mat4 trans = Transformation.GetModel();
		glUniformMatrix4fv(TransformationID, 1, GL_FALSE, &trans[0][0]);
		

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Hello[0][0]);
		glfwPollEvents();
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		//color->fadingColor(Red, Green, Blue);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, color->GetColorSize(), color->GetColorData(), GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 12*3);
		glDisableVertexAttribArray(0);
		glfwSwapBuffers(windowLive);
		glfwSetInputMode(windowLive, GLFW_STICKY_KEYS, GL_TRUE);

		if (glfwGetKey(windowLive, GLFW_KEY_RIGHT) == GLFW_PRESS) xRot += 0.001f;
		if (glfwGetKey(windowLive, GLFW_KEY_UP) == GLFW_PRESS) yRot += 0.001f;
		if (glfwGetKey(windowLive, GLFW_KEY_LEFT) == GLFW_PRESS) xRot -= 0.001f;
		if (glfwGetKey(windowLive, GLFW_KEY_DOWN) == GLFW_PRESS) zRot -= 0.001f;

		//if (glfwGetKey(windowLive, GLFW_KEY_R == GLFW_PRESS)) {
			//printf("Rotation Mode:");

			//while (GLFW_KEY_R == GLFW_PRESS) {
			//	if (glfwGetKey(windowLive, GLFW_KEY_D) == GLFW_PRESS) 
			//  if (glfwGetKey(windowLive, GLFW_KEY_W) == GLFW_PRESS)
			//	if (glfwGetKey(windowLive, GLFW_KEY_A) == GLFW_PRESS)
			//	if (glfwGetKey(windowLive, GLFW_KEY_S) == GLFW_PRESS)
			//}
		//}
	
	} while (glfwGetKey(windowLive, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(windowLive) == 0);
	
}


