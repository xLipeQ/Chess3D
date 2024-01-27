#pragma once

#include <GL/glew.h>
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak(); 
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Model;
class VertexArray;
class IndexBuffer;
class Mesh;

class Renderer
{
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Draw(const Model& model, Shader& shader) const;
	void Clear() const;
};