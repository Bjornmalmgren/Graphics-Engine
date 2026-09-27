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
#include "core/ShaderResource.h"
#include "core/GraphicsNode.h"
#include "core/LoadOBJFile.h"
#include "render/PointLight.h"
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
	GraphicsNode graphicsNode;
	GraphicsNode graphicsNode2;
	MeshResource cube;
	PointLight pointLight;
	std::shared_ptr<MeshResource> meshPtr = std::make_shared<MeshResource>();
	std::shared_ptr<ShaderResource> shaderPtr = std::make_shared<ShaderResource>();
	std::shared_ptr<TextureResource> texturePtr = std::make_shared<TextureResource>();
	bool WASD[4];
	bool leftMouseButton = false;
	bool moveLight = false;
	mat4 transform = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0.5f, 0, 1));
	mat4 transform2;
	mat4 mat = mat4();
	OBJLoader objloader;
	TextureResource text;
};
} // namespace Example