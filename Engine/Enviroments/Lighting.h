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