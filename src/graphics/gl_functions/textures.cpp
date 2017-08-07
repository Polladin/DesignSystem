
#include "textures.h"


namespace shader{


GLuint Textures::get_texture(const char * textureName)
{
    // Find texture in list
    auto itToTextureName = std::find(textureNames.begin(), textureNames.end(), std::string(textureName));

    // Texture should be exist
    if ( itToTextureName == textureNames.end())
        throw std::runtime_error("Texture is not found!");

    return texturesId[itToTextureName - textureNames.begin()];
}


void Textures::set_active(GLuint shaderProgram, unsigned textureNum, const char * textureName, const char * shaderTextureName)
{
    // Check max texture num
    if (textureNum >= GL_MAX_TEXTURE_UNITS)
        throw std::runtime_error("Texture num larger than maximum!");

    // Active texture
    glActiveTexture(GL_TEXTURE0 + textureNum);

    // Bind texture
    glBindTexture(GL_TEXTURE_2D, get_texture(textureName));

    // Bind into shader
    glUniform1i(glGetUniformLocation(shaderProgram, shaderTextureName), textureNum);
}


void Textures::load_all()
{
    // Resize vector for all textures ID
    texturesId.resize(sizeof(textures_path)/sizeof(textures_path[0]));

    // Generate texture objects
    glGenTextures(texturesId.size(), texturesId.data());

    // Load textures
    for (size_t textureFileNum = 0; textureFileNum < texturesId.size(); ++textureFileNum)
    {
        std::string fullPath = std::string("../textures/") + textures_path[textureFileNum];
        load_texture(fullPath.c_str(), texturesId[textureFileNum]);
        textureNames.emplace_back(textures_path[textureFileNum]);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

}//namespace shader