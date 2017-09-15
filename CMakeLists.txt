include(sources.cmake)

cmake_minimum_required(VERSION 2.8)

project(OpenGLgames)


#################### Definitions #################################

add_definitions(-std=c++1y -Wall)

# Add predefined variables for:
#   - Shaders
#   - Textures
add_definitions(-DSRC_WITH_SHADERS="${PROJECT_SOURCE_DIR}/src/shaders")
add_definitions(-DTEXTURE_FOLDER="${PROJECT_SOURCE_DIR}/textures")


################### Import libs #####################################

# Import GLEW
set (GLEW_libs ${PROJECT_SOURCE_DIR}/import/libs/win64/lib/glew32s.lib)

# Import GLFW
set (GLFW_libs ${PROJECT_SOURCE_DIR}/import/libs/win64/lib/glfw3.lib)

## Add SOIL lib
#set (SOIL_include /opt/SOIL/include)
#set (SOIL_libs /opt/SOIL/lib/libSOIL.a)
set(SOIL_libs ${PROJECT_SOURCE_DIR}/import/libs/win64/lib/SOIL.lib)

# Imported lib
set (Imported_include ${PROJECT_SOURCE_DIR}/import/include)


################## Include #############################################

include_directories(${PROJECT_SOURCE_DIR}/src)

################### FactoryGL ##########################################

add_executable(FactoryGL ${FACTORY_GL_SRC} ${FACTORY_GL_HEADER})
set_target_properties(FactoryGL PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(FactoryGL PUBLIC ${SOIL_include}
                                            ${Imported_include} )

                                            
                                      
                                            
target_link_libraries(FactoryGL opengl32
                                ${SOIL_libs}
                                ${GLEW_libs}
                                ${GLFW_libs})
                                