#pragma once
#include <memory>
#include "render/Meshresource.h"
#include "core/ShaderResource.h"
#include "render/textureResource.h"
#include <string>
#include "core/mat4.h"
class GraphicsNode
{
public:
	GraphicsNode();
	GraphicsNode(MeshResource *mesh,ShaderResource  *shader, TextureResource *texture);
	~GraphicsNode();
	void draw(mat4 transform, mat4 view, mat4 projection, mat4 rotation);
	
	std::shared_ptr<MeshResource> mesh;
	std::shared_ptr<ShaderResource> shader;
	std::shared_ptr<TextureResource> texture;
private:

};
