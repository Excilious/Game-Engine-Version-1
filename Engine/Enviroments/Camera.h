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


//------------------Camera.h------------------//
//  Author: Excilious
//  Date: 02/04/24
//  Abstraction: Header file for the camera player view.
//
//----------------------------------------------//

#ifndef CAMERA_HEADER
#define CAMERA_HEADER
#define GLM_ENABLE_EXPERIMENTAL

#include "../Dependancies/glad/glad.h"
#include "../Dependancies/GLFW/glfw3.h"
#include "../Dependancies/glm/glm.hpp"
#include "../Dependancies/glm/gtc/matrix_transform.hpp"
#include "../Dependancies/glm/gtc/type_ptr.hpp"
#include "../Dependancies/glm/gtx/rotate_vector.hpp"
#include "../Dependancies/glm/gtx/vector_angle.hpp"

#include "Shader.h"

class Camera
{
    public:
        glm::vec3 Position = glm::vec3(0.0f,0.0f,0.0f);
        glm::vec3 UpPosition = glm::vec3(0.0f,1.0f,0.0f);
        glm::vec3 Orientation = glm::vec3(0.0f,0.0f,-1.0f);
        glm::mat4 CameraMatrix = glm::mat4(1.0f);

        glm::mat4 ViewMatrix = glm::mat4(1.0f);
        glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

        float LastX = 0;
        float LastY = 0;
        float RotateX = 0;
        float RotateY = 0;
        float XOffset = 0;
        float YOffset = 0;
        bool FirstMouse = true;

        int Width;
        int Height;
        float Speed = 0.04f;
        float Sensitivity = 0.1f;
        float JumpMultiplier = 1.5f;
        bool MouseCursorLocked = false;

        Camera(int WINDOW_WIDTH,int WINDOW_HEIGHT,glm::vec3 Position);
        void UpdateMatrix(float FieldOfView,float NearPlane,float FarPlane);
        void SetMatrix(Shader& ShaderInstance,const char* Uniform);
        void MoveCamera(GLFWwindow* InputWindow);
        void Inputs(GLFWwindow* InputWindow);
        void UpdateCameraPosition(GLFWwindow* InputWindow,double XPosition,double YPosition);
};

#endif
