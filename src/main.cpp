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
#include "event_machine/event_machine.h"
#include "graphics/mediator.h"

#include "engine/core/simple_engine.h"

#include <iostream>


int main()
{
    try
    {
        GLFWwindow * window  = graphics::GlInitialization::opengl_start();

        std::cout << "Start the main loop ..." << std::endl;

        auto p_eventMachine = std::make_shared<eventmachine::EventMachine>();

        // Engine
        engine::SimpleEngine engineObj(p_eventMachine);

        // Get Mediator
        auto p_mediatorObj = std::make_shared<mediator::Mediator>(&engineObj);

        // Add receiver in Event Machine
        p_eventMachine->add_receiver(p_mediatorObj.get());

        // Draw Fps
        std::shared_ptr<mediator::ObserverCalcFps> drawFps (new graphics::DrawFps);

        //
        p_mediatorObj->add_observer_calc_fps(drawFps);

        // Main Loop
        while(!glfwWindowShouldClose(window))
        {
            // Catch events
            glfwPollEvents();

            // Call step for engine
            engineObj.step();

            // Clear a buffer
            glClear(GL_COLOR_BUFFER_BIT);

            // Swap buffers
            glfwSwapBuffers(window);
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
