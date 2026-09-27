#pragma once
#include "vector"
#include "core/mat4.h"
#include "GL/glew.h"
#include "render/Material.h"
#include "textureResource.h"
#define _USE_MATH_DEFINES
#include "math.h"
struct Vertex
{
	vec3 position;
	vec4 color;
	GLfloat textureCord[2];
	
	vec3 normals;

};

struct GLTFMaterial
{
	vec4 baseColorFactor = vec4(1, 1, 1, 1); 
	int baseColorTexture = -1;
	enum class AlphaMode :uint8_t
	{
		Opaque, Mask, Blend
	};
	float alphaCutOff{0.5f};
	AlphaMode alphamode{ AlphaMode::Opaque };
	bool doubleSided = false;
};

struct primitive
{
	GLuint64 offset;
	GLuint64 indicesNum;
	GLuint VBO;
	GLTFMaterial material; 
};

class MeshResource
{
public:
	MeshResource();
	~MeshResource();
	std::vector<Vertex> vertexBO;
	std::vector<unsigned int> indexBO;
	std::vector<primitive> primitiveGroup;
	GLuint vertexBuffer; // for gltf loading
	GLuint indexBuffer;
	GLuint VAO;
	unsigned type = GL_UNSIGNED_INT;
	BlinnPhongMaterial BPM;
	std::vector<GLuint> buffers;
	std::vector<TextureResource> textures;
	void setUpBuffers();
	void setUpVBO(float* vertex, unsigned int size);
	void bindVBO();
	void setUpIBO(unsigned int* index, unsigned int size);
	void bindIBO();
	void setUpOBJIBO();
	void setUpOBJVBO();
	void setUpVertexAttributes();
	void setUpVertexAttributesNT();
	void buildSphere();
	void drawMesh(int);
	void drawOBJ(int amount);
	void drawSphere();
	void SetUpSphere();
	void createQuad();
	void BuildInterleavedVertices();
	void DrawWithShader(ShaderResource);
	MeshResource createCube(int, int, int);
	void deleteResources();
	//thigs to make a sphere
	GLuint sphereVAO;
	GLuint sphereVBO;
	GLuint sphereIBO;
	float sphereRadius;
	int sectorCount;
	int stackCount;
	std::vector<float> sphereVerticies;
	std::vector<float> sphereNormals;
	std::vector<float> sphereTexCoords;
	std::vector<float> sphereInterleavedVertices;
	std::vector<unsigned int> sphereIndices;
	std::vector<unsigned int> sphereLineIndices;
private:

};
