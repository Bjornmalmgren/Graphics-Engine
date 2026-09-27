//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "objAndLightning.h"
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
	
	
	

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	
		 std::string filePath = "../engine/core/cube.obj";
		//std::string filePath = "../engine/core/bunny.obj";
		objloader.LoadOBJ(filePath, cube);
		
		cube.setUpOBJVBO();
		cube.setUpOBJIBO();
		pointLight.intesity = 0.3;
		
		
		shaderPtr.get()->SetUpShader("../engine/render/vertexShader.glvs", "../engine/render/fragmentShader.glfs");
		//texturePtr.get()->LoadFromFile("../projects/CameraAndTexture/Texture/1384063.png");
		//text.LoadFromFile("../projects/CameraAndTexture/Texture/1384063.png");
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
	GLint rot = graphicsNode.shader.get()->UniformLocation("rotation");//binds to the rotation variable
	GLint views = graphicsNode.shader.get()->UniformLocation("view");
	GLint projectins = graphicsNode.shader.get()->UniformLocation("projection");
	//GLint img = graphicsNode.shader.get()->EnableTexture();
	GLint transfor = graphicsNode.shader.get()->UniformLocation("transform");
	GLint lights = graphicsNode.shader.get()->UniformLocation("lightPos");
	GLint cameraPos = graphicsNode.shader.get()->UniformLocation("cameraPos");
	GLint lightDir = graphicsNode.shader.get()->UniformLocation("lightDirection");
	GLint lightCol = graphicsNode.shader.get()->UniformLocation("lightColor");
	GLint lightIntesity = graphicsNode.shader.get()->UniformLocation("specularStrength");
	GLint hasTexture = graphicsNode.shader.get()->UniformLocation("hasTexture");
	glEnable(GL_DEPTH_TEST);
	float time = 0; //time variable for rotation
	Render::Grid grid;
	while (this->window->IsOpen())
	{
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->window->Update();
		graphicsNode.shader.get()->UseProgram();
		
		/*glUseProgram(this->program);*/
		Camera camera;
		const float radius = 10.0f;
		/*float camX = sinf(time) * radius;
		float camZ = cosf(time) * radius;*/
		camera.createCamera(vec3(0, 3, 0), vec3(0, 0, -1), vec3(0, 1, 0));
		mat4 view = camera.getViewMatrix();


		mat4 projection = perspective(0.52, 4.0 / 3, 0.1f, 100);
		
		
		
		
		
		
		time += 0.02f;
		// do stuff
		

		
		
		meshPtr.get()->createCube(3, 3, 3);
		graphicsNode.mesh = meshPtr;
		graphicsNode2.mesh = meshPtr;
		
		
		
		
		
		/*mat = mat * rotationz(time) * rotationx(time);*/
		//mat[3] += vec4(sinf(2 * time) / 2, cosf(2*time)/2, 0, 0); //adds rotation and movement in the x and y axis
		//mat[3] += vec4(sinf(0.01f * time) / 1, 0, 0, 0); //adds rotation and movement in the x and y axis
		//adds the rotation to the mesh
	
		
	

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

		if (moveLight) {
			pointLight.moveLightInCircle(time);
		}
		
		
		
		transform2[3] = vec4(pointLight.position.x, pointLight.position.y, pointLight.position.z, 1);
		
		//graphicsNode.draw(transform,view,projection, mat);
		//
		graphicsNode2.draw(transform2, view, projection, mat);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		pointLight.draw(lights, pointLight.position);
		//glUniform1i(img, 0);
		glUniformMatrix4fv(transfor, 1, GL_FALSE, (GLfloat*)&transform);
		glUniformMatrix4fv(views, 1, GL_TRUE, (GLfloat*)&view);
		glUniformMatrix4fv(projectins, 1, GL_TRUE, (GLfloat*)&projection);
		glUniformMatrix4fv(rot, 1, GL_TRUE, (GLfloat*)&mat);
		pointLight.draw(cameraPos, camera.position);
		pointLight.draw(lightCol, vec3(1, 1, 1));
		glUniform1f(lightIntesity, pointLight.intesity);
		glUniform1i(hasTexture, 0);
		
	
		cube.bindVBO();
		cube.bindIBO();
	    cube.setUpVertexAttributesNT();
		
		//text.bind();
		//cube.BPM.Apply();
		cube.drawMesh(cube.indexBO.size());
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