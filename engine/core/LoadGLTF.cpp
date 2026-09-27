#include "config.h"
#include "LoadGLTF.h"

GLTFLoader::GLTFLoader()
{
}

GLTFLoader::~GLTFLoader()
{
}

int GLTFLoader::SlotFromGLTF(std::string attribute) {
	if (attribute == "POSITION") {
		return 0;
	}
	else if (attribute == "NORMAL")
	{
		return 3;
	}
	else if (attribute == "TEXCOORD_0")
	{
		return 2;
	}
	else if (attribute == "TANGENT")
	{
		return 4;
	}
}

bool GLTFLoader::hasBeenActivated(std::string activate, std::vector<std::string> toActivate) {
	for (int i = 0; i < toActivate.size(); i++)
	{
		if (toActivate[i] == activate) {
			return true;
		}
	}
	return false;
}


std::vector<std::string> GLTFLoader::loadGLTF(std::string toFile,std::string fileName, MeshResource& model, std::vector<std::string>& toActivate) {
	fx::gltf::Document doc = fx::gltf::LoadFromText(fileName);
	model.buffers.reserve(doc.bufferViews.size());
	std::string path;

	std::vector<std::string> paths;
	for (size_t i = 0; i < doc.bufferViews.size(); i++)
	{
		model.buffers.push_back(0);
	}
	
	glGenBuffers(doc.bufferViews.size(), model.buffers.data());
	for (unsigned i = 0; i < doc.bufferViews.size(); i++)
	{
		auto const& bufferView = doc.bufferViews[i];
		GLenum target = (GLenum)bufferView.target;
		if (target == 0) {
			if (bufferView.name != "") {
				size_t found = bufferView.name.find("Scalar");
				if (found != std::string::npos) {
					target = GL_ELEMENT_ARRAY_BUFFER;
				}
			}else
			{
				for (auto const& mesh : doc.meshes)
				{
					for (auto const& prim : mesh.primitives)
					{
						for (auto const& attri : prim.attributes) {
							auto const& accessor = doc.accessors[attri.second];
							if (accessor.type == fx::gltf::Accessor::Type::Scalar)
							{
								target = GL_ELEMENT_ARRAY_BUFFER;
							}
						}
					}
				}
			}
			if (target == 0) {
				target = GL_ARRAY_BUFFER;
			}
			
		}
		glBindBuffer(target, model.buffers[i]);
		glBufferData(target, bufferView.byteLength, (byte*)(doc.buffers[bufferView.buffer].data.data()) + bufferView.byteOffset, GL_STATIC_DRAW);
	}
	int i = 0;
	for (auto const& mesh : doc.meshes)
	{
	
		for (auto const& prim : mesh.primitives)
		{
			primitive p;
			glGenVertexArrays(1, &p.VBO);
			glBindVertexArray(p.VBO);
			for (auto const& attri : prim.attributes)
			{
				auto const& accessor = doc.accessors[attri.second];
				auto offeset = accessor.byteOffset;
				auto stride = doc.bufferViews[accessor.bufferView].byteStride;

				auto normalized = accessor.normalized;
				auto type = (GLenum)accessor.componentType;
				/*auto type = (GLenum)accessor.componentType;*/
				auto slot = SlotFromGLTF(attri.first);
				GLenum component;
				switch (accessor.type)
				{
				case fx::gltf::Accessor::Type::Scalar:
					component = 1;
					break;
				case fx::gltf::Accessor::Type::Vec2:
				case fx::gltf::Accessor::Type::Vec3:
				case fx::gltf::Accessor::Type::Vec4:
					component = (GLint)accessor.type;
					break;
				default:
					
					break;
				}
				auto target = (GLenum)doc.bufferViews[accessor.bufferView].target;
				if (target == 0) {
					switch (accessor.type)
					{
					case fx::gltf::Accessor::Type::Scalar:
						target = GL_ELEMENT_ARRAY_BUFFER;
						break;
					default:
						target = GL_ARRAY_BUFFER;
						
					}
				}
				glBindBuffer(target, model.buffers[accessor.bufferView]);
				glEnableVertexArrayAttrib(p.VBO, slot);
				glVertexAttribPointer(slot, component, type, normalized, stride, (void*)(intptr_t)offeset);

			}
			


			auto const& iaccessor = doc.accessors[prim.indices]; 
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.buffers[iaccessor.bufferView]);
			p.indicesNum = iaccessor.count;
			p.offset = iaccessor.byteOffset;
			

			//both embeded and non embeded
			if (doc.images[doc.materials[prim.material].pbrMetallicRoughness.baseColorTexture.index].IsEmbeddedResource()) {
				std::vector<unsigned char> vec;
				doc.images[doc.materials[prim.material].pbrMetallicRoughness.baseColorTexture.index].MaterializeData(vec);
				TextureResource t;
				unsigned char s;
				for (int i = 0; i < vec.size(); i++)
				{
					s = s + vec[i];
				}
				t.LoadFromMemory(&s,0,vec.size());
				model.textures.push_back(t);
				toActivate.push_back("Texture");
				
			}
			else
			{
				path = toFile + doc.images[doc.materials[prim.material].pbrMetallicRoughness.baseColorTexture.index].uri.c_str();
				paths.push_back(path);
				toActivate.push_back("Texture");
			}
			
			/*if (!hasBeenActivated("Texture", toActivate)) {
				toActivate.push_back("Texture");
			}*/
			//not used
			//if (doc.materials[prim.material].emissiveTexture.empty() != true) {
			//	path = toFile + doc.images[doc.materials[prim.material].emissiveTexture.index].uri.c_str();
			//	paths.push_back(path);
			//	toActivate.push_back("emissive");
			//	/*if (!hasBeenActivated("emissive", toActivate)) {
			//		toActivate.push_back("emissive");
			//	}*/
			//	
			//}
			//not used
			/*if (doc.materials[prim.material].pbrMetallicRoughness.metallicRoughnessTexture.empty() != true) {
				path = toFile + doc.images[doc.materials[prim.material].pbrMetallicRoughness.metallicRoughnessTexture.index].uri.c_str();
				paths.push_back(path);
				toActivate.push_back("metal");
			}*/
			
			/*if (!hasBeenActivated("metal", toActivate)) {
				toActivate.push_back("metal");
			}*/
			//not used
			/*if (doc.materials[prim.material].occlusionTexture.empty() != true) {
				path = toFile + doc.images[doc.materials[prim.material].occlusionTexture.index].uri.c_str();
				paths.push_back(path);
				toActivate.push_back("AO");
			}*/
			
			/*if (!hasBeenActivated("AO", toActivate)) {
				toActivate.push_back("AO");
			}*/
			//both embeded and non embeded
			if (doc.materials[prim.material].normalTexture.empty() != true) {
				if (doc.images[doc.materials[prim.material].normalTexture.index].IsEmbeddedResource()) {
					std::vector<unsigned char> vec;
					doc.images[doc.materials[prim.material].normalTexture.index].MaterializeData(vec);
					TextureResource t;
					unsigned char s;
					for (int i = 0; i < vec.size(); i++)
					{
						s = s + vec[i];
					}
					t.LoadFromMemory(&s, 0, vec.size());
					model.textures.push_back(t);
					toActivate.push_back("normalMap");
					model.BPM.hasNormalMap = 1;
				}
				else {
					path = toFile + doc.images[doc.materials[prim.material].normalTexture.index].uri.c_str();
					paths.push_back(path);
					toActivate.push_back("normalMap");
					model.BPM.hasNormalMap = 1;
				}
			}
			
			
			/*if (!hasBeenActivated("normalMap", toActivate)) {
				toActivate.push_back("normalMap");
			}*/
			
			glBindVertexArray(0);
			model.primitiveGroup.push_back(std::move(p));
		}
	}
	
	
	
	
	return paths;
}