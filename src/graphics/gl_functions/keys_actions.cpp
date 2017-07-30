
#include "keys_actions.h"


namespace graphics{


// ------------------------------ KeysCallback ---------------------------------------

void KeysCallback::default_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    // Stop main loop if a key ESCAPE was pressed
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


}//namespace graphics{
