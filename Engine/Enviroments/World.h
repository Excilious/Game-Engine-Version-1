/*
Copyright (C) 2023-2024 Excilious

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
