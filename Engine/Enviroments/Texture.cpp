//------------------Texture.cpp------------------//
//  Author: Excilious
//  Date: 05/04/24
//  Abstraction: Texture script file using stbi
//
//----------------------------------------------//

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "Texture.h"

Texture::Texture(const char* Image,const char* TextureType,GLuint Slot)
{
    stbi_set_flip_vertically_on_load(true);
    Type = TextureType;
    int WidthImage,HeightImage,ColourNumberChannel;
    unsigned char* Bytes = stbi_load(Image,&WidthImage,&HeightImage,&ColourNumberChannel,0);

    glGenTextures(1,&TextureID);
    glActiveTexture(GL_TEXTURE0+Slot);
    Unit = Slot;
    glBindTexture(GL_TEXTURE_2D,TextureID);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    if (ColourNumberChannel == 4) {glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,WidthImage,HeightImage,0,GL_RGBA,GL_UNSIGNED_BYTE,Bytes);} 
    else if (ColourNumberChannel == 3) {glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,WidthImage,HeightImage,0,GL_RGB,GL_UNSIGNED_BYTE,Bytes);} 
    else if (ColourNumberChannel == 1) {glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,WidthImage,HeightImage,0,GL_RED,GL_UNSIGNED_BYTE,Bytes);} 
    else {throw std::invalid_argument("Cannot find texture type.");}

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(Bytes);

    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::TextureUnit(Shader& NewShader,const char* Uniform,GLuint Unit)
{
    GLuint TextureUnit = glGetUniformLocation(NewShader.Program,Uniform);
    NewShader.ActivateShader();
    glUniform1i(TextureUnit,Unit);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0+Unit);
    glBindTexture(GL_TEXTURE_2D,TextureID);
}

void Texture::Unbind()
{glBindTexture(GL_TEXTURE_2D,0);}

void Texture::Delete()
{glDeleteTextures(1,&TextureID);}

