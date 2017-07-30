
#include "gl_initialization.h"

#include "graphics/gl_functions/keys_actions.h"

#include <stdexcept>
#include <iostream>


namespace graphics{


GLFWwindow * GlInitialization::opengl_start(bool setUnlimitedFps)
{
    // Initializing GLFW
    initialize_glfw();

    // Create a glfw window and set as current context
    GLFWwindow * window  = create_window(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

    // Initializing GLEW
    initialize_glew();

    // Get width and height of a window
    auto widthHeightPair = get_width_and_height(window);

    // Set a viewport
    glViewport(0, 0, widthHeightPair.first, widthHeightPair.second);

    // Set keys callback
    glfwSetKeyCallback(window, KeysCallback::default_callback);

    // Set unlimited fps
    glfwSwapInterval((setUnlimitedFps ? 0 : 1));

    // Set the color after clear
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    return window;
}


void GlInitialization::initialize_glfw()
{
    // Initialize GLFW
    glfwInit();

    // Set minimal OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Use only CORE OpenGL function
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Restrict to resize a window
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}


GLFWwindow * GlInitialization::create_window(int width, int height)
{
    // Create a window
    GLFWwindow * window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);

    // Unable to create a window
    if (window == nullptr)
        throw std::runtime_error("Failed to create GLFW window");

    // Set as a current context
    glfwMakeContextCurrent(window);

    return window;
}


void GlInitialization::initialize_glew()
{
    // Able to use newest functions
    glewExperimental = GL_TRUE;

    // Initialize GLEW
    GLenum err = glewInit();

    // If fail to initialize GLEW
    if (err != GLEW_OK)
        throw std::runtime_error("Failed to initialize GLEW");
}


std::pair<int, int> GlInitialization::get_width_and_height(GLFWwindow * window)
{
    int   width  {800}
        , height {600};

    // if window is nullptr returns a default values
    if (window != nullptr)
        glfwGetFramebufferSize(window, &width, &height);

    return std::make_pair(width, height);
}


}//namespace graphics

