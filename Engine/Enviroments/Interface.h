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