#pragma once
#include "GL/glew.h"
#include "iostream"
#include <vector>
class TextureResource
{
public:
	TextureResource();
	~TextureResource();
	void LoadFromFile(std::string name, int unit);
	void bind(int unit);
	void LoadFromMemory(const unsigned char* buffer, int unit, int length);
	std::string type;
	int id;
private:
	GLuint texture;
	int width;
	int height;
	int nrChannels;
	
};

