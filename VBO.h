#pragma once

#include <vector>
#include <glad/glad.h>
#include "Vector3.h"

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vector3>& vertices, GLsizeiptr size);
	VBO();
	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();

	// Updates the VBO
	void Update(std::vector<Vector3>& vertices, GLsizeiptr size);
};