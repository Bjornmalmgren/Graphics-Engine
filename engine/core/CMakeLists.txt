#--------------------------------------------------------------------------
# core
#--------------------------------------------------------------------------

SET(files_core
	app.h
	app.cc
	vec3.h
	vec4.h
	mat4.h
	ShaderResource.h
	ShaderResource.cpp
	GraphicsNode.h
	GraphicsNode.cpp
	LoadOBJFile.cpp
	LoadOBJFile.h
	LoadGLTF.h
	LoadGLTF.cpp
	gltf.h
	GBuffer.h
	GBuffer.cpp)
SOURCE_GROUP("core" FILES ${files_core})
SET(files_pch ../config.h ../config.cc)
SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(core STATIC ${files_core} ${files_pch})
TARGET_PCH(core ../)
ADD_DEPENDENCIES(core glew)
TARGET_LINK_LIBRARIES(core PUBLIC engine exts glew)

 