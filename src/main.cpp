// GLEW need to include before GLFW.
// GLEW
//#define GLEW_STATIC
//#include <GL/glew.h>
//// GLFW
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include <vector>

#include "graphics/gl_functions/gl_initialization.h"
#include "graphics/tools/draw_fps.h"
//#include "graphics/observers.h"

#include "engine/core/simple_engine.h"

#include <iostream>
#include <chrono>
#include <thread>


int main()
{
    try
    {
        GLFWwindow * window  = graphics::GlInitialization::opengl_start();

        std::cout << "Start the main loop ..." << std::endl;

        // Engine
        engine::SimpleEngine engineObj;

        // Get Mediator
        mediator::Mediator * p_mediatorObj = engineObj.get_mediator();

        // Draw Fps
        std::shared_ptr<mediator::ObserverCalcFps> drawFps (new graphics::DrawFps);

        //
        p_mediatorObj->add_observer_calc_fps(drawFps);

        // Main Loop
        while(!glfwWindowShouldClose(window))
        {
        	// Startcycle time
			auto startCycleTime = std::chrono::high_resolution_clock::now();

            // Catch events
            glfwPollEvents();

            // Call step for engine
            engineObj.step();

            // Clear a buffer
            glClear(GL_COLOR_BUFFER_BIT);

            // Swap buffers
            glfwSwapBuffers(window);

            // Timeout to get no more than 60 fps
            std::this_thread::sleep_until(startCycleTime + std::chrono::microseconds(16667));
        }

        glfwTerminate();
    }
    catch(std::runtime_error & err)
    {
        std::cerr << "Runtime exception was caught : "  << err.what() << "\n";
        glfwTerminate();
    }
    catch(...)
    {
        std::cerr << "Any exception was caught\n";
        glfwTerminate();
    }

    return 0;


}
