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


//--------------------Mesh.cpp--------------------//
//  Author: Excilious
//  Date: 05/04/24
//  Abstraction: Creation of new meshes with vertices.
//
//----------------------------------------------//

#include "Mesh.h"
#include "../Dependancies/glm/gtx/string_cast.hpp"

Mesh::Mesh(std::vector<Vertex>& Vertices,std::vector<GLuint>& Indices,std::vector<Texture>& Textures,unsigned int Instances,std::vector<glm::mat4> InstanceMatrix)
{
    Mesh::Vertices = Vertices;
    Mesh::Indices = Indices;
    Mesh::Textures = Textures;
    Mesh::Instances = Instances;

    VertexArray.Bind();
    VertexBufferObject InstanceVertexBuffer(InstanceMatrix);
    VertexBufferObject VertexBuffer(Vertices);
    ElementBufferObject ElementBuffer(Indices);

    VertexArray.LinkAttribute(VertexBuffer,0,3,GL_FLOAT,sizeof(Vertex),(void*)0);
    VertexArray.LinkAttribute(VertexBuffer,1,3,GL_FLOAT,sizeof(Vertex),(void*)(3*sizeof(float)));
    VertexArray.LinkAttribute(VertexBuffer,2,3,GL_FLOAT,sizeof(Vertex),(void*)(6*sizeof(float)));
    VertexArray.LinkAttribute(VertexBuffer,3,2,GL_FLOAT,sizeof(Vertex),(void*)(9*sizeof(float)));
    if (Instances != 1)
    {
        InstanceVertexBuffer.Bind();
        VertexArray.LinkAttribute(InstanceVertexBuffer,4,4,GL_FLOAT,sizeof(glm::mat4),(void*)0);
        VertexArray.LinkAttribute(InstanceVertexBuffer,5,4,GL_FLOAT,sizeof(glm::mat4),(void*)(1*sizeof(glm::vec4)));
        VertexArray.LinkAttribute(InstanceVertexBuffer,6,4,GL_FLOAT,sizeof(glm::mat4),(void*)(2*sizeof(glm::vec4)));
        VertexArray.LinkAttribute(InstanceVertexBuffer,7,4,GL_FLOAT,sizeof(glm::mat4),(void*)(3*sizeof(glm::vec4)));

        glVertexAttribDivisor(4,1);
        glVertexAttribDivisor(5,1);
        glVertexAttribDivisor(6,1);
        glVertexAttribDivisor(7,1);
    }

    VertexArray.Unbind();
    VertexBuffer.Unbind();
    ElementBuffer.Unbind();
}

void Mesh::Draw(Shader& ShaderInstance,Camera& CameraInstance,glm::mat4 Matrix,glm::vec3 Translation,glm::quat Rotation,glm::vec3 Scale)
{
    ShaderInstance.ActivateShader();
    VertexArray.Bind();
    unsigned int NumberDiffuse = 0;
    unsigned int NumberSpecular = 0;

    for (unsigned int x = 0; x < Textures.size(); x++)
    {
        std::string Number;
        std::string Type = Textures[x].Type;
        
        if (Type == "diffuse")
        {Number = std::to_string(NumberDiffuse++);}
        else if (Type == "specular")
        {Number = std::to_string(NumberSpecular++);};

        Textures[x].TextureUnit(ShaderInstance,(Type+Number).c_str(),x);
        Textures[x].Bind();
    }

    glUniform3f(glGetUniformLocation(ShaderInstance.Program,"camPos"),CameraInstance.Position.x,CameraInstance.Position.y,CameraInstance.Position.z);
    CameraInstance.SetMatrix(ShaderInstance,"camMatrix");

    if (Instances == 1)
    {
        glm::mat4 NewTransformation = glm::mat4(1.0f);
        glm::mat4 NewRotation = glm::mat4(1.0f);
        glm::mat4 NewScale = glm::mat4(1.0f);

        NewTransformation = glm::translate(NewTransformation,Translation);
        NewRotation = glm::mat4_cast(Rotation);
        NewScale = glm::scale(NewScale,Scale);

        glUniformMatrix4fv(glGetUniformLocation(ShaderInstance.Program,"translation"),1,GL_FALSE,glm::value_ptr(NewTransformation));
        glUniformMatrix4fv(glGetUniformLocation(ShaderInstance.Program,"rotation"),1,GL_FALSE,glm::value_ptr(NewRotation));
        glUniformMatrix4fv(glGetUniformLocation(ShaderInstance.Program,"scale"),1,GL_FALSE,glm::value_ptr(NewScale));
        glUniformMatrix4fv(glGetUniformLocation(ShaderInstance.Program,"model"),1,GL_FALSE,glm::value_ptr(Matrix));

        glDrawElements(GL_TRIANGLES,Indices.size(),GL_UNSIGNED_INT,0);
    } else {
        glDrawElementsInstanced(GL_TRIANGLES,Indices.size(),GL_UNSIGNED_INT,0,Instances);
    }
}
