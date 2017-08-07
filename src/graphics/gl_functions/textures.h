
#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

#include "SOIL.h"


#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

// GLEW need to include before GLFW.
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace shader{

const char * const textures_path[] =
{
      "container.jpg"
    , "awesomeface.png"
};


class Textures
{
public:

    Textures() { load_all(); }

    //
    GLuint get_texture(const char * textureName);

    //
    void set_active(GLuint shaderProgram, unsigned textureNum, const char * textureName, const char * shaderTextureName);

private:

    void load_all();

    void load_texture(const char * filePath, GLuint texId)
    {
        glBindTexture(GL_TEXTURE_2D, texId);

        int width, height;
        unsigned char* image = SOIL_load_image(filePath, &width, &height, 0, SOIL_LOAD_RGB);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        SOIL_free_image_data(image);
    }

public:

    std::vector<std::string> textureNames;

private:

    std::vector<GLuint> texturesId;

};


}//namespace shader