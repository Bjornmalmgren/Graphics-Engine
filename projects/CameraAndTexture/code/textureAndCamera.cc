//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "textureAndCamera.h"
#include <cstring>
#include "imgui.h"
#include <windows.h>
#define STRING_BUFFER_SIZE 8192

const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec4 color;\n"
"layout(location=2) in vec2 texCord;\n"
"layout(location=0) out vec4 Color;\n"
"layout(location=2) out vec2 TexCord;\n"
"uniform mat4 rotation;\n"//rotation variable
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"	gl_Position =rotation* vec4(pos, 1) * view* projection ;\n"//adds rotation to the position
"	Color = color;\n"
"   TexCord = texCord;\n"
"}\n";

const GLchar* ps =
"#version 430\n"
"layout(location=2) in vec2 TexCord;\n"
"layout(location=0) in vec4 color;\n"
"out vec4 Color;\n"
"uniform sampler2D Texture;\n"
"void main()\n"
"{\n"
"	Color = color;\n"
"   Color = texture(Texture,TexCord);\n"
"}\n";

using namespace Display;


namespace Example
{

//------------------------------------------------------------------------------
/**
*/
ImGuiExampleApp::ImGuiExampleApp() : vertexShader(0), pixelShader(0), program(0)
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
ImGuiExampleApp::~ImGuiExampleApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
void
ImGuiExampleApp::Close()
{
	if (this->window->IsOpen())
		mesh.deleteResources();
		this->window->Close();

	Core::App::Close();
}

//------------------------------------------------------------------------------
/**
*/

bool
ImGuiExampleApp::Open()
{
	App::Open();
	this->window = new Display::Window;
	//window.
	window->SetSize(1080, 720);
	
	
	
	

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	
		
		this->vsBuffer = new GLchar[STRING_BUFFER_SIZE];
		this->fsBuffer = new GLchar[STRING_BUFFER_SIZE];

		// copy the hardcoded shader into buffer
		strncpy_s(this->vsBuffer, STRING_BUFFER_SIZE, vs, STRING_BUFFER_SIZE);
		strncpy_s(this->fsBuffer, STRING_BUFFER_SIZE, ps, STRING_BUFFER_SIZE);
		
		
		
		this->CompileShaders();

		return true;
	}
	return false;
}





//------------------------------------------------------------------------------
/**
*/

void
ImGuiExampleApp::Run()
{	
	
	glEnable(GL_DEPTH_TEST);
	GLint rot = glGetUniformLocation(this->program, "rotation");//binds to the rotation variable
	GLint views = glGetUniformLocation(this->program, "view");
	GLint projectins = glGetUniformLocation(this->program, "projection");
	GLint img = glGetUniformLocation(this->program, "Texture");
	GLint hasTexture = glGetUniformLocation(this->program, "hasTexture");
	text.LoadFromFile("../projects/CameraAndTexture/Texture/1384063.png",0);
	float time = 0; //time variable for rotation
	Render::Grid grid;
	while (this->window->IsOpen())
	{
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->window->Update();
		glUseProgram(this->program);

		Camera camera;
		const float radius = 5.0f;
		float camX = sinf(time) * radius;
		float camZ = cosf(time) * radius;
		camera.createCamera(vec3(camX, 3, camZ), vec3(0, 0, -1), vec3(0, 1, 0));
		mat4 view = camera.getViewMatrix();


		mat4 projection = perspective(0.52, 4.0 / 3, 0.1f, 100);
		glUniformMatrix4fv(views, 1, GL_TRUE, (GLfloat*)&view);
		glUniformMatrix4fv(projectins, 1, GL_TRUE, (GLfloat*)&projection);




		mesh.createCube(3, 3, 3);
		time += 0.02f;
		// do stuff
		mesh.setUpVertexAttributes();
		mesh.bindIBO();




		//mat4 mat = rotationz(time); //rotation matrix
		//mat4 mat = rotationaxis(vec3(1, 0, 1), time); //rotation matrix
		mat4 mat = rotationz(time) * rotationx(time);
		mat = mat * rotationy(time);
		//mat[3] += vec4(sinf(2 * time) / 2, cosf(2*time)/2, 0, 0); //adds rotation and movement in the x and y axis
		//mat[3] += vec4(sinf(0.01f * time) / 1, 0, 0, 0); //adds rotation and movement in the x and y axis
		glUniformMatrix4fv(rot, 1, GL_TRUE, (GLfloat*)&mat);//adds the rotation to the mesh
		glUniform1i(img, 0);
		glUniform1i(hasTexture, 1);
		text.bind(0);
		mesh.drawMesh(mesh.indexBO.size());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//unbinds the buffer
		grid.Draw((GLfloat*)&(projection * view));
		glBindBuffer(GL_ARRAY_BUFFER, 0);//unbinds the buffer
		
		// transfer new frame to window
		this->window->SwapBuffers();

#ifdef CI_TEST
		// if we're running CI, we want to return and exit the application after one frame
		// break the loop and hopefully exit gracefully
		break;
#endif
	}

}
void
ImGuiExampleApp::CompileShaders()
{
	// check if shader already exists
	if (this->program)
	{
		glDeleteProgram(this->program);
		this->program = 0;
	}
	if (this->vertexShader)
	{
		glDeleteShader(this->vertexShader);
		this->vertexShader = 0;
	}
	if (this->pixelShader)
	{
		glDeleteShader(this->pixelShader);
		this->pixelShader = 0;
	}

	this->compilerLog.clear();

	// setup vertex shader
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLint length = static_cast<GLint>(std::strlen(this->vsBuffer));
	glShaderSource(this->vertexShader, 1, &this->vsBuffer, &length);
	glCompileShader(this->vertexShader);

	// get error log
	GLint shaderLogSize;
	glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
		this->compilerLog.append(buf);
		printf("[VERTEX SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}

	// setup pixel shader
	this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	length = static_cast<GLint>(std::strlen(this->fsBuffer));
	glShaderSource(this->pixelShader, 1, &this->fsBuffer, &length);
	glCompileShader(this->pixelShader);

	// get error log
	shaderLogSize;
	glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
		this->compilerLog.append(buf);
		printf("[PIXEL SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}

	// create a program object
	this->program = glCreateProgram();
	glAttachShader(this->program, this->vertexShader);
	glAttachShader(this->program, this->pixelShader);
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

}


 // namespace Example