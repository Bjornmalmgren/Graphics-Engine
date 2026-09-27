#include "config.h"
#include "Meshresource.h"
#include "GL/glew.h"


MeshResource::MeshResource() {





}


MeshResource::~MeshResource()
{

}

void MeshResource::setUpVBO(float* vertex, unsigned int size) {
	glGenBuffers(1, &this->vertexBuffer);//generatas a buffer 
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);//binds buffer
	glBufferData(GL_ARRAY_BUFFER, size, vertex, GL_STATIC_DRAW);//creates a new data store for vertex
}
void MeshResource::bindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);//binds the vertex buffer 
}
void MeshResource::setUpIBO(unsigned int* index, unsigned int size) {
	glGenBuffers(1, &this->indexBuffer);//generatas a buffer 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);//binds buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, index, GL_STATIC_DRAW);//creates a new data store for vertex
}
void MeshResource::bindIBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);//binds the index buffer
}
void MeshResource::setUpVertexAttributes() {
	glEnableVertexAttribArray(0); //enables generix vertex attribute with index 0
	glEnableVertexAttribArray(1); //enables generix vertex attribute with index 1
	glEnableVertexAttribArray(2); //enables generix vertex attribute with index 2
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 9, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 9, (GLvoid*)(sizeof(float32) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float32) * 9, (GLvoid*)(sizeof(float32) * 7));
}
void MeshResource::setUpVertexAttributesNT() {
	glEnableVertexAttribArray(0); //enables generix vertex attribute with index 0
	glEnableVertexAttribArray(1); //enables generix vertex attribute with index 1
	glEnableVertexAttribArray(2); //enables generix vertex attribute with index 2
	glEnableVertexAttribArray(3); //enables generix vertex attribute with index 2
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float32) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float32) * 7));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float32) * 7));
}
//draws the mesh
void MeshResource::drawMesh(int amount) {
	
	glDrawElements(GL_TRIANGLES, amount, GL_UNSIGNED_INT, (void*)0); //renders the data 
	//glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

}

void MeshResource::DrawWithShader(ShaderResource shader) {
	
	if (primitiveGroup.size() != 0) {
		for (int i = 0; i < primitiveGroup.size(); i++)
		{
			glBindVertexArray(primitiveGroup[i].VBO);
			glDrawElements(GL_TRIANGLES, primitiveGroup[i].indicesNum, type, (void*)(primitiveGroup[i].offset));
		}
		glBindVertexArray(0);
	}
	else if (sphereIndices.size() == 0) {
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indexBO.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	else
	{
		glBindVertexArray(sphereVAO);
		glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
	}
	
	

}

//creates a default quad mesh
void MeshResource::createQuad() {
	float vertex[] =
	{
		-0.5f,	-0.5f,	-1,			// pos 0
		1,		0,		0,		1,	// color 0

		0.5f,		-0.5f,	-1,			// pos 1
		0,		1,		0,		1,	// color 0

		0.5f,	0.5f,	-1,			// pos 2
		0.5f,		0.5f,		1,		1,	// color 0

		-0.5f,	0.5,	-1,			// pos 3
		1,		0,		1,		1	// color 0
	};
	setUpVBO(vertex, sizeof(vertex));
	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};
	setUpIBO(indices, sizeof(indices));
}
MeshResource MeshResource::createCube(int height, int width, int depth) {
	
	float heightbyte = 0.1f * height;
	float widthbyte = 0.1f * height;
	float depthbyte = 0.1f * height;

	unsigned int indices[] = {
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		8,9,10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,21,22,
		22,23,20

	};
	indexBO.reserve(36);
	indexBO.push_back(0);
	indexBO.push_back(1);
	indexBO.push_back(2);

	indexBO.push_back(2);
	indexBO.push_back(3);
	indexBO.push_back(0);

	indexBO.push_back(4);
	indexBO.push_back(5);
	indexBO.push_back(6);

	indexBO.push_back(6);
	indexBO.push_back(7);
	indexBO.push_back(4);

	indexBO.push_back(8);
	indexBO.push_back(9);
	indexBO.push_back(10);
	indexBO.push_back(10);
	indexBO.push_back(11);
	indexBO.push_back(8);

	indexBO.push_back(12);
	indexBO.push_back(13);
	indexBO.push_back(14);
	indexBO.push_back(14);
	indexBO.push_back(15);
	indexBO.push_back(12);

	indexBO.push_back(16);
	indexBO.push_back(17);
	indexBO.push_back(18);
	indexBO.push_back(18);
	indexBO.push_back(19);
	indexBO.push_back(16);

	indexBO.push_back(20);
	indexBO.push_back(21);
	indexBO.push_back(22);
	indexBO.push_back(22);
	indexBO.push_back(23);
	indexBO.push_back(20);
	float vertex[] =
	{
		//face one
		-widthbyte,	-heightbyte,	depthbyte,			// pos 0
		0.0f,		1.0f,		1.0f,		1.0f,	// color 0
		0.0f,0.0f,
		widthbyte,	-heightbyte,	depthbyte,			// pos 1
		0.0f,		1.0f,		1.0f,		1.0f,	// color 0
		1.0f,0.0f,
		widthbyte,	heightbyte,	depthbyte,		// pos 2
		0.0f,		1.0f,		1.0f,		1.0f,	// color 0
		1.0f,1.0f,
		- widthbyte,	heightbyte,depthbyte,			// pos 3
		0.0f,		1.0f,		1.0f,		1.0f,	// color 0
		0.0f,1.0f,


		 widthbyte,	heightbyte,	depthbyte,			// pos 12
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		0.0f,0.0f,
		widthbyte,	heightbyte,	-depthbyte,			// pos 13
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		0.0f,1.0f,
		widthbyte,	-heightbyte,	-depthbyte,		// pos 14
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		1.0f,1.0f,
		widthbyte,	-heightbyte,	depthbyte,			// pos 15
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0		
		1.0f,0.0f,

		

	    - widthbyte,	-heightbyte,	depthbyte,			// pos 8
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		0.0f,0.0f,
		widthbyte,	-heightbyte,	depthbyte,			// pos 9
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		0.0f,1.0f,
		widthbyte,	-heightbyte,	-depthbyte,		// pos 10
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		1.0f,1.0f,
		-widthbyte,	-heightbyte,	-depthbyte,			// pos 11
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0		
		1.0f,0.0f,

		

		-widthbyte,	heightbyte,	depthbyte,			// pos 16
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		0.0f,0.0f,
		widthbyte,	heightbyte,	depthbyte,			// pos 17
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		0.0f,1.0f,
		widthbyte,	heightbyte,	-depthbyte,		// pos 18
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		1.0f,1.0f,
		-widthbyte,	heightbyte,	-depthbyte,			// pos 19
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0		
		1.0f,0.0f,

		-widthbyte,	-heightbyte,	depthbyte,			// pos 20
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		0.0f,0.0f,
		-widthbyte,	heightbyte,	depthbyte,			// pos 21
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		0.0f,1.0f,
		-widthbyte,	heightbyte,	-depthbyte,		// pos 22
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		1.0f,1.0f,
		-widthbyte,	-heightbyte,	-depthbyte,			// pos 23
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0		
		1.0f,0.0f,

		-widthbyte,	-heightbyte,	-depthbyte,			// pos 4
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		0.0f,0.0f,
		-widthbyte,	heightbyte,	-depthbyte,			// pos 5
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		0.0f,1.0f,
		widthbyte,	heightbyte,	-depthbyte,		// pos 6
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0
		1.0f,1.0f,
		widthbyte,	-heightbyte,	-depthbyte,			// pos 7
		1.0f,		0.0f,		1.0f,		1.0f,	// color 0		
		1.0f,0.0f,
	};
	
	setUpVBO(vertex, sizeof(vertex));
	bindVBO();
	setUpIBO(indices, sizeof(indices));
	bindIBO();

	return *this;
}

void MeshResource::deleteResources() {
	glDeleteBuffers(sizeof(indexBuffer), &indexBuffer);
	glDeleteBuffers(sizeof(vertexBuffer), &vertexBuffer);
}

void MeshResource::setUpOBJIBO() {
	glGenBuffers(1, &this->indexBuffer);//generatas a buffer 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);//binds buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBO.size() * sizeof(GLuint), indexBO.data(), GL_STATIC_DRAW);//creates a new data store for vertex

}
void MeshResource::setUpOBJVBO() { 
	glGenBuffers(1, &this->vertexBuffer);//generatas a buffer 
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);//binds buffer
	glBufferData(GL_ARRAY_BUFFER, vertexBO.size() * sizeof(Vertex), vertexBO.data(), GL_STATIC_DRAW);//creates a new data store for vertex

}
void MeshResource::setUpBuffers() {

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	setUpOBJVBO();
	bindVBO();
	setUpOBJIBO();
	bindIBO();
	glBindVertexArray(0);
}

void MeshResource::drawOBJ(int amount) {
	
	//glBindVertexArray(VAO);
	//glBindVertexArray(VBO);
	//BPM.Apply();
	for (int i = 0; i < primitiveGroup.size(); i++)
	{
		glBindVertexArray(primitiveGroup[i].VBO);
		glDrawElements(GL_TRIANGLES, primitiveGroup[i].indicesNum, type, (void*)(primitiveGroup[i].offset));
	}
	glBindVertexArray(0);
	 //renders the data 
	//glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

}

void MeshResource::buildSphere() {
	float PI = acos(-1.0f);
	
	float x;
	float y;
	float z;
	float xy;
	float nx, ny, nz, length = 1.0f / sphereRadius;
	float s, t;

	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle;
	float stackAngle;
	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;
		xy = sphereRadius * cosf(stackAngle);
		z = sphereRadius * sinf(stackAngle);
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;
			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);
			sphereVerticies.push_back(x);
			sphereVerticies.push_back(y);
			sphereVerticies.push_back(z);

			nx = -(x * length);
			ny = -(y * length);
			nz = -(z * length);
			sphereNormals.push_back(nx);
			sphereNormals.push_back(ny);
			sphereNormals.push_back(nz);
			//textture coordinates
			s = ((float)j) / sectorCount;
			t = ((float)i) / stackCount;
			sphereTexCoords.push_back(s);
			sphereTexCoords.push_back(t);
		}
	}

	unsigned int k1;
	unsigned int k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     
		k2 = k1 + sectorCount + 1;
		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			if (i != 0) {
				sphereIndices.push_back(k1);
				sphereIndices.push_back(k2);
				sphereIndices.push_back(k1 + 1);
			}
			if (i != (stackCount - 1)) {
				sphereIndices.push_back(k1 + 1);
				sphereIndices.push_back(k2);
				sphereIndices.push_back(k2 + 1);
			}
			sphereLineIndices.push_back(k1);
			sphereLineIndices.push_back(k2);
			if (i != 0) {
				sphereLineIndices.push_back(k1);
				sphereLineIndices.push_back(k1 + 1);
			}
		}
	}
	BuildInterleavedVertices();
}

void MeshResource::drawSphere() {
	//BPM.Apply();
	
	glBindVertexArray(sphereVAO);
	glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

void MeshResource::SetUpSphere() {
	glGenVertexArrays(1, &sphereVAO);
	glBindVertexArray(sphereVAO);

	glGenBuffers(1, &sphereVBO);
	glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
	glBufferData(GL_ARRAY_BUFFER, (unsigned int)sphereInterleavedVertices.size() * sizeof(float), sphereInterleavedVertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &sphereIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (unsigned int)sphereIndices.size() * sizeof(unsigned int), sphereIndices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(int)*8, (void*)0);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(int) * 8, (void*)(sizeof(float) * 3));
	glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(int) * 8, (void*)(sizeof(float) * 5));

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	vertexBuffer = 0;
	
}
void MeshResource::BuildInterleavedVertices() {
	size_t i, j;
	size_t count = sphereVerticies.size();
	for (i = 0, j = 0; i < count; i += 3, j += 2)
	{
		sphereInterleavedVertices.push_back(sphereVerticies[i]);
		sphereInterleavedVertices.push_back(sphereVerticies[i + 1]);
		sphereInterleavedVertices.push_back(sphereVerticies[i + 2]);

		sphereInterleavedVertices.push_back(sphereNormals[i]);
		sphereInterleavedVertices.push_back(sphereNormals[i + 1]);
		sphereInterleavedVertices.push_back(sphereNormals[i + 2]);

		sphereInterleavedVertices.push_back(sphereTexCoords[j]);
		sphereInterleavedVertices.push_back(sphereTexCoords[j + 1]);
	}
}

