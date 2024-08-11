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


//------------------Camera.cpp------------------//
//  Author: Excilious
//  Date: 02/04/24
//  Abstraction: Player view camera script.
//
//----------------------------------------------//

#include "Camera.h"

Camera::Camera(int WINDOW_WIDTH,int WINDOW_HEIGHT,glm::vec3 Position)
{
    Camera::Width = WINDOW_WIDTH;
    Camera::Height = WINDOW_HEIGHT;
    Position = Position;
}

void Camera::UpdateMatrix(float FieldOfView,float NearPlane,float FarPlane)
{
    ViewMatrix = glm::lookAt(Position,Position+Orientation,UpPosition);
    ProjectionMatrix = glm::perspective(glm::radians(FieldOfView),(float)(Width/Height),NearPlane,FarPlane);
    CameraMatrix = ProjectionMatrix * ViewMatrix;
}

void Camera::SetMatrix(Shader& ShaderInstance,const char* Uniform)
{glUniformMatrix4fv(glGetUniformLocation(ShaderInstance.Program,Uniform),1,GL_FALSE,glm::value_ptr(CameraMatrix));};

void Camera::MoveCamera(GLFWwindow* InputWindow)
{
    float RotationX;
    float RotationY;
    double MouseX;
    double MouseY;
    RotationX = Sensitivity * (float)(MouseY - (Height/2)) / Height;
    RotationY = Sensitivity * (float)(MouseX - (Width/2)) / Width;

    glm::vec3 NewOrientation = glm::rotate(Orientation,glm::radians(-RotationX),glm::normalize(glm::cross(Orientation,UpPosition)));

    if (!((glm::angle(NewOrientation,UpPosition) <= glm::radians(5.0f)) or (glm::angle(NewOrientation,-UpPosition) <= glm::radians(5.0f))))
    {Orientation = NewOrientation;}
    Orientation = glm::rotate(Orientation,glm::radians(-RotationY),UpPosition);
}

void Camera::UpdateCameraPosition(GLFWwindow* InputWindow,double XPosition,double YPosition)
{
    glfwSetInputMode(InputWindow,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    if (FirstMouse)
    {
        LastX = XPosition;
        LastY = YPosition;
        FirstMouse = false;
    }

    XOffset = XPosition - LastX;
    YOffset = LastY - YPosition;
    LastX = XPosition;
    LastY = YPosition;

    XOffset *= Sensitivity;
    YOffset *= Sensitivity;
    RotateX += XOffset;
    RotateY += YOffset;

    if (RotateY > 89.0f)
    {RotateY = 89.0f;}
    if (RotateY < -89.0f)
    {RotateY = -89.0f;}

    Orientation.x = cos(glm::radians(RotateX)) * cos(glm::radians(RotateY));
    Orientation.y = sin(glm::radians(RotateY));
    Orientation.z = sin(glm::radians(RotateX));
    Orientation = glm::normalize(Orientation);
}


void Camera::Inputs(GLFWwindow* InputWindow)
{
    if (glfwGetKey(InputWindow,GLFW_KEY_W) == GLFW_PRESS)
    {Position += Speed * Orientation;}
    if (glfwGetKey(InputWindow,GLFW_KEY_A) == GLFW_PRESS)
    {Position += Speed * -glm::normalize(glm::cross(Orientation,UpPosition));}
    if (glfwGetKey(InputWindow,GLFW_KEY_S) == GLFW_PRESS)
    {Position += Speed * -Orientation;}
    if (glfwGetKey(InputWindow,GLFW_KEY_D) == GLFW_PRESS)
    {Position += Speed * glm::normalize(glm::cross(Orientation,UpPosition));}
}
