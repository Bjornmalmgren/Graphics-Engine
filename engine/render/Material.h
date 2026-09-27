#pragma once
#include "core/ShaderResource.h"
#include "PointLight.h"
#include "core/mat4.h"
#include "render/Camera.h"
#include <vector>
class Material
{
public:
	virtual void Apply() = 0;

private:

};
class BlinnPhongMaterial : public Material
{
public:
	BlinnPhongMaterial();
	~BlinnPhongMaterial();
	void Apply() override;
	void SetLight(PointLight);
	void SetRotation(mat4);
	void SetView(mat4);
	void SetTransform(mat4);
	void SetProjection(mat4);
	void SetCamer(Camera);
	void SetHasTexture(int);
	void SetSiny(float shiny);
	std::shared_ptr<ShaderResource> shader;
	PointLight light;
	mat4 rot;
	mat4 transform;
	mat4 view;
	mat4 projection;
	Camera camera;
	int hasTexture;
	float shinyness;
	int hasNormalMap;
	std::vector<std::string> toActivate;
private:
	
};


