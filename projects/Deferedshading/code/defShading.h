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

#include "core/LoadOBJFile.h"
#include "render/Material.h"
#include "core/LoadGLTF.h"
#include "core/GBuffer.h"
#include "render/textureResource.h"
#include "core/ShaderResource.h"
#include "core/GraphicsNode.h"
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
	void RenderQuad();
	void renderCube();
private:


	GBuffer gbuffer;
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
	GLTFLoader gltfLoader;
	MeshResource cube;
	MeshResource cube2;
	PointLight pointLight;
	std::shared_ptr<MeshResource> meshPtr = std::make_shared<MeshResource>();
	std::shared_ptr<ShaderResource> shaderPtr = std::make_shared<ShaderResource>();
	std::shared_ptr<TextureResource> texturePtr = std::make_shared<TextureResource>();
	bool WASD[4];
	bool leftMouseButton = false;
	bool rightMouseButton = false;
	bool moveLight = false;
	mat4 transform = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
	mat4 transform2;
	mat4 mat = mat4();
	std::vector<TextureResource> gltfTextures;
	OBJLoader objloader;
	TextureResource text;
	int shiny = 16;
	Camera camera;
	GLuint gBuffer;
	GLuint gNormal;
	GLuint gAlbedoSpec;
	GLuint gPosition;
	GLuint gDepth;
	const int numberOfLights = 1;

	std::vector<mat4> lightTransforms;
	ShaderResource lightingPass;
	ShaderResource geometryPass;
	ShaderResource lightingBox;

	int SCR_WIDTH = 2560;
	int SCR_HEIGHT = 1440;
	bool firstMouse = true;
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	void mouse_callback(float xposIn, float yposIn);
	void scroll_callback(float xoffset, float yoffset);
};
} // namespace Example