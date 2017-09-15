
file(GLOB_RECURSE ENGINE_COMMON_HEADER   src/engine/common/*.h)
file(GLOB_RECURSE ENGINE_COMMON_SRC      src/engine/common/*.cpp)

file(GLOB_RECURSE CORE_HEADER            src/engine/core/*.h)
file(GLOB_RECURSE CORE_SRC               src/engine/core/*.cpp)
                                         
file(GLOB_RECURSE ENGINE_TOOLS_HEADER    src/engine/tools/*.h)
file(GLOB_RECURSE ENGINE_TOOLS_SRC       src/engine/tools/*.cpp)
                                         
file(GLOB_RECURSE MAP_HEADER             src/engine/map/*.h)
file(GLOB_RECURSE MAP_SRC                src/engine/map/*.cpp)

file(GLOB_RECURSE BUILDINGS_HEADER       src/engine/buildings/*.h)
file(GLOB_RECURSE BUILDINGS_SRC          src/engine/buildings/*.cpp)

file(GLOB_RECURSE VEHICLES_HEADER        src/engine/vehicles/*.h)
file(GLOB_RECURSE VEHICLES_SRC           src/engine/vehicles/*.cpp)

file(GLOB_RECURSE GL_FUNCTIONS_HEADER    src/graphics/gl_functions/*.h)
file(GLOB_RECURSE GL_FUNCTIONS_SRC       src/graphics/gl_functions/*.cpp)

file(GLOB_RECURSE GRAPHICS_TOOLS_HEADER  src/graphics/tools/*.h)
file(GLOB_RECURSE GRAPHICS_TOOLS_SRC     src/graphics/tools/*.cpp)

file(GLOB_RECURSE EVENT_MACHINE_HEADER   src/event_machine/*.h)
file(GLOB_RECURSE EVENT_MACHINE_SRC      src/event_machine/*.cpp)


set(FACTORY_GL_SRC ${ENGINE_COMMON_SRC}
                   ${CORE_SRC}
                   ${ENGINE_TOOLS_SRC}
                   ${MAP_SRC}
                   ${BUILDINGS_SRC}
                   ${VEHICLES_SRC}
                   ${GL_FUNCTIONS_SRC}
                   ${GRAPHICS_TOOLS_SRC}
                   ${EVENT_MACHINE_SRC}
                   src/main.cpp)
                   
set(FACTORY_GL_HEADER ${ENGINE_COMMON_HEADER}
                   ${CORE_HEADER}
                   ${ENGINE_TOOLS_HEADER}
                   ${MAP_HEADER}
                   ${BUILDINGS_HEADER}
                   ${VEHICLES_HEADER}
                   ${GL_FUNCTIONS_HEADER}
                   ${GRAPHICS_TOOLS_HEADER}
                   ${EVENT_MACHINE_HEADER})                   

                   
# Create folders in Visual Studio
                   
source_group("src\\engine\\common"               FILES ${ENGINE_COMMON_SRC})                   
source_group("src\\engine\\core"                 FILES ${CORE_SRC})
source_group("src\\engine\\tools"                FILES ${ENGINE_TOOLS_SRC})
source_group("src\\engine\\map"                  FILES ${MAP_SRC})
source_group("src\\engine\\buildings"            FILES ${BUILDINGS_SRC})
source_group("src\\engine\\vehicles"             FILES ${VEHICLES_SRC})
source_group("src\\graphics\\gl_functions"       FILES ${GL_FUNCTIONS_SRC})
source_group("src\\graphics\\tools"              FILES ${GRAPHICS_TOOLS_SRC})
source_group("src\\event_machine"                FILES ${EVENT_MACHINE_SRC})
source_group("src"                               src/main.cpp)

source_group("header\\engine\\common"            FILES ${ENGINE_COMMON_HEADER})        
source_group("header\\engine\\core"              FILES ${CORE_HEADER})
source_group("header\\engine\\tools"             FILES ${ENGINE_TOOLS_HEADER})
source_group("header\\engine\\map"               FILES ${MAP_HEADER})
source_group("header\\engine\\buildings"         FILES ${BUILDINGS_HEADER})
source_group("header\\engine\\vehicles"          FILES ${VEHICLES_HEADER})
source_group("header\\graphics\\gl_functions"    FILES ${GL_FUNCTIONS_HEADER})
source_group("header\\graphics\\tools"           FILES ${GRAPHICS_TOOLS_HEADER})
source_group("header\\event_machine"             FILES ${EVENT_MACHINE_HEADER})