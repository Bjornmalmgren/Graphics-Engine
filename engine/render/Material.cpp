#include "config.h"
#include "Material.h"
#include <iostream>
#include <filesystem>
BlinnPhongMaterial::BlinnPhongMaterial()
{
}

BlinnPhongMaterial::~BlinnPhongMaterial()
{
}


void BlinnPhongMaterial::Apply() {
	if (shader.get()->vertexBuffer == 0) {
	

		shader.get()->SetUpShader("../../../engine/render/vertexShaderOld.glvs", "../../../engine/render/fragmentShaderOld.glfs");
	}
	std::vector<GLint> imgs;
	GLint img;
	//binds to the rotation variable
	GLint views = shader.get()->UniformLocation("view");
	GLint rots = shader.get()->UniformLocation("rotation");
	GLint projectins = shader.get()->UniformLocation("projection");
	if (toActivate.size() != 0) {
		imgs = shader.get()->EnableTextures(toActivate);
	}
	else
	{
		img = shader.get()->UniformLocation("Texture");
	}
	
	GLint transfor = shader.get()->UniformLocation("transform");
	GLint lights = shader.get()->UniformLocation("lightPos");
	GLint cameraPos = shader.get()->UniformLocation("cameraPos");
	GLint lightDir = shader.get()->UniformLocation("lightDirection");
	GLint lightCol = shader.get()->UniformLocation("lightColor");
	GLint lightIntesity = shader.get()->UniformLocation("specularStrength");
	GLint hastexture = shader.get()->UniformLocation("hasTexture");
	GLint shiny = shader.get()->UniformLocation("shiny");
	GLint hasNormalmap = shader.get()->UniformLocation("hasNormalMap");
	if (toActivate.size() != 0) {
		for (int i = 0; i < imgs.size(); i++)
		{
			glUniform1i(imgs[i], i);
		}
	}
	else
	{
		glUniform1i(img, 1);
	}
	

	glUniformMatrix4fv(transfor, 1, GL_FALSE, (GLfloat*)&transform);
	glUniformMatrix4fv(views, 1, GL_TRUE, (GLfloat*)&view);
	glUniformMatrix4fv(projectins, 1, GL_TRUE, (GLfloat*)&projection);
	glUniformMatrix4fv(rots, 1, GL_TRUE, (GLfloat*)&rot);
	light.draw(cameraPos, camera.position);
	light.draw(lightCol, light.color);
	glUniform1f(lightIntesity, light.intesity);
	glUniform1i(hastexture, hasTexture);
	light.draw(lights, light.position);
	glUniform1f(shiny, shinyness);
	glUniform1i(hasNormalmap, hasNormalMap);
	//makes the light directional more like the sun
	//light.draw(lightDir, vec3(0,-1, 0));
}
void BlinnPhongMaterial::SetHasTexture(int texture) {
	hasTexture = texture;
}

void BlinnPhongMaterial::SetSiny(float shiny) {
	 shinyness = shiny;
}

void BlinnPhongMaterial::SetLight(PointLight lights) {
	light.position = lights.position;
	light.color = lights.color;
	light.intesity = lights.intesity;
}
void BlinnPhongMaterial::SetRotation(mat4 rotations) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			rot[i][j] = rotations[i][j];
		}
	}
}
void BlinnPhongMaterial::SetView(mat4 views) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			view[i][j] = views[i][j];
		}
	}
}
void BlinnPhongMaterial::SetTransform(mat4 transforms) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			transform[i][j] = transforms[i][j];
		}
	}
}
void BlinnPhongMaterial::SetProjection(mat4 projections) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			projection[i][j] = projections[i][j];
		}
	}
}
void BlinnPhongMaterial::SetCamer(Camera cameras) {
	camera.position = cameras.position;
	
}