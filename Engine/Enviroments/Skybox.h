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