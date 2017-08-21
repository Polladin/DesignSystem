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
#include "graphics/gl_functions/shader_functions.h"
#include "engine/core/simple_engine.h"
#include "graphics/gl_functions/textures.h"

#include "SOIL.h"


#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>
#include <chrono>
#include <thread>


int main()
{
    // Set up vertex data (and buffer(s)) and attribute pointers
    std::vector<GLfloat> vertices {
        // Positions          // Colors           // Texture Coords
                 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   3.0f, 3.0f, // Top Right
                 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   3.0f, 0.0f, // Bottom Right
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
                -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 3.0f  // Top Left
                                   };

    std::vector<GLuint> indices {// Помните, что мы начинаем с 0!
                                        0, 1, 3,   // Первый треугольник
                                        1, 2, 3    // Второй треугольник
                                  };

    try
    {
        std::unique_ptr<graphics::GlInitialization> glLib(new graphics::GlInitialization());

        std::cout << "Start the main loop ..." << std::endl;

        // Create an Event Machine
        auto p_eventMachine = std::make_shared<eventmachine::EventMachine>();

        // Create an Engine
        engine::SimpleEngine engineObj(p_eventMachine);

        // Create a Mediator
        auto p_mediatorObj = std::make_shared<mediator::Mediator>(&engineObj);

        // Add receiver in Event Machine
        p_eventMachine->add_receiver(p_mediatorObj.get());


        // ----------------------- Initialize graphic Objects ----------------------

        // Draw Fps
        std::shared_ptr<mediator::ObserverCalcFps> drawFps (new graphics::DrawFps);
        p_mediatorObj->add_observer_calc_fps(drawFps);


        // ---------------------- Shaders -----------------------------------------

        // Initialize shader program
        GLuint shaderProgram = shader::Shaders().create_shader_program();

        // Initialize AVO
        GLuint VAO = shader::Shaders().create_VAO(vertices, indices);

        GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");

        // ----------------------- Texture ----------------------------------
        shader::Textures textures;

        // ---------------------- Main Loop ---------------------------------------

        float rotation = 0.0f;

        // Main Loop
        while(!glfwWindowShouldClose(glLib->get_window()))
        {
            // Start cycle time
            auto startCycleTime = std::chrono::high_resolution_clock::now();

            // Catch events
            glfwPollEvents();

            // Call step for engine
            engineObj.step();

            // Clear a buffer
            glClear(GL_COLOR_BUFFER_BIT);

            // Draw our first triangle
            glUseProgram(shaderProgram);

            rotation += 0.1;

            glm::mat4 trans;
            trans = glm::rotate(trans, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0));
            trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
            trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

            textures.set_active(shaderProgram, 0, "container.jpg", "ourTexture1");
            textures.set_active(shaderProgram, 1, "awesomeface.png", "ourTexture2");

//            glBindTexture(GL_TEXTURE_2D, texture);
            glBindVertexArray(VAO);

//            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glBindVertexArray(0);

            // Swap buffers
            glfwSwapBuffers(glLib->get_window());

            // Timeout to get no more than 60 fps
            std::this_thread::sleep_until(startCycleTime + std::chrono::microseconds(16667));
        }

    }
    catch(std::runtime_error & err)
    {
        std::cerr << "Runtime exception was caught : "  << err.what() << "\n";
    }
    catch(...)
    {
        std::cerr << "Any exception was caught\n";
    }

    return 0;


}
