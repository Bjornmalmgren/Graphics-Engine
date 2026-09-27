#--------------------------------------------------------------------------
# Camera and Texture project
#--------------------------------------------------------------------------

PROJECT(LightingAndOBJ)
FILE(GLOB LightingAndOBJ_headers code/*.h)
FILE(GLOB LightingAndOBJ_sources code/*.cc)

SET(files_LightingAndOBJ ${LightingAndOBJ_headers} ${LightingAndOBJ_sources})
SOURCE_GROUP("LightingAndOBJ" FILES ${files_LightingAndOBJ})

ADD_EXECUTABLE(LightingAndOBJ ${files_LightingAndOBJ})
TARGET_LINK_LIBRARIES(LightingAndOBJ core render)
ADD_DEPENDENCIES(LightingAndOBJ core render)