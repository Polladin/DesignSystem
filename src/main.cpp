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

#include "SOIL.h"

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


        // ----------------------- Texture ----------------------------------
        GLuint texture;
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        int width, height;
        unsigned char* image = SOIL_load_image("/home/alex/Desktop/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(image);

        GLuint texture2;
        glGenTextures(1, &texture2);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

//        int width, height;
        unsigned char* image2 = SOIL_load_image("/home/alex/Desktop/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
        glGenerateMipmap(GL_TEXTURE_2D);


        glBindTexture(GL_TEXTURE_2D, 0);

        // ---------------------- Main Loop ---------------------------------------

        // Main Loop
        while(!glfwWindowShouldClose(glLib->get_window()))
        {
            // Startcycle time
            auto startCycleTime = std::chrono::high_resolution_clock::now();

            // Catch events
            glfwPollEvents();

            // Call step for engine
            engineObj.step();

            // Clear a buffer
            glClear(GL_COLOR_BUFFER_BIT);

            // Draw our first triangle
            glUseProgram(shaderProgram);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);
            glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 1);

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
