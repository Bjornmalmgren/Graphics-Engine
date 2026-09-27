//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "defShading.h"
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
	window->SetSize(SCR_WIDTH, SCR_HEIGHT);
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
		case GLFW_MOUSE_BUTTON_2:
			rightMouseButton = (bool)action;
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
		glDisable(GL_BLEND);
		
		gbuffer.LoadModels();

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
	
	
	glClearColor(0, 0, 0, 1.0f);
	const float radius = 10.0f;
	camera.createCamera(vec3(0, 3, radius), vec3(0, 0, -1), vec3(0, 1, 0));
	double dt = 0.01667f;
	gbuffer.LoadShaders();
	gbuffer.Setuniforms();
	gbuffer.SetUpBuffers();
	//makes the light directional
	//vec3 ds = vec3(-0.2, -1, -0.3);
	//gbuffer.MakeDirectionalLight(ds);
	
	float time = 0; //time variable for rotation
	Render::Grid grid;
	while (this->window->IsOpen())
	{
		auto timeStart = std::chrono::steady_clock::now();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->window->Update();
		//shaderPtr.get()->UseProgram();
		double MAX_DT = 1.0f / 60.0f;  // Max 60 FPS equivalent
		dt = min(dt, MAX_DT);


		/*float camX = sinf(time) * radius;
		float camZ = cosf(time) * radius;*/

		if (rightMouseButton) {
			mat = mat * rotationy(0.03f);
			
		}
		mat4 view = lookat(camera.position, camera.position + vec3(0, 0, -1), vec3(0, 1, 0));
		
		gbuffer.camera.position = camera.position;
		gbuffer.camera.cameraFront = camera.cameraFront;
		gbuffer.camera.cameraPitch = camera.cameraPitch;
		gbuffer.camera.cameraRight = camera.cameraRight;
		gbuffer.camera.cameraUp = camera.cameraUp;
		gbuffer.camera.cameraYaw = camera.cameraYaw;
		gbuffer.camera.Zoom = camera.Zoom;

		gbuffer.shiny = shiny;
		
		double pi = 3.14159265359;
		mat4 projection = perspective(gbuffer.camera.Zoom * (pi/180), 4.0 / 3, 0.1f, 100);






		time += 0.02f;
		// do stuff










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
			//pointLight.moveLightInCircle(time);
		}



		//transform2[3] = vec4(pointLight.position.x, pointLight.position.y, pointLight.position.z, 1);

		//graphicsNode.draw(transform,view,projection, mat);
		//




		//graphicsNode2.draw(transform2, view, projection, mat);

		//cube.BPM.SetHasTexture(1);
		//cube.BPM.SetCamer(camera);
		//cube.BPM.SetLight(pointLight);
		//cube.BPM.SetProjection(projection);
		//cube.BPM.SetRotation(mat);
		//cube.BPM.SetTransform(transform);
		//cube.BPM.SetView(view);
		//cube.BPM.SetSiny(16);
		//cube.SetUpSphere();
		//cube2.bindIBO();
		//cube2.bindVBO();
		//cube2.type = GL_UNSIGNED_SHORT;
		//for (int i = 0; i < gltfTextures.size(); i++)
		//{
		//	gltfTextures[i].bind(i);
		//}
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//mat4 project = perspective(0.52, SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
		//mat4 viewd = lookat(camera.position, camera.cameraTarget + vec3(0,0,-1), vec3(0, 1, 0));
		//mat4 model = mat4();

		////geometrypass	
		//
		//geometryPass.UseProgram();
		//int shiny = 16;


		//GLint diff = geometryPass.UniformLocation("texture_diffuse1");
		//GLint spec = geometryPass.UniformLocation("texture_specular1");
		//glUniform1i(diff, 0);
		//glUniform1i(spec, shiny);
		//GLint prj = geometryPass.UniformLocation("projection");
		//GLint vi = geometryPass.UniformLocation("view");
		//glUniformMatrix4fv(prj, 1, GL_TRUE, (GLfloat*)&project);
		//glUniformMatrix4fv(vi, 1, GL_TRUE, (GLfloat*)&viewd); 
		//for (unsigned int i = 0; i < objectPositions.size(); i++)
		//{

		//	model = transform * mat;
		//	GLint modl = geometryPass.UniformLocation("model");
		//	glUniformMatrix4fv(modl, 1, GL_TRUE, (GLfloat*)&model);
		//	cube2.DrawWithShader(geometryPass);
		//	//cube.DrawWithShader(geometryPass);
		//}
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gbuffer.GeometryPass();

		//lightingPass.UseProgram();
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, gPosition);
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, gNormal);
		//glActiveTexture(GL_TEXTURE2);
		//glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
		//for (unsigned int i = 0; i < lightPositions.size(); i++)
		//{
		//	std::string s = std::to_string(i);
		//	std::string test = "lights[" + s + "].Position ";
		//	GLint posse = lightingPass.UniformLocation(test);
		//	GLint coloroe = lightingPass.UniformLocation("lights[" + s + "].Color");
		//	vec3 light = lightPositions[i];
		//	vec3 lightColor = lightColors[i];
		//	glUniform3fv(posse, 1, (GLfloat*)&light);
		//	glUniform3fv(coloroe,1, (GLfloat*)&lightColor);
		//	
		//	
		//	// update attenuation parameters and calculate radius
		//	const float linear = 0.7f;
		//	const float quadratic = 1.8f;
		//	GLint lin = lightingPass.UniformLocation("lights[" + s + "].Linear");
		//	GLint qua = lightingPass.UniformLocation("lights[" + s + "].Quadratic");
		//	glUniform1f(lin, linear);
		//	glUniform1f(qua, quadratic);

		//	
		//}
		//GLint colors = lightingPass.UniformLocation("viewPos");
		//glUniform3fv(colors, 1, (GLfloat*)&camera.position);
		//RenderQuad();
		//
		//glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
		//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); 
		//glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		gbuffer.LightPass(dt);


		/*lightingBox.UseProgram();
		GLint prjn = lightingBox.UniformLocation("projection");
		GLint vin = lightingBox.UniformLocation("view");
		glUniformMatrix4fv(prjn, 1, GL_TRUE, (GLfloat*)&project);
		glUniformMatrix4fv(vin, 1, GL_TRUE, (GLfloat*)&viewd);
		for (unsigned int i = 0; i < lightPositions.size(); i++)
		{

			model = lightTransforms[i];

			GLint modls = lightingBox.UniformLocation("model");
			glUniformMatrix4fv(modls, 1, GL_TRUE, (GLfloat*)&model);
			GLint color = lightingBox.UniformLocation("lightColor");
			glUniform3fv(color, 1, &lightColors[i][0]);
			renderCube();
		}*/
		gbuffer.LightBoxPass();
		//grid.Draw((GLfloat*)&(project * viewd));
		// transfer new frame to window
		this->window->SwapBuffers();
		auto timeEnd = std::chrono::steady_clock::now();
		dt = min(0.04,
			std::chrono::duration<double>(timeEnd - timeStart).count());

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