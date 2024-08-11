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


#include "Interface.h"

std::vector<float> Vertices = {
    -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
    1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
    -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 
    1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};

std::vector<unsigned int> Indices = {
    0,1,2,2,1,3
};

Interface::Interface()
{};

void Interface::Frame(glm::vec3 Position,glm::vec4 Colour)
{
    InterfacePosition = Position;
    InterfaceColour = Colour;
    Shader NewShader;
    NewShader.CreateNewShader("../../Shaders/Instance2D.vert","../../Shaders/Instance2D.frag");
    Interface::Shader2D = NewShader;

    glGenVertexArrays(1,&InterfaceVertexArray);
    glGenBuffers(1,&InterfaceVertexBuffer);
    glGenBuffers(1,&InterfaceElementBuffer);
    glBindVertexArray(InterfaceVertexArray);

    glBindBuffer(GL_ARRAY_BUFFER,InterfaceVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,Vertices.size()*sizeof(float),Vertices.data(),GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,InterfaceElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,Indices.size()*sizeof(unsigned int),Indices.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
}

void Interface::RenderFrame(Camera& NewCamera)
{
    Shader2D.ActivateShader();
    glBindVertexArray(InterfaceVertexArray);
    glUniform3f(glGetUniformLocation(Shader2D.Program,"Position"),InterfacePosition.x,InterfacePosition.y,InterfacePosition.z);
    glUniform4f(glGetUniformLocation(Shader2D.Program,"Colour"),InterfaceColour.x,InterfaceColour.y,InterfaceColour.z,InterfaceColour.w);
    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
}

void Interface::DestroyFrame()
{
    glDeleteVertexArrays(1,&InterfaceVertexArray);
    glDeleteBuffers(1,&InterfaceVertexBuffer);
    Shader2D.DestroyShader();
}
