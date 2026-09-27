//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "ShaderAndNode.h"
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
	window->SetSize(1080, 720);
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
	
	
	

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		shaderPtr.get()->SetUpShader("../engine/render/vertexShader.glvs", "../engine/render/fragmentShader.glfs");
		texturePtr.get()->LoadFromFile("../projects/CameraAndTexture/Texture/1384063.png",0);

		graphicsNode.shader = shaderPtr;
		graphicsNode.texture = texturePtr;
		graphicsNode2.shader = shaderPtr;
		graphicsNode2.texture = texturePtr;
		
		

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
	//GLint rot  = graphicsNode.shader.get()->EnableRotation();//binds to the rotation variable
	//GLint views = graphicsNode.shader.get()->EnableView();
	//GLint projectins = graphicsNode.shader.get()->EnableProjection();
	GLint img = graphicsNode.shader.get()->UniformLocation("Texture");
	float time = 0; //time variable for rotation
	Render::Grid grid;
	while (this->window->IsOpen())
	{
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->window->Update();
		graphicsNode.shader.get()->UseProgram();
		/*glUseProgram(this->program);*/
		Camera camera;
		const float radius = 5.0f;
		/*float camX = sinf(time) * radius;
		float camZ = cosf(time) * radius;*/
		camera.createCamera(vec3(0, 3, 0), vec3(0, 0, -1), vec3(0, 1, 0));
		mat4 view = camera.getViewMatrix();


		mat4 projection = perspective(0.52, 4.0 / 3, 0.1f, 100);






		time += 0.02f;
		// do stuff
		/*mesh.setUpVertexAttributes();
		mesh.bindIBO();*/
		meshPtr.get()->createCube(3, 3, 3);
		graphicsNode.mesh = meshPtr;
		graphicsNode2.mesh = meshPtr;

		//mat4 mat = rotationz(time); //rotation matrix
		//mat4 mat = rotationaxis(vec3(1, 0, 1), time); //rotation matrix

		//if()



		/*mat = mat * rotationz(time) * rotationx(time);*/
		//mat[3] += vec4(sinf(2 * time) / 2, cosf(2*time)/2, 0, 0); //adds rotation and movement in the x and y axis
		//mat[3] += vec4(sinf(0.01f * time) / 1, 0, 0, 0); //adds rotation and movement in the x and y axis
		//adds the rotation to the mesh


		//glUniformMatrix4fv(rot, 1, GL_TRUE, (GLfloat*)&mat);
		glUniform1i(img, 0);

		/*text.bind();
		mesh.drawMesh();*/


		if (leftMouseButton) {
			mat = mat * rotationy(0.03f);
			mat = mat * rotationx(0.03f) * rotationz(0.03f);
			if (WASD[0]) {
				transform[3][2] -= 0.1f;
				transform2[3][2] -= 0.1f;
			}
			if (WASD[1]) {
				transform[3][2] += 0.1f;
				transform2[3][2] += 0.1f;
			}
			if (WASD[2]) {
				transform[3][0] -= 0.1f;
				transform2[3][0] -= 0.1f;
			}
			if (WASD[3]) {
				transform[3][0] += 0.1f;
				transform2[3][0] += 0.1f;
			}
		}

		graphicsNode.draw(transform, view, projection, mat);
		

		graphicsNode2.draw(transform2, view, projection, mat);
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



} // namespace Example