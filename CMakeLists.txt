cmake_minimum_required(VERSION 2.8)

project(OpenGLgames)

add_definitions(-std=c++1y -Wall)

include_directories(${PROJECT_SOURCE_DIR}/src)

set(SRC src/main.cpp

        src/engine/core/engine.h
        src/engine/core/simple_engine.h
        src/engine/core/simple_engine.cpp

        src/engine/tools/tool.h
        src/engine/tools/calc_fps.h
        src/engine/tools/calc_fps.cpp
        
        src/graphics/gl_functions/gl_initialization.cpp
        src/graphics/gl_functions/gl_initialization.h
        src/graphics/gl_functions/keys_actions.h
        src/graphics/gl_functions/keys_actions.cpp
        
        src/graphics/mediator.h
        src/graphics/mediator.cpp
        src/graphics/observers.h
        
        src/graphics/tools/draw_fps.h
        src/graphics/tools/draw_fps.cpp

        src/engine/map/map.h
        src/engine/map/map.cpp

        src/engine/vehicles/action_object.h
        src/engine/vehicles/vehicle.h
        src/engine/vehicles/vehicle_unit.h
        src/engine/vehicles/vehicle_unit.cpp
        )

add_executable(FactoryGL ${SRC})

target_link_libraries(FactoryGL glfw3 
                                GLEW 
                                X11 
                                Xrandr 
                                Xinerama 
                                Xcursor 
                                dl 
                                GL 
                                pthread)

