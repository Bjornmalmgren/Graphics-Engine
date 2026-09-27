#pragma once
#include "config.h"
#include "GL/glew.h"
#include <string>
#include <fstream>
#include "iostream"
#include "core/mat4.h"
#include <vector>
class ShaderResource
{
public:
	ShaderResource();
	~ShaderResource();
	void SetUpShader(std::string VertexPath, std::string FragmentPath);
	void SetUpShader();
	GLuint LoadShaderFromFile(std::string path, GLenum shaderType);
	void UseProgram();
	std::vector<GLint> EnableTextures(std::vector<std::string> textures);
	void CreateProgram();
	GLint UniformLocation(std::string name);
	const GLchar* vsBuffer;
	const GLchar* frBuffer;
	GLuint vertexBuffer;
	GLuint fragmentBuffer;
	GLuint program;
	GLuint fbuf;
	GLuint vbuf;
private:
	std::string compilerLog;
	GLint shaderLogSize;
};

