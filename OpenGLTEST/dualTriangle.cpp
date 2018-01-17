#include "dualTriangle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

unsigned int points_VBO;
unsigned int points_VBO2; //For second triangle.

const GLchar *vertexShaderSource = R"(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	void main()
	{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	})";

const GLchar *fragmentShaderSource = R"(
	#version 330 core
	out vec4 FragColor;
	void main()
    {
	FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);
	})";

const GLchar *yellowShaderSource = R"(
	#version 330 core
	out vec4 FragColor;
	void main()
    {
	FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);
	})";


dualTriangle::dualTriangle()
{
	//First need to create verticies. for double triangle.
	float tri1[] = {
		-0.5f, -0.5f, 0.0f,//Bottom left
		0.0f, 0.5f, 0.0f,//Top
		0.5f, -0.5f, 0.0f//Bottom right
	};

	float tri2[] = {
		-0.5f, -0.5f, 0.0f,//Bottom left
		0.0f, 0.5f, 0.0f,//Top
		0.5f, -0.5f, 0.0f//Bottom right
	};

	//Lets create a VBO. VBO Just stores all of our data/points into a large array.
	glGenBuffers(1, &points_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, points_VBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), tri1, GL_STATIC_DRAW);

	//Lets make a VBO for our second triangle.
	glGenBuffers(1, &points_VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, points_VBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), tri2, GL_STATIC_DRAW);

	//Lets start to create the shaders.
	unsigned int shader;
	shader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int colorShader;
	unsigned int colorShader2;
	colorShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Lets do something with these shaders.

}


dualTriangle::~dualTriangle()
{
}
