#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2022 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
#include "render/grid.h"
#include "render/Camera.h"
#include <string>
#include "render/textureResource.h"
#include "render/Meshresource.h"
namespace Example
{
class ImGuiExampleApp : public Core::App
{
public:
	/// constructor
	ImGuiExampleApp();
	/// destructor
	~ImGuiExampleApp();
	void CompileShaders();
	/// open app
	bool Open();
	/// clone app
	void Close();
	/// run app
	void Run();
private:



	GLuint program;
	GLuint vertexShader;
	GLuint pixelShader;
	GLuint triangle;
	GLuint test;
	GLuint color;
	Display::Window* window;
	GLchar *vsBuffer;
	GLchar *fsBuffer;
	std::string compilerLog;
	MeshResource mesh;
	mat4 transform = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0.5f, 0, 1));
	mat4 transform2;
	mat4 mat = mat4();
	TextureResource text;
};
} // namespace Example