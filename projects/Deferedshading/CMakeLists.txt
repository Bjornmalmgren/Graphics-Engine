#--------------------------------------------------------------------------
# Camera and Texture project
#--------------------------------------------------------------------------

PROJECT(defShading)
FILE(GLOB defShading_headers code/*.h)
FILE(GLOB defShading_sources code/*.cc)


SET(files_defShading ${defShading_headers} ${defShading_sources})
SOURCE_GROUP("defShading" FILES ${files_defShading})

ADD_EXECUTABLE(defShading ${files_defShading})
TARGET_LINK_LIBRARIES(defShading core render)
ADD_DEPENDENCIES(defShading core render)