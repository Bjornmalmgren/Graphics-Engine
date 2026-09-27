//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "matAndGLTF.h"
#include <cstring>
#include "imgui.h"
#include <windows.h>
#define STRING_BUFFER_SIZE 8192


using namespace Display;

namespace Example
{
	MeshResource mesh;
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
	for (int i = 0; i < 4; i++)
	{
		WASD[i] = false;
	}
	window->SetSize(2160, 1440);
	window->SetKeyPressFunction([this](int32 key, int32 , int32 action, int32)
		{
			switch (key)
			{
			case GLFW_KEY_W:
				WASD[0] = (bool)action;
				break;
			case GLFW_KEY_S:
				WASD[1] = (bool)action;
				break;
			case GLFW_KEY_A:
				WASD[2] = (bool)action;
				break;
			case GLFW_KEY_D:
				WASD[3] = (bool)action;
				break;
			case GLFW_KEY_SPACE:
				if (action == GLFW_PRESS) {
					moveLight = !moveLight;
				}
				
				break;
			default:
				break;
			}

		});
	window->SetMousePressFunction([this](int32 key, int32 action, int32) {
		switch (key)
		{case GLFW_MOUSE_BUTTON_1:
			leftMouseButton = (bool)action;
		default:
			break;
		}
		});
	window->SetMouseMoveFunction([this](float64 mouseX, float64 mouseY) {
		mouse_callback(mouseX, mouseY);
		});
	if (leftMouseButton) {

		window->SetMouseScrollFunction([this](float64 x, float64 y) {
			scroll_callback(x, y);
			});
	}
	
	
	

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		cube.setUpBuffers();
		//Avocado model loading path
		
		//auto filePath =	"../../../bin/GLTFmodel/Avocado/Avocado.gltf";
		//std::string toFile = "../../../bin/GLTFmodel/Avocado/";
		//transform[0][0] *= 10;
		//transform[1][1] *= 10;
		//transform[2][2] *= 10;
		

		//Damaged helmet model loading path
		auto filePath =	"../../../engine/core/GLTFmodel/DamagedHelmet/DamagedHelmet.gltf";
		std::string toFile = "../../../engine/core/GLTFmodel/DamagedHelmet/";
		

		//FlightHelmet model loading path
		//std::string filePath = "../../../engine/core/GLTFmodel/FlightHelmet/FlightHelmet.gltf";
		//std::string toFile = "../../../engine/core/GLTFmodel/FlightHelmet/";

		//Cube model loading path
		/*std::string filePath = "../../../engine/core/GLTFmodel/Cube/Cube.gltf";
		std::string toFile = "../../../engine/core/GLTFmodel/Cube/";*/

		//to load the normalmap test
		/*std::string filePath = "../../../engine/core/GLTFmodel/Mirror/NormalTangentMirrorTest.gltf";
		std::string toFile = "../../../engine/core/GLTFmodel/Mirror/";*/

		//std::string filePath = "../../../engine/core/cube.obj";
		//objloader.LoadOBJ(filePath, cube);

	
		std::vector<std::string> toActivate;
		std::vector<std::string> paths = gltfLoader.loadGLTF(toFile,filePath, cube,toActivate);
		cube.BPM.toActivate = toActivate;
	
		for (int i = 0; i < paths.size(); i++)
		{
			TextureResource t;
			gltfTextures.push_back(t);
		}
	
		for (int i = 0; i < paths.size(); i++)
		{
			gltfTextures[i].LoadFromFile(paths[i].c_str(),i);
		}
		pointLight.intesity = 0.5;

		shaderPtr.get()->SetUpShader();
		
		//texturePtr.get()->LoadFromFile("../projects/CameraAndTexture/Texture/1384063.png");
		//text.LoadFromFile("../projects/CameraAndTexture/Texture/1384063.png");
		graphicsNode.shader = shaderPtr;
		graphicsNode.texture = texturePtr;
		//graphicsNode2.shader = shaderPtr;
		//graphicsNode2.texture = texturePtr;
		cube.BPM.shader = shaderPtr;
		

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
	float time = 0; //time variable for rotation
	Render::Grid grid;
	const float radius = 10.0f;
	
	camera.createCamera(vec3(0, 1, radius), vec3(0, 0, -1), vec3(0, 1, 0));

	//meshPtr.get()->createCube(3, 3, 3);
	while (this->window->IsOpen())
	{
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->window->Update();
		cube.BPM.shader.get()->UseProgram();
		
		/*glUseProgram(this->program);*/
	
		
		/*float camX = sinf(time) * radius;
		float camZ = cosf(time) * radius;*/
		
		mat4 view = lookat(camera.position, camera.position + camera.cameraFront, vec3(0, 1, 0));

		double pi = 3.14159265359;
		mat4 projection = perspective(camera.Zoom * (pi / 180), 4.0 / 3, 0.1f, 100);
		
		
		
		
		
		
		time += 0.02f;
		// do stuff
		

		
		
		//meshPtr.get()->createCube(3, 3, 3);
		graphicsNode.mesh = meshPtr;
		//graphicsNode2.mesh = meshPtr;
		
		
		
		
		
		/*mat = mat * rotationz(time) * rotationx(time);*/
		//mat[3] += vec4(sinf(2 * time) / 2, cosf(2*time)/2, 0, 0); //adds rotation and movement in the x and y axis
		//mat[3] += vec4(sinf(0.01f * time) / 1, 0, 0, 0); //adds rotation and movement in the x and y axis
		//adds the rotation to the mesh
	
		
	

		/*text.bind();
		mesh.drawMesh();*/
		

		if (leftMouseButton) {
			float cameraSpeed = 0.05;
			if (WASD[0]) {
				camera.position += camera.cameraFront * cameraSpeed;
			}
			if (WASD[1]) {
				camera.position -= camera.cameraFront * cameraSpeed;
			}
			if (WASD[2]) {
				camera.position -= normalize(cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;
			}
			if (WASD[3]) {
				camera.position += normalize(cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;
			}
		}

		if (moveLight) {
			pointLight.moveLightInCircle(time);
		}
		
		
		
		transform2[3] = vec4(pointLight.position.x, pointLight.position.y, pointLight.position.z, 1);
		
		//graphicsNode.draw(transform,view,projection, mat);
		//
		
		//graphicsNode2.draw(transform2, view, projection, mat);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		cube.BPM.SetHasTexture(1);
		cube.BPM.SetCamer(camera);
		cube.BPM.SetLight(pointLight);
		cube.BPM.SetProjection(projection);
		cube.BPM.SetRotation(mat);
		cube.BPM.SetTransform(transform);
		cube.BPM.SetView(view);
		cube.BPM.SetSiny(16);
		
	
		cube.bindVBO();
		cube.bindIBO();
		//cube.setUpVertexAttributesNT();
		
		//text.bind();
		
		cube.BPM.Apply();
		cube.type = GL_UNSIGNED_SHORT;
		for (int i = 0; i < gltfTextures.size(); i++)
		{
			gltfTextures[i].bind(i);
		}
		
		cube.drawOBJ(cube.indexBO.size());
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
void ImGuiExampleApp::mouse_callback(float xposIn, float yposIn)
{
	//std::cout << xposIn << " " << yposIn << std::endl;
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
	if (leftMouseButton) {
		camera.ProcessMouseMovement(xoffset, yoffset);
	}

}
void ImGuiExampleApp::scroll_callback(float xoffset, float yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


} // namespace Example