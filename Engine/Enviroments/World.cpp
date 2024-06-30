//------------------World.cpp------------------//
//  Author: Excilious
//  Date: 12/06/24
//  Abstraction: World script for world generation
//
//----------------------------------------------//

#include "World.h"

World::World()
{};

std::string World::DestroyCharacters(std::string &InputString,char CharacterToDestroy) 
{
   InputString.erase(std::remove(InputString.begin(), InputString.end(), CharacterToDestroy), InputString.end());
   return InputString;
}

std::string World::RemoveSpaces(std::string SubString)
{
    SubString.erase(remove(SubString.begin(),SubString.end(),' '),SubString.end());
    return SubString;
}

void World::ParseThroughContents(const char* NewFile)
{
    std::ifstream InputFileContents(NewFile,std::ios::binary);
    std::string String;

    while (std::getline(InputFileContents,String))
    {
        String = DestroyCharacters(String,' ');
        if (String.substr(0,1) == "#")
        {continue;}
        else if (String.substr(0,3) == "<v>")
        {
            String = DestroyCharacters(String,'v');
            String = DestroyCharacters(String,'<');
            String = DestroyCharacters(String,'>');
            std::stringstream NewString(String);
            while (NewString.good())
            {
                std::string SubString;
                std::getline(NewString,SubString,',');
                if (!SubString.empty() || !(SubString.length() == 0))
                {
                    std::cout << SubString << "\n";
                    Vertices.push_back(std::stof(SubString));
                }
            } 
        }
        else if (String.substr(0,3) == "<p>")
        {
            String = DestroyCharacters(String,'p');
            String = DestroyCharacters(String,'<');
            String = DestroyCharacters(String,'>');
            std::stringstream NewString(String);
            while (NewString.good())
            {
                std::string SubString;
                std::getline(NewString,SubString,',');
                Position.push_back(std::stof(SubString));
            }
        }
        else if (String.substr(0,3) == "<e>")
        {
            String = DestroyCharacters(String,'e');
            String = DestroyCharacters(String,'<');
            String = DestroyCharacters(String,'>');
            std::stringstream NewString(String);
            while (NewString.good())
            {
                std::string SubString;
                std::getline(NewString,SubString,',');
                std::cout << SubString << "\n";
            }
            std::cout << "Entity Found. Nothing has been done yet!" << "\n";     
        }
        else if (String.substr(0,3) == "<l>")
        {
            String = DestroyCharacters(String,'l');
            String = DestroyCharacters(String,'<');
            String = DestroyCharacters(String,'>');
            EntityCountPosition++;  
            EntityMap[std::to_string(EntityCountPosition)]["LightColour"] = glm::vec4(0.0f,0.0f,0.0f,0.0f);
            EntityMap[std::to_string(EntityCountPosition)]["LightPosition"] = glm::vec4(0.0f,0.0f,0.0f,0.0f);
            EntityMap[std::to_string(EntityCountPosition)]["LightScale"] = glm::vec4(0.0f,0.0f,0.0f,0.0f);

            std::stringstream NewString(String);
            while (NewString.good())
            {
                std::string SubString;
                std::getline(NewString,SubString,',');
            } 
        }
        else if (String.substr(0,3) == "<s>")
        {
            String = DestroyCharacters(String,'s');
            String = DestroyCharacters(String,'<');
            String = DestroyCharacters(String,'>');
            std::stringstream NewString(String);
            while (NewString.good())
            {
                std::string SubString;
                std::getline(NewString,SubString,',');
                Size.push_back(std::stof(SubString));
            }
        }
        else if (String.substr(0,3) == "<i>")
        {
            String = DestroyCharacters(String,'i');
            String = DestroyCharacters(String,'<');
            String = DestroyCharacters(String,'>');
            std::stringstream NewString(String);
            while (NewString.good())
            {
                std::string SubString;
                std::getline(NewString,SubString,',');
                Indices.push_back(std::stoi(SubString));
            }
        }
    }
    InputFileContents.close();
}

void World::StartWorld()
{
    //TODO - Add textures when ready!
    //TODO - try to make this efficent. There are too many buffers so far.

    Shader NewShaderProgram;
    NewShaderProgram.CreateNewShader("../../Shaders/World.vert","../../Shaders/World.frag");
    ParseThroughContents("../../Anarchy/Anarchy1.axz");
    World::NewShader = NewShaderProgram;

    glGenVertexArrays(1,&VertexArray);
    glGenBuffers(1,&VertexBuffer);
    glGenBuffers(1,&ElementBuffer);

    glBindVertexArray(VertexArray);

    glBindBuffer(GL_ARRAY_BUFFER,VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,Vertices.size()*sizeof(float),Vertices.data(),GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,Indices.size()*sizeof(unsigned int),Indices.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
}

void World::RenderWorld(Camera& NewCamera)
{
    NewShader.ActivateShader();
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 Translation = glm::mat4(1.0f);
    Model = glm::scale(Model,glm::vec3(Size.data()[0],Size.data()[1],Size.data()[2]));
    Translation = glm::translate(Translation,glm::vec3(Position.data()[0],Position.data()[1],Position.data()[2]));

    glUniformMatrix4fv(glGetUniformLocation(NewShader.Program,"matrix"),1,GL_FALSE,glm::value_ptr(Model));
    glUniformMatrix4fv(glGetUniformLocation(NewShader.Program,"projection"),1,GL_FALSE,glm::value_ptr(NewCamera.ProjectionMatrix));
    glUniformMatrix4fv(glGetUniformLocation(NewShader.Program,"view"),1,GL_FALSE,glm::value_ptr(NewCamera.ViewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(NewShader.Program,"translation"),1,GL_FALSE,glm::value_ptr(Translation));

    glBindVertexArray(VertexArray);
    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
}

void World::Destroy()
{
    glDeleteVertexArrays(1,&VertexArray);
    glDeleteBuffers(1,&VertexBuffer);
    NewShader.DestroyShader();
}
