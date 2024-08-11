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


#ifndef LIGHTING_HEADER
#define LIGHTING_HEADER

#include "../CoreDefine.h"

class Lighting
{
    public:
        glm::vec3 LightPosition;
        glm::vec3 LightScale;
        glm::vec4 LightColour;

        Lighting();
        void CreateLightBlock(glm::vec3 Scale, glm::vec3 Position, glm::vec4 Colour);
        void RenderLightBlock(Camera& NewCamera,World& NewWorld);

    private:
        Shader NewLightShader;

        GLuint LightVertexArray;
        GLuint LightElementBuffer;
        GLuint LightVertexBuffer;
};

#endif
