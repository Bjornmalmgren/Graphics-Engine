#include "config.h"
#include "ShaderResource.h"
ShaderResource::ShaderResource() : vertexBuffer(0), fragmentBuffer(0)
{
	program = 0;
}
ShaderResource::~ShaderResource() {

}
void ShaderResource::SetUpShader(std::string VertexPath, std::string FragmentPath) {
	vbuf = LoadShaderFromFile(VertexPath, GL_VERTEX_SHADER);
	fbuf = LoadShaderFromFile(FragmentPath, GL_FRAGMENT_SHADER);
	vertexBuffer = vbuf;
	fragmentBuffer = fbuf;

	GLint shaderLogSize;


	// create a program object
	this->program = glCreateProgram();
	glAttachShader(this->program, this->vertexBuffer);
	glAttachShader(this->program, this->fragmentBuffer);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
		this->compilerLog.append(buf);
		printf("[PROGRAM LINK ERROR]: %s", buf);
		delete[] buf;
	}
	glDeleteShader(vertexBuffer);
	glDeleteShader(fragmentBuffer);

}
void ShaderResource::CreateProgram() {
	this->program = glCreateProgram();
	glAttachShader(this->program, this->vertexBuffer);
	glAttachShader(this->program, this->fragmentBuffer);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
		this->compilerLog.append(buf);
		printf("[PROGRAM LINK ERROR]: %s", buf);
		delete[] buf;
	}
}
void ShaderResource::SetUpShader() {
	vbuf = LoadShaderFromFile("../../../engine/render/vertexShaderOld.glvs", GL_VERTEX_SHADER);
	fbuf = LoadShaderFromFile("../../../engine/render/fragmentShaderOld.glfs", GL_FRAGMENT_SHADER);
	vertexBuffer = vbuf;
	fragmentBuffer = fbuf;

	GLint shaderLogSize;


	// create a program object
	this->program = glCreateProgram();
	glAttachShader(this->program, this->vertexBuffer);
	glAttachShader(this->program, this->fragmentBuffer);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
		this->compilerLog.append(buf);
		printf("[PROGRAM LINK ERROR]: %s", buf);
		delete[] buf;
	}
	glDeleteShader(vertexBuffer);
	glDeleteShader(fragmentBuffer);

}


void ShaderResource::UseProgram() {
	glUseProgram(this->program);
}

GLint ShaderResource::UniformLocation(std::string name) {
	return glGetUniformLocation(this->program, name.c_str());
}
std::vector<GLint> ShaderResource::EnableTextures(std::vector<std::string> textures) {
	std::vector<GLint> textes;
	
	for (size_t i = 0; i < textures.size(); i++)
	{
		
		textes.push_back(glGetUniformLocation(this->program, textures[i].c_str()));
	}
	
	
	return textes;
}

GLuint ShaderResource::LoadShaderFromFile(std::string path, GLenum shaderType) {
	GLuint shaderId = 0;
	std::string shaderString;
	std::ifstream sourceFile(path.c_str());

	if (sourceFile) {
		shaderString.assign((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
		shaderId = glCreateShader(shaderType);
		if (shaderType == GL_VERTEX_SHADER) {
			vsBuffer = shaderString.c_str();
			glShaderSource(shaderId, 1, (const GLchar**)&vsBuffer, NULL);
		}
		else if (shaderType == GL_FRAGMENT_SHADER) {
			frBuffer = shaderString.c_str();
			glShaderSource(shaderId, 1, (const GLchar**)&frBuffer, NULL);
		}

		//const GLchar* shaderSource = shaderString.c_str();
		glCompileShader(shaderId);

		// get error log
		GLint shaderLogSize;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderInfoLog(shaderId, shaderLogSize, NULL, buf);
			printf("[SHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}
	}
	else
	{
		printf("Unable to open file %s\n", path.c_str());
	}
	return shaderId;

}