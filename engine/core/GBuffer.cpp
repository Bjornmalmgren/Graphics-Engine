#include "config.h"
#include "core/GBuffer.h"
GBuffer::GBuffer()
{
	
}

GBuffer::~GBuffer()
{
}

void GBuffer::MakeDirectionalLight(vec3 dir) {
	GLint isLight = lightingPass.UniformLocation("isDir");
	GLint dirLight = lightingPass.UniformLocation("lightDirection");
	glUniform1i(isLight, 1);
	glUniform3fv(dirLight, 1, (GLfloat*)&dir);
}

void GBuffer::LoadShaders() {
	lightingBox.SetUpShader("../../../engine/render/deferred_light_box.glvs", "../../../engine/render/deferred_light_box.glfs");
	geometryPass.SetUpShader("../../../engine/render/g_buffer.glvs", "../../../engine/render/g_buffer.glfs");
	lightingPass.SetUpShader("../../../engine/render/deferred_shading.glvs", "../../../engine/render/deferred_shading.glfs");
}

void GBuffer::SetTexture(int i) {
	switch (i)
	{
	case 0:
		glUniform1i(gbDiffuse, 0);
		break;
	case 1:
		glUniform1i(gbDiffuse, 2);
		break;
	case 2:
		glUniform1i(gbDiffuse, 4);
		break;
	case 3:
		glUniform1i(gbDiffuse, 5);
		break;
	default:
		break;
	}
}

void GBuffer::SetUpBuffers() {
	

	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

	glGenTextures(1, &gPosition);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

	glGenTextures(1, &gAlbedoSpec);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);

	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

	glGenRenderbuffers(1, &gDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, gDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, gDepth);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	srand(13);
	for (int i = 0; i < numberOfLights; i++)
	{
		lightTransforms.push_back(mat4());
		lightTransforms[i][0][0] *= 0.05;
		lightTransforms[i][1][1] *= 0.05;
		lightTransforms[i][2][2] *= 0.05;
		float xPos = static_cast<float>(((rand() % 100) / 100.0f) * 6.0f - 2.0f);
		float yPos = static_cast<float>(((rand() % 100) / 100.0f) * 6.0f - 4.0f);
		float zPos = static_cast<float>(((rand() % 100) / 100.0f) * 6.0f - 2.0f);
		lightPositions.push_back(vec3(xPos, yPos, zPos));
		lightTransforms[i][3] = vec4(xPos, yPos, zPos, 1);

		float rColor = static_cast<float>(((rand() % 100) / 100.0f));
		float gColor = static_cast<float>(((rand() % 100) / 100.0f) );
		float bColor = static_cast<float>(((rand() % 100) / 100.0f) );
		lightColors.push_back(vec3(rColor, gColor, bColor));
	}

	glUseProgram(0);
	lightingPass.UseProgram();

	glUniform1i(gbPosition, 0);
	glUniform1i(gbNormal, 1);
	glUniform1i(gbAlbedoSpec, 2);
	meshes[3].buildSphere();
}
void GBuffer::LoadModels() {
	for (int i = 0; i < 4; i++)
	{
		meshes.push_back(MeshResource());
		meshes[i].setUpBuffers();
	}
	//cube.setUpBuffers();

	std::string filePath1 = "../../../engine/core/GLTFmodel/Avocado/Avocado.gltf";
	std::string toFile1 = "../../../engine/core/GLTFmodel/Avocado/";
	std::string filePath2 = "../../../engine/core/GLTFmodel/DamagedHelmet/DamagedHelmet.gltf";
	std::string toFile2 = "../../../engine/core/GLTFmodel/DamagedHelmet/";
	std::string filePath3 = "../../../engine/core/GLTFmodel/Cube/Cube.gltf";
	std::string toFile3 = "../../../engine/core/GLTFmodel/Cube/";
	std::vector<std::string> toActivate; // not currently used
	std::vector<std::string> paths = gltfLoader.loadGLTF(toFile1, filePath1, meshes[0], toActivate);
	for (int i = 0; i < paths.size(); i++)
	{
		TextureResource t;
		gltfTextures.push_back(t);
	}
	for (int i = 0; i < paths.size(); i++)
	{
		gltfTextures[i].LoadFromFile(paths[i].c_str(), i);
	}
	std::vector<std::string> paths2 = gltfLoader.loadGLTF(toFile2, filePath2, meshes[1], toActivate);
	int a = gltfTextures.size();
	 for (int i = 0; i < paths2.size(); i++)
	 {
		 TextureResource t;
		 gltfTextures.push_back(t);
	 }
	 for (int i = 0; i < paths2.size(); i++)
	 {
		 gltfTextures[a+i].LoadFromFile(paths2[i].c_str(), a+i);
	 }

	 std::vector<std::string> paths3 = gltfLoader.loadGLTF(toFile3, filePath3, meshes[2], toActivate);
	 int s = gltfTextures.size();
	 for (int i = 0; i < paths3.size(); i++)
	 {
		 TextureResource t;
		 gltfTextures.push_back(t);
	 }
	 for (int i = 0; i < paths3.size(); i++)
	 {
		 gltfTextures[s+i].LoadFromFile(paths3[i].c_str(), s+i);
	 }

	//std::vector<std::string> paths3 = gltfLoader.loadGLTF(toFile3, filePath3, cube, toActivate);
	//int s = gltfTextures.size();
	//for (int i = 0; i < paths3.size(); i++)
	//{
	//	TextureResource t;
	//	gltfTextures.push_back(t);
	//}
	//for (int i = 0; i < paths3.size(); i++)
	//{
	//	gltfTextures[i].LoadFromFile(paths3[i].c_str(), i);
	//}
	
	/*TextureResource t;
	gltfTextures.push_back(t);
	gltfTextures[gltfTextures.size()-1].LoadFromFile("../projects/CameraAndTexture/Texture/2k_earth_daymap.jpg", gltfTextures.size()-1);*/
	sphere.setUpBuffers();
	sphere.sphereRadius = 1;
	sphere.stackCount = 18;
	sphere.sectorCount = 36;
	meshes[3].sphereRadius = 0.1f;
	meshes[3].stackCount = 18;
	meshes[3].sectorCount = 36;
	sphere.buildSphere();
	meshes[3].SetUpSphere();
	sphere.SetUpSphere();

	LightSphere.setUpBuffers();
	LightSphere.sphereRadius = 2;
	LightSphere.stackCount = 18;
	LightSphere.sectorCount = 36;
	LightSphere.buildSphere();
	LightSphere.SetUpSphere();
	/*for (int i = 0; i < amountOfItems/5; i++)
	{
		mat4 m1 = mat4(vec4(6, 0, 0, 0), vec4(0, 6, 0, 0), vec4(0, 0, 6, 0), vec4(0, 0, -(i / 2), 1));
		mat4 m2 = mat4(vec4(0.1, 0, 0, 0), vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(1, 0, -(i / 2), 1)); v
		mat4 m3 = mat4(vec4(0.1, 0, 0, 0), vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(0.5f, 0, -(i / 2), 1));
		mat4 m4 = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(-0.5, 0, -(i / 2), 1));
		mat4 m5 = mat4(vec4(6, 0, 0, 0), vec4(0, 6, 0, 0), vec4(0, 0, 6, 0), vec4(-1, 0, -(i/2), 1));

		objectTransforms.push_back(m1);
		objectTransforms.push_back(m2);
		objectTransforms.push_back(m3);
		objectTransforms.push_back(m4);
		objectTransforms.push_back(m5);
	}*/

	mat4 m1 = mat4(vec4(6, 0, 0, 0), vec4(0, 6, 0, 0), vec4(0, 0, 6, 0), vec4(0, 0, 1, 1));
	m1 = m1 * rotationy(3.14);
	mat4 m2 = mat4(vec4(0.1, 0, 0, 0),	vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(1, 0, 1, 1));
	mat4 m3 = mat4(vec4(2, 0, 0, 0),	vec4(0, 2, 0, 0), vec4(0, 0, 2, 0), vec4(0.5, 0, 4, 1));
	mat4 m4 = mat4(vec4(1, 0, 0, 0),	vec4(0, 1, 0, 0),	vec4(0, 0, 1, 0),	vec4(-0.5, 0, 1, 1));
	mat4 m5 = mat4(vec4(6, 0, 0, 0),	vec4(0, 6, 0, 0),	vec4(0, 0, 6, 0),	vec4(-1.4, 0, 1, 1));
	m5 = m5 * rotationy(3.14);
	mat4 m6 = mat4(vec4(0.1, 0, 0, 0),	vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(0, 0,0, 1));
	mat4 m7 = mat4(vec4(0.1, 0, 0, 0),	vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(1, 0, 0, 1));
	mat4 m8 = mat4(vec4(1, 0, 0, 0),	vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(0.5f, 0, 0, 1));
	mat4 m9 = mat4(vec4(6, 0, 0, 0),	vec4(0, 6, 0, 0),	vec4(0, 0, 6, 0),	vec4(-1, 0, 0, 1));
	mat4 m10 = mat4(vec4(0.1, 0, 0, 0), vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(-0.5, 0, 0, 1));
	m9 = m9 * rotationy(3.14);
	mat4 m11 = mat4(vec4(0.1, 0, 0, 0), vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(-0.5, 0, -1, 1));
	mat4 m12 = mat4(vec4(1, 0, 0, 0),	vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(0.5f, 0, -1, 1));
	mat4 m13 = mat4(vec4(6, 0, 0, 0),	vec4(0, 6, 0, 0),	vec4(0, 0, 6, 0),	vec4(-1, 0, -1, 1));
	mat4 m14 = mat4(vec4(0.1, 0, 0, 0), vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(0, 0, -1, 1));
	mat4 m15 = mat4(vec4(0.1, 0, 0, 0), vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(1, 0, -1, 1));
	m13 = m13 * rotationy(3.14);
	mat4 m16 = mat4(vec4(1, 0, 0, 0), vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(0.5f, 0, -2, 1));
	mat4 m17 = mat4(vec4(6, 0, 0, 0), vec4(0, 6, 0, 0), vec4(0, 0, 6, 0), vec4(-1, 0, -2, 1));
	mat4 m18 = mat4(vec4(0.1, 0, 0, 0), vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(1, 0, -2, 1));
	mat4 m19 = mat4(vec4(0.1, 0, 0, 0), vec4(0, 0.1, 0, 0), vec4(0, 0, 0.1, 0), vec4(0, 0, -2, 1));
	mat4 m20 = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(-0.5, 0, -2, 1));
	m17 = m17 * rotationy(3.14);
	objectTransforms.push_back(m1);
	objectTransforms.push_back(m2);
	objectTransforms.push_back(m3);
	objectTransforms.push_back(m4);
	objectTransforms.push_back(m5);

	objectTransforms.push_back(m6);
	objectTransforms.push_back(m7);
	objectTransforms.push_back(m8);
	objectTransforms.push_back(m9);
	objectTransforms.push_back(m10);

	objectTransforms.push_back(m11);
	objectTransforms.push_back(m12);
	objectTransforms.push_back(m13);
	objectTransforms.push_back(m14);
	objectTransforms.push_back(m15);

	objectTransforms.push_back(m16);
	objectTransforms.push_back(m17);
	objectTransforms.push_back(m18);
	objectTransforms.push_back(m19);
	objectTransforms.push_back(m20);

}
void GBuffer::Setuniforms() {
	
	gbPosition = lightingPass.UniformLocation("gPosition");
	gbNormal = lightingPass.UniformLocation("gNormal");
	gbAlbedoSpec = lightingPass.UniformLocation("gAlbedoSpec");
	gbDiffuse = geometryPass.UniformLocation("texture_diffuse1");
	gbSpecular = geometryPass.UniformLocation("texture_specular1");
	gbProjection = geometryPass.UniformLocation("projection");
	gbView = geometryPass.UniformLocation("view");
	gbModel = geometryPass.UniformLocation("model");
	lpViewPos = lightingPass.UniformLocation("viewPos");
	lbProjection = lightingBox.UniformLocation("projection");
	lbView = lightingBox.UniformLocation("view");
	lbModel = lightingBox.UniformLocation("model");
	lbLightColor = lightingBox.UniformLocation("lightColor");
}

void GBuffer::GeometryPass() {
	for (int i = 0; i < meshes.size()-1; i++)
	{
		meshes[i].bindIBO();
		meshes[i].bindVBO();
		meshes[i].type = GL_UNSIGNED_SHORT;
	}
	//cube.bindIBO();
	//cube.bindVBO();
	//cube.type = GL_UNSIGNED_SHORT;
	
	for (int i = 0; i < gltfTextures.size(); i++)
	{
		gltfTextures[i].bind(i);
	}
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_DEPTH_TEST);
	double pi = 3.14159265359;
	projection = perspective(0.52, 4.0 / 3, 0.1f, 100);
	
	mat4 viewede = lookat(camera.position, camera.position + camera.cameraFront, vec3(0, 1, 0));
	this->view = viewede;
	model = mat4();

	geometryPass.UseProgram();
	
	
	glUniform1i(gbSpecular, shiny);
	int j = 0;
	glUniformMatrix4fv(gbProjection, 1, GL_TRUE, (GLfloat*)&projection);
	glUniformMatrix4fv(gbView, 1, GL_TRUE, (GLfloat*)&view);
	for (unsigned int i = 0; i < objectTransforms.size(); i++)
	{
		
		if (j >= meshes.size()) {
			j = 0;
		}
		
		model = objectTransforms[i];
		glUniformMatrix4fv(gbModel, 1, GL_TRUE, (GLfloat*)&model);
		
		SetTexture(j);
	
		meshes[j].DrawWithShader(geometryPass);
		//cube.DrawWithShader(geometryPass);
		j++;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GBuffer::LightPass(float dt) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	lightingPass.UseProgram();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	
	glEnable(GL_CULL_FACE);
	for (unsigned int i = 0; i < lightPositions.size(); i++)
	{
		int radius = LightSphere.sphereRadius;
		
		if (length(lightPositions[i]- camera.position) < radius) {
			glCullFace(GL_BACK);
		}
		else
		{
			glCullFace(GL_FRONT);
		}
		LightSphere.bindIBO();
		LightSphere.bindVBO();
		LightSphere.type = GL_UNSIGNED_SHORT;
		
		LightSphere.drawSphere();
		lpLightPositions = lightingPass.UniformLocation("Position");
		lpLightColors = lightingPass.UniformLocation("Color");
		vec3 light = lightPositions[i];
		vec3 lightColor = lightColors[i];
		glUniform3fv(lpLightPositions, 1, (GLfloat*)&light);
		glUniform3fv(lpLightColors, 1, (GLfloat*)&lightColor);


		// update attenuation parameters and calculate radius
		const float linear = 130;
		const float quadratic =90;
		lpLightLinears = lightingPass.UniformLocation("Linear");
		lpLightQuadratics = lightingPass.UniformLocation("Quadratic");
		GLint rad = lightingPass.UniformLocation("radius");
		GLint modes = lightingPass.UniformLocation("model");
		GLint viewed = lightingPass.UniformLocation("view");
		GLint proj = lightingPass.UniformLocation("projection");
		
		mat4 m = mat4(vec4(radius,0,0,0), vec4(0, radius,0,0), vec4(0,0, radius,0), vec4(lightPositions[i].x, lightPositions[i].y, lightPositions[i].z, 1));
		model = m;
		glUniformMatrix4fv(modes, 1, GL_TRUE, (GLfloat*)&model);
		glUniformMatrix4fv(viewed, 1, GL_TRUE, (GLfloat*)&view);
		glUniformMatrix4fv(proj, 1, GL_TRUE, (GLfloat*)&projection);
		glUniform1f(rad, radius);
		glUniform1f(lpLightLinears, linear);
		glUniform1f(lpLightQuadratics, quadratic);
		
		float rotationSpeed = 0.1;
		angle += rotationSpeed * dt;
		double sinus = sin(angle) * radius * 0.01;
		double cosinus = cos(angle) * radius * 0.01;
		lightPositions[i].x = lightPositions[i].x + cosinus;
		lightPositions[i].z = lightPositions[i].z + sinus;
		lightTransforms[i][3].x += cosinus;
		lightTransforms[i][3].z += sinus;
	}
	
	glUniform3fv(lpViewPos, 1, (GLfloat*)&camera.position);
	//RenderQuad();
	
	glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::LightBoxPass() {
	lightingBox.UseProgram();
	
	glUniformMatrix4fv(lbProjection, 1, GL_TRUE, (GLfloat*)&projection);
	glUniformMatrix4fv(lbView, 1, GL_TRUE, (GLfloat*)&view);
	for (unsigned int i = 0; i < lightPositions.size(); i++)
	{
		mat4 temp = lightTransforms[i];
		
		model = temp;
		glUniformMatrix4fv(lbModel, 1, GL_TRUE, (GLfloat*)&model);
		glUniform3fv(lbLightColor, 1, &lightColors[i][0]);
		//RenderCube();
		sphere.bindIBO();
		sphere.bindVBO();
		sphere.type = GL_UNSIGNED_SHORT;
		
		sphere.DrawWithShader(geometryPass);
	}
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void GBuffer::RenderQuad() {
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
/*void GBuffer::RenderCube() {
	// initialize (if necessary)
	if (cubeVAO == 0)
	{
		float vertices[] = {
			// back face
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
			// front face
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			// left face
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			// right face
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
			 // bottom face
			 -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			  1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
			  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			 -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			 -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			 // top face
			 -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			  1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			  1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
			  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			 -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			 -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
		};
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);
		// fill buffer
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// link vertex attributes
		glBindVertexArray(cubeVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	// render Cube
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}*/