#include "config.h"
#include "textureResource.h"
#define STB_IMAGE_IMPLEMENTATION
#include "render/stb_image.h"
TextureResource::TextureResource()
{
	this->texture = 0;
	this->width = 512;
	this->height = 512;
	this->nrChannels = 0;
}

TextureResource::~TextureResource()
{
}

void TextureResource::LoadFromMemory(const unsigned char* buffer, int unit, int length) {
	
	auto data = stbi_load_from_memory(buffer, length, &width, &height, & nrChannels, 3);
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "not working " << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureResource::LoadFromFile(std::string name, int unit) {
		
		unsigned char* dataptr = stbi_load(name.c_str(), &width, &height, &nrChannels, 3);
		
		//unsigned char* dataptr = stbi_load(name, &width, &height, &nrChannels, 0);
		glGenTextures(1, &texture);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (dataptr) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataptr);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "not working " << std::endl;
		}

		stbi_image_free(dataptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	
	
		
	
}
void TextureResource::bind(int unit) {
	
	glActiveTexture(GL_TEXTURE0+unit);
	glBindTexture(GL_TEXTURE_2D, texture);
	

}