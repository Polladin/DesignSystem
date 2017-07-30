
#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace graphics{


/**
 *      KeysCallback
 *
 */
class KeysCallback
{
private:

public:

    static void default_callback(GLFWwindow * window, int key, int scancode, int action, int mods);

};


}//namespace graphics
