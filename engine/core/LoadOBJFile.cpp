#include "config.h"
#include "LoadOBJFile.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "algorithm"
#include <vector>
#include <ctype.h>
#include <map>
#include <iterator>
OBJLoader::OBJLoader()
{
}

OBJLoader::~OBJLoader()
{
}
void OBJLoader::LoadOBJ(std::string fileName, MeshResource &mesh) {

	std::string vertexes;
	std::ifstream myFile(fileName);
	std::vector<vec3> position;
	std::vector<vec3> normals;
	std::vector<vec3> normalsHolder;
	std::vector<vec3> textureCordinates; //only use the first two numbers for texture cord
	std::vector<vec3> textureCordinatesHolder;
	int faceCount = 0;
	int normalCount = 0;
	int positionCount = 0;
	std::map<std::string, int> map;
	if (!myFile.is_open())
	{
		std::cout << "file not opening dumbass" << std::endl;
	}
	
	while(std::getline(myFile,vertexes))
	{
		std::istringstream ver(vertexes);
		std::string defintion;
		ver >> defintion;
		if (defintion == "v") {
			vec3 v;
			ver >> v.x >> v.y >> v.z;
			position.push_back(v);
			positionCount++;
		}
		else if (defintion == "vn")
		{
			vec3 v;
			ver >> v.x >> v.y >> v.z;
			normals.push_back(v);
			normalCount++;
		}
		else if (defintion =="vt")
		{
			vec3 v;
			ver >> v.x >> v.y;
			v.z = 0;
			textureCordinates.push_back(v);
			
		}
		else if (defintion == "f")
		{
			Vertex v;
			
			int pos;
			int text;
			int norm;
			
			
			
			
			
			
			
			for (int i = 0; i < 3; i++)
			{
				std::string data;
				ver >> data;
				
				

				
				if (map.count(data) == 0)
				{
					map[data] += 1;
					std::replace(data.begin(), data.end(), '/', ' ');
					std::istringstream ver2(data);


					ver2 >> pos >> text >> norm;
					//std::cout << norm << std::endl;

					mesh.indexBO.push_back(pos - 1);
					int temp = text - 1;
					textureCordinatesHolder.push_back(textureCordinates[temp]);
					normalsHolder.push_back(normals[norm - 1]);
				}
				else
				{
					std::map<std::string, int>::iterator refrence = map.find(data);
					data = refrence->first;
					std::replace(data.begin(), data.end(), '/', ' ');
					std::istringstream ver2(data);


					ver2 >> pos >> text >> norm;

					//data >> pos >> norm >> text;
					mesh.indexBO.push_back(pos - 1);
					int temp = text - 1;
					//std::cout << norm << std::endl;
					textureCordinatesHolder.push_back(textureCordinates[temp]);
					normalsHolder.push_back(normals[norm - 1]);
				}
			
				
			
			}
			faceCount++;
				//std::replace(data.begin(), data.end(), "/", " ");
			
			

			
		}
	}
	std::cout << faceCount << std::endl;
	int nj = 0;
	int pj = 0;
	int nsize = normals.size();
	int j = 0;
	/*for (int i = 0; i < mesh.indexBO.size(); i++)
	{
		std::cout << mesh.indexBO[i] << std::endl;
		j++;
		if (j >= 3)
		{
			j = 0;
			std::cout << std::endl;
		}
		*/
	//}
	for (int i = 0; i < faceCount; i++)
	{
		Vertex v;
		
		vec3 v3 = position[pj];
		v.position = v3;
		

		vec3 va = normalsHolder[nj];
		v.normals = va;
		
		
		
		v.textureCord[0] = textureCordinatesHolder[i][0];
		v.textureCord[1] = textureCordinatesHolder[i][1];
		
		
	
		nj++;
		if (nj >= normalCount)
		{
			nj = 0;
		}
		pj++;
		if (pj >= positionCount)
		{
			pj = 0;
		}
	
		v.color = vec4(0, 0, 0.9f, 1);
	
		
		mesh.vertexBO.push_back(v);
	}
	
	myFile.close();
	
}