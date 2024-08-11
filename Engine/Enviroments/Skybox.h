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

#ifndef SKYBOX_HEADER
#define SKYBOX_HEADER
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <string>

#include "../Dependancies/glm/glm.hpp"
#include "../Dependancies/glm/gtc/matrix_transform.hpp"
#include "../Dependancies/glm/gtc/type_ptr.hpp"
#include "../Dependancies/glm/gtx/rotate_vector.hpp"
#include "../Dependancies/glm/gtx/vector_angle.hpp"

#include "../Dependancies/glad/glad.h"
#include "../Dependancies/GLFW/glfw3.h"
#include "../Enviroments/Texture.h"

class Skybox
{
    public:
        std::string FaceCubemap[6] = {
            "../../Textures/Skybox/right.jpg",
            "../../Textures/Skybox/left.jpg",
            "../../Textures/Skybox/top.jpg",
            "../../Textures/Skybox/bottom.jpg",
            "../../Textures/Skybox/front.jpg",
            "../../Textures/Skybox/back.jpg"
        };

        unsigned int SkyboxVertexArrayObject;
        unsigned int SkyboxVertexBufferObject;
        unsigned int SkyboxVertexElementObject;
        unsigned int CubemapTexture;

        int WINDOW_WIDTH;
        int WINDOW_HEIGHT;
        float NEAR_VIEW;
        float FAR_VIEW;

        Skybox(int WindowWidth,int WindowHeight,float Near,float Far);
        void RenderSkybox(glm::vec3 Position,glm::vec3 Orientation,glm::vec3 UpPosition,Shader SkyboxShader);
};

#endif
