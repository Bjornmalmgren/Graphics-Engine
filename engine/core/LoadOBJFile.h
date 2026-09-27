#pragma once
#include "render/Meshresource.h"

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();
	void LoadOBJ(std::string fileName, MeshResource &mesh);
private:

};
