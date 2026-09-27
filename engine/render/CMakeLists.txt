#--------------------------------------------------------------------------
# render
#--------------------------------------------------------------------------

SET(files_render_display
	window.h
	window.cc
	grid.h
	grid.cc
	Meshresource.h
	Meshresource.cpp
	fragmentShader.glfs
	vertexShader.glvs
	fragmentShaderOld.glfs
	vertexShaderOld.glvs
	PointLight.h
	PointLight.cpp
	Material.h
	Material.cpp
	Camera.h
	textureResource.h
	textureResource.cpp
	stb_image.h
	g_buffer.glfs
	g_buffer.glvs
	deferred_shading.glfs
	deferred_shading.glvs
	deferred_light_box.glfs
	deferred_light_box.glvs)

SOURCE_GROUP("display" FILES ${files_render_display})


SET(files_render
	${files_render_display}
	${files_render_pch})

SET(files_pch ../config.h ../config.cc)
SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(render STATIC ${files_render} ${files_pch})
TARGET_PCH(render ../)	
ADD_DEPENDENCIES(render glew glfw)   
TARGET_LINK_LIBRARIES(render PUBLIC engine exts glew glfw imgui ${OPENGL_LIBS})