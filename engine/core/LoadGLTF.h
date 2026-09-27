#pragma once
#include "core/gltf.h"
#include "core/json.hpp"
#include "GL/glew.h"
#include "render/MeshResource.h"
#include "render/textureResource.h"
using json = nlohmann::json;
class GLTFLoader
{
public:
	GLTFLoader();
	~GLTFLoader();
	std::vector<std::string> loadGLTF(std::string toFile,std::string fileName, MeshResource& model, std::vector<std::string>& toActivate);
	int SlotFromGLTF(std::string attribute);
	bool hasBeenActivated(std::string activate, std::vector<std::string> toActivate);
	bool tangentExists = false;
private:

};
