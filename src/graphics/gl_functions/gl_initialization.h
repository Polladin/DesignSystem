
#pragma once


#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

// GLEW need to include before GLFW.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>


namespace graphics{


const int DEFAULT_WINDOW_WIDTH = 800;
const int DEFAULT_WINDOW_HEIGHT = 600;


/**
 *      GLInitializaiton
 *
 */
class GlInitialization
{
public:

    GlInitialization(bool setUnlimitedFps = false) { window = opengl_start(setUnlimitedFps); }

    GLFWwindow * get_window() { return window; }

    ~GlInitialization() { glfwTerminate(); }

private:

    // Initialize OpenGL libs and create a window
    GLFWwindow * opengl_start(bool setUnlimitedFps = false);

    // Initialize GLFW lib
    static void initialize_glfw();

    // Create a window and set as a current context
    static GLFWwindow * create_window(int width, int height);

    // Initialize GLEW lib
    static void initialize_glew();

    // Get width and height from a window
    static std::pair<int, int> get_width_and_height(GLFWwindow * window);

private:

    GLFWwindow * window;

};


}//namespace graphics
