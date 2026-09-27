#--------------------------------------------------------------------------
# Camera and Texture project
#--------------------------------------------------------------------------

PROJECT(matAndGLTF)
FILE(GLOB matAndGLTF_headers code/*.h)
FILE(GLOB matAndGLTF_sources code/*.cc)


SET(files_matAndGLTF ${matAndGLTF_headers} ${matAndGLTF_sources})
SOURCE_GROUP("matAndGLTF" FILES ${files_matAndGLTF})

ADD_EXECUTABLE(matAndGLTF ${files_matAndGLTF})
TARGET_LINK_LIBRARIES(matAndGLTF core render)
ADD_DEPENDENCIES(matAndGLTF core render)