#--------------------------------------------------------------------------
# Camera and Texture project
#--------------------------------------------------------------------------

PROJECT(CamAndTex)
FILE(GLOB CamAndTex_headers code/*.h)
FILE(GLOB CamAndTex_sources code/*.cc)
FILE(GLOB CamAndTex_pictures code/*.png)

SET(files_CamAndTex ${CamAndTex_headers} ${CamAndTex_sources})
SOURCE_GROUP("CamAndTex" FILES ${files_CamAndTex})

ADD_EXECUTABLE(CamAndTex ${files_CamAndTex})
TARGET_LINK_LIBRARIES(CamAndTex core render)
ADD_DEPENDENCIES(CamAndTex core render)