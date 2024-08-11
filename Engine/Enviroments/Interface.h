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


#ifndef INTERFACE_HEADER
#define INTERFACE_HEADER

#include "../Dependancies/glad/glad.h"
#include "../Dependancies/GLFW/glfw3.h"
#include "../Dependancies/glm/glm.hpp"
#include "Camera.h"
#include <vector>

class Interface
{
    public:
        Shader Shader2D;

        Interface();
        void Frame(glm::vec3 Position,glm::vec4 Colour);
        void RenderFrame(Camera& NewCamera);
        void DestroyFrame();
    private:
        glm::vec3 InterfacePosition;
        glm::vec4 InterfaceColour;
        GLuint InterfaceVertexArray;
        GLuint InterfaceVertexBuffer;
        GLuint InterfaceElementBuffer;
};

#endif
