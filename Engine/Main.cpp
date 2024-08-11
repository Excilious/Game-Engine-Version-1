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


//--------------------Main.cpp------------------//
//  Author: Excilious
//  Date: 02/04/24
//  Abstraction: Main file to run the engine.
//
//----------------------------------------------//

#define STB_IMAGE_IMPLEMENTATION
#include "Main.h"
#include <math.h>

Main::Main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,VERSION_MINOR);
    glfwWindowHint(GLFW_SAMPLES,Samples);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* NewWindow;
    //glfwGetPrimaryMonitor()
    NewWindow = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Flippin Ibiscus",NULL,NULL);
    glfwMakeContextCurrent(NewWindow);
    gladLoadGL();
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

    if (NewWindow == NULL)
    {
        std::cout << "Failed to open GLFW window"<<"\n";
        glfwTerminate();
    }   
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      std::cout << "Failed to load GLAD" << "\n"; 
      glfwTerminate();
    }

    Main::Render(NewWindow);
 
    glfwDestroyWindow(NewWindow);
    glfwTerminate();
}

void Main::Release(GLFWwindow* NewWindow)
{
    if (glfwGetKey(NewWindow,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwTerminate();
        exit(0);
    }
}

void Main::Render(GLFWwindow* NewWindow)
{
    Shader ShaderProgram;
    Shader SkyboxShader;

    ShaderProgram.CreateNewShader("../../Shaders/Instance.vert","../../Shaders/Instance.frag");
    SkyboxShader.CreateNewShader("../../Shaders/Skybox.vert","../../Shaders/Skybox.frag");

    glm::vec4 LightColour = glm::vec4(1.0f,0.0f,0.0f,1.0f);
    glm::vec3 LightPosition = glm::vec3(-1.6f,-1.6f,-1.6f);
    glm::vec3 LightScale = glm::vec3(2.0f,2.0f,2.0f);

    glm::vec3 InterfacePosition = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec4 InterfaceColour = glm::vec4(0.2f,0.4f,0.3f,1.0f);

    Player NewPlayer;
    World NewWorld;
    Lighting NewLight;
    Camera NewCamera(WINDOW_WIDTH,WINDOW_HEIGHT,glm::vec3(0.0f,0.0f,0.0f));
    Skybox NewSkybox(WINDOW_WIDTH,WINDOW_HEIGHT,NEAR_VIEW,FAR_VIEW);
    Model NewModel("../../Meshes/scene.gltf",glm::quat(0.0f,0.0f,0.0f,0.0f),glm::vec3(1,1,1),glm::vec3(0,0,0),1);

    NewLight.CreateLightBlock(LightScale,LightPosition,LightColour);
    glUniform1i(glGetUniformLocation(SkyboxShader.Program,"skybox"),0);
    ShaderProgram.ActivateShader();
    SkyboxShader.ActivateShader();

    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);
    glFrontFace(GL_CCW);
    NewWorld.StartWorld();

    while (!glfwWindowShouldClose(NewWindow))
    {
        glfwPollEvents();
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        NewCamera.Inputs(NewWindow);
        NewCamera.UpdateMatrix(FIELD_OF_VIEW,NEAR_VIEW,FAR_VIEW);
        NewCamera.UpdateCameraPosition(NewWindow,XPosition,YPosition);

        NewSkybox.RenderSkybox(NewCamera.Position,NewCamera.Orientation,NewCamera.UpPosition,SkyboxShader);
        NewPlayer.Render(NewCamera,NewWorld);
        NewWorld.RenderWorld(NewCamera);
        NewLight.RenderLightBlock(NewCamera,NewWorld);
        NewModel.Draw(ShaderProgram,NewCamera);

        Release(NewWindow);
        glfwGetCursorPos(NewWindow,&XPosition,&YPosition);
        glfwSwapBuffers(NewWindow);
    }

    NewWorld.Destroy();
    SkyboxShader.DestroyShader();
    ShaderProgram.DestroyShader();
    glfwTerminate();
}

int main()
{Main Engine;}
