#pragma once
#include "core/mat4.h"
#include "core/ShaderResource.h"
#include "render/MeshResource.h"
#include "core/LoadGLTF.h"
#include "render/textureResource.h"
class GBuffer
{
public:
	GBuffer();
	~GBuffer();
	void SetUpBuffers();
	void LoadModels();
	void Setuniforms();
	void GeometryPass();
	void LightPass(float dt);
	void LightBoxPass();
	void RenderQuad();
	void RenderCube();
	void LoadShaders();
	void SetTexture(int i);
	void MakeDirectionalLight(vec3);
	int shiny;
	mat4 model;
	mat4 projection; 
	mat4 view;
	Camera camera;
private:
	
	GLuint gBuffer;
	GLuint gNormal;
	GLuint gAlbedoSpec;
	GLuint gPosition;
	GLuint gDepth;
	float radius = 0.01;
	double angle = 0.00;
	
	const int numberOfLights = 20;
	int amountOfItems = 20;
	unsigned int quadVAO = 0;
	unsigned int quadVBO;
	unsigned int cubeVAO = 0;
	unsigned int cubeVBO = 0;
	std::vector<vec3> objectPositions;
	std::vector<MeshResource> meshes;
	//MeshResource cube;
	std::vector<TextureResource> gltfTextures;
	std::vector<vec3> lightPositions;
	std::vector<vec3> lightColors;
	std::vector<mat4> lightTransforms;
	std::vector<mat4> objectTransforms;
	ShaderResource lightingPass;
	ShaderResource geometryPass;
	ShaderResource lightingBox;
	MeshResource sphere;
	MeshResource LightSphere;

	int SCR_WIDTH = 2560;
	int SCR_HEIGHT = 1440;
	GLTFLoader gltfLoader;

	//geometrypass uniforms
	GLint gbPosition;
	GLint gbNormal;
	GLint gbAlbedoSpec;
	GLint gbProjection;
	GLint gbView;
	GLint gbDiffuse;
	GLint gbSpecular;
	GLint gbModel;

	//lightpass uniforms
	GLint lpLightPositions;
	GLint lpLightColors;
	GLint lpLightLinears;
	GLint lpLightQuadratics;
	GLint lpViewPos;
	
	//lightbox uniforms
	GLint lbProjection;
	GLint lbView;
	GLint lbModel;
	GLint lbLightColor;
};
