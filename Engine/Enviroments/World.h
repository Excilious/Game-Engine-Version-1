//------------------World.h------------------//
//  Author: Excilious
//  Date: 12/06/24
//  Abstraction: Header script containing values for World.cpp
//
//----------------------------------------------//

#ifndef WORLD_HEADER
#define WORLD_HEADER

#include <list>
#include <algorithm>
#include <cctype>
#include <map>
#include <string>
#include "../CoreDefine.h"

struct WorldVertex
{
    glm::vec3 Position;
    glm::vec3 Normals;
    glm::vec3 Colours;
    glm::vec2 TextureUV;
};

class World
{
    public:
        Shader NewShader;
        Shader LightShader;
        GLuint ElementBuffer;
        GLuint VertexBuffer;
        GLuint VertexArray;
        std::vector<float> Vertices = {};
        std::vector<unsigned int> Indices = {};
        std::vector<float> Size = {};
        std::vector<float> Position = {};

        World();
        void StartWorld();
        void Destroy();
        void RenderWorld(Camera& NewCamera);
    private:
        std::map<std::string,std::map<std::string,glm::vec4>> EntityMap {};
        int EntityCountPosition = 0;
        void ParseThroughContents(const char* NewFile);
        std::string RemoveSpaces(std::string SubString);
        std::string DestroyCharacters(std::string &InputString,char CharacterToDestroy);
    
};

#endif