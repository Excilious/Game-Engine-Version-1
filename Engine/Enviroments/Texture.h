//-------------------Texture.h-------------------//
//  Author: Excilious
//  Date: 05/04/24
//  Abstraction: Header file for texture.
//
//----------------------------------------------//

#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include "../Dependancies/glad/glad.h"
#include "../Dependancies/stb/stb_image.h"
#include "Shader.h"

class Texture
{
    public: 
        GLuint TextureID;
        GLuint Unit;
        const char* Type;

        Texture(const char* Image,const char* TextureType,GLuint Slot);
        void TextureUnit(Shader& NewShader,const char* Uniform,GLuint Unit);
        void Bind();
        void Unbind();
        void Delete();
};

#endif 