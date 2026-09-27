#--------------------------------------------------------------------------
# Shaders and GrphicsNode project
#--------------------------------------------------------------------------

PROJECT(ShadAndNode)
FILE(GLOB ShadAndNode_headers code/*.h)
FILE(GLOB ShadAndNode_sources code/*.cc)

SET(files_ShadAndNode ${ShadAndNode_headers} ${ShadAndNode_sources})
SOURCE_GROUP("ShadAndNode" FILES ${files_ShadAndNode})

ADD_EXECUTABLE(ShadAndNode ${files_ShadAndNode})
TARGET_LINK_LIBRARIES(ShadAndNode core render)
ADD_DEPENDENCIES(ShadAndNode core render)