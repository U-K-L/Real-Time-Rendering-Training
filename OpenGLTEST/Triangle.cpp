#include "Triangle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

using namespace std;
unsigned int VBO, VAO, EBO; //vertex buffer object. allocates space.
unsigned int shaderProgram;

//The string of shader code. RAW STRING LITERALS.
const GLchar *vertexShaderSource = R"(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	void main()
	{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	})";

//This decides the color.
const GLchar *fragmentShaderSource = R"(
	#version 330 core
	out vec4 FragColor;
	void main()
    {
	FragColor = vec4(1.0f, 0.5f, 0.8f, 1.0f);
	})";


Triangle::Triangle()
{

	//--------------------------------
	//Goals:
	//Initialize Vertex data in a VBO
	//Setup shaders
	//Linked all of the data.
	//Managed the memory.


	//creates a triangle shape.
	float verticies[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	//Second triangle.
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

		//Compiling shaders!
	unsigned int shader; //allocate space. create variable.
	unsigned int fragShader;

	shader = glCreateShader(GL_VERTEX_SHADER);//type of shader to create.
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	
	//get shader file to compile. shader is just a string of commands for GLSL.
	glShaderSource(shader, 1, &vertexShaderSource, NULL); //get shader source, initialize.
	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);

	glCompileShader(shader); //compile shader.
	glCompileShader(fragShader);


	//---------------------------
	//Create a shaderProgram.
	shaderProgram = glCreateProgram();


	//Attach those shaders.
	glAttachShader(shaderProgram, shader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram); //Finalizing the program.


	glUseProgram(shaderProgram); //We now use our program shader!

	//Now lets delete the shaders we no longer need!
	glDeleteShader(fragShader);
	glDeleteShader(shader);






	//---------------------------------------
	//Time to instruct OpenGL how to handle the memory.
	glVertexAttribPointer(0, //What vertex to order? Where?
		3, //The size, the dimension, vec3 = 3
		GL_FLOAT, //What data type? GL_FLOAT == floats
		GL_FALSE, //Should data be normalized? All values between 1-0
		3*sizeof(float), //The size of the array. The Stride.
		(void*)0 //Where does it start?
		);
	glEnableVertexAttribArray(0); //enable it, with the location.
		
		

	//-------------------------
	//Checks if everything worked.
	int success;
	char infoLog[512];

	//Check the shader-------------------
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog <<
			std::endl;
	}
	else
		cout << "it worked!" << endl;

	//Check the program shader-------------------
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog <<
			std::endl;
	}
	else
		cout << "it worked!" << endl;
	//-----------------------------



	//Let's create a way to store all of this data.
	//A VAO.
	glGenVertexArrays(1, &VAO); //Geenerate array and give ID.

	//Create element buffer object.
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Initialization Done. Now to Draw.
	//---------------------------------
	//Lets draw our hard work!

	glBindVertexArray(VAO); //Must happen first!

	//copy verticies into a buffer.
	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	//Now for EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Set the pointers.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);





}

void Triangle::render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Can decide if line or not.
	//use the shader program
	glUseProgram(shaderProgram);

	//Bind Object.
	glBindVertexArray(VAO);

	//Draw the object!!!
	glDrawArrays(GL_POINTS, 100, 6);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //What we want to draw, how many verticies (6) Type? Offset?

	//glBindVertexArray(0); //Do not unbind for multiple objects.
}


Triangle::~Triangle()
{
}
