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


//--------------------Mesh.h--------------------//
//  Author: Excilious
//  Date: 05/04/24
//  Abstraction: Creation of new meshes with vertices.
//
//----------------------------------------------//

#ifndef MESH_HEADER
#define MESH_HEADER

#include <string>
#include "Buffers/VertexArray.h"
#include "Buffers/ElementBuffer.h"
#include "Camera.h"
#include "Texture.h"
#include <string.h>

class Mesh
{
    public:
        std::vector <Vertex> Vertices;
        std::vector <GLuint> Indices;
        std::vector <Texture> Textures;

        VertexArrayObject VertexArray;
        unsigned int Instances;

        Mesh(
            std::vector<Vertex>& Vertices,
            std::vector<GLuint>& Indices,
            std::vector<Texture>& Textures,
            unsigned int Instances = 1,
            std::vector<glm::mat4> InstanceMatrix = {}
        );
        void Draw(Shader& ShaderInstance,Camera& CameraInstance,glm::mat4 Matrix = glm::mat4(1.0f),glm::vec3 Translation = glm::vec3(0.0f,0.0f,0.0f),glm::quat Rotation = glm::quat(1.0f,0.0f,0.0f,0.0f),glm::vec3 Scale = glm::vec3(1.0f,1.0f,1.0f));
};

#endif
