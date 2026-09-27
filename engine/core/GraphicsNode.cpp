#include "config.h"
#include "GraphicsNode.h"
GraphicsNode::GraphicsNode()
{

}
GraphicsNode::GraphicsNode(MeshResource* mesh, ShaderResource* shader, TextureResource* texture)
{
	this->mesh = std::shared_ptr<MeshResource>(mesh);
	this->shader = std::shared_ptr<ShaderResource>(shader);
	this->texture = std::shared_ptr<TextureResource>(texture);
}


GraphicsNode::~GraphicsNode()
{
}


void GraphicsNode::draw(mat4 transform, mat4 view, mat4 projection, mat4 rotation) {
	GLint transfor = shader.get()->UniformLocation("transform");
	GLint rot = shader.get()->UniformLocation("rotation");//binds to the rotation variable
	GLint views = shader.get()->UniformLocation("view");
	GLint projectins = shader.get()->UniformLocation("projection");
	glUniformMatrix4fv(transfor, 1, GL_FALSE, (GLfloat*)&transform);
	glUniformMatrix4fv(views, 1, GL_TRUE, (GLfloat*)&view);
	glUniformMatrix4fv(projectins, 1, GL_TRUE, (GLfloat*)&projection);
	glUniformMatrix4fv(rot, 1, GL_TRUE, (GLfloat*)&rotation);
	mesh.get()->setUpVertexAttributes();
	mesh.get()->bindIBO();
	if (texture != nullptr) {
		GLint has = shader.get()->UniformLocation("Texture");
		GLint hasTexture = shader.get()->UniformLocation("hasTexture");
		glUniform1i(hasTexture, 1);
		glUniform1i(has, 0);
		texture.get()->bind(0);
	}
	
	mesh.get()->drawMesh(mesh.get()->indexBO.size());
}