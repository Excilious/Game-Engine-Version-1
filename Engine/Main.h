//--------------------Main.h--------------------//
//  Author: Excilious
//  Date: 02/04/24
//  Abstraction: Main header files for precompiled values.
//
//----------------------------------------------//

#define IMGUI_DEFINE_MATH_OPERATORS

#include <iostream>
#include <string>
#include "Dependancies/glad/glad.h"
#include "Dependancies/GLFW/glfw3.h"

#include "Anarchy/Player.h"
#include "Enviroments/Lighting.h"
#include "Enviroments/Skybox.h"
#include "Enviroments/World.h"
#include "Enviroments/Interface.h"

const bool DEBUG_MODE = false;

class Main
{
    public:
        int WINDOW_WIDTH = 1280;
        int WINDOW_HEIGHT = 720;
        
        const float NEAR_VIEW = 0.1f;
        const float FAR_VIEW = 100.0f;
        const float FIELD_OF_VIEW = 60.0f;

        double PreviousTime = 0.0;
        double CurrentTime = 0.0;
        double TimeDifference;
        double XPosition;
        double YPosition;
        unsigned int Counter = 0;
        unsigned int Samples = 8;

        std::string FramesPerSecond;

        Main();
        void Render(GLFWwindow* NewWindow);
        void Release(GLFWwindow* NewWindow);

    private:
        const int VERSION_MAJOR = 3;
        const int VERSION_MINOR = 3;
};

