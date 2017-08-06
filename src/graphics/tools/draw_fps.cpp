
#include "draw_fps.h"

#include "engine/core/engine.h"

namespace graphics{


void DrawFps::update_fps(float newFps)
{
    fps = newFps;

//    std::cout << "FPS update : " << fps << std::endl;
}


}//namespace graphics
