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

//-------------------Shader.cpp------------------//
//  Author: Excilious
//  Date: 02/04/24
//  Abstraction: Reading and creating programs with given shaders.
//
//----------------------------------------------//

#include "Shader.h"

Shader::Shader()
{}

std::string GetShaderContents(const char* ShaderName)
{
    std::ifstream ShaderFile(ShaderName, std::ios::binary);
    if (ShaderFile.is_open())
    {
        std::string Contents;
        ShaderFile.seekg(0,std::ios::end);
        Contents.resize(ShaderFile.tellg());
        ShaderFile.seekg(0,std::ios::beg);
        ShaderFile.read(&Contents[0],Contents.size());
        ShaderFile.close();
        return (Contents);
    }
    return "";
}

void ReportErrors(unsigned int Shader,const char* Type)
{
    GLint HasCompiled;
    char InfoLog[1024];
    if (Type != "_P")
    {
        glGetShaderiv(Shader,GL_COMPILE_STATUS,&HasCompiled);
        if (HasCompiled == 0)
        {
            glGetShaderInfoLog(Shader,1024,NULL,InfoLog);
            std::cout << "Failed" << InfoLog << "\n";
        }
    } else {
        glGetProgramiv(Shader,GL_LINK_STATUS,&HasCompiled);
        if (HasCompiled == 0)
        {
            glGetProgramInfoLog(Shader,1024,NULL,InfoLog);
            std::cout << "Failed" << InfoLog << "\n";
        }
    }
}

void Shader::CreateNewShader(const char* VertexShaderFile,const char* FragmentShaderFile)
{
    std::string VertexText = GetShaderContents(VertexShaderFile);
    std::string FragmentText = GetShaderContents(FragmentShaderFile);

    const char* VertexSource = VertexText.c_str();
    const char* FragmentSource = FragmentText.c_str();

    GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(VertexShader,1,&VertexSource,NULL);
    glShaderSource(FragmentShader,1,&FragmentSource,NULL);

    glCompileShader(VertexShader);
    glCompileShader(FragmentShader);
    ReportErrors(VertexShader,"_V");
    ReportErrors(FragmentShader,"_F");

    Program = glCreateProgram();
    glAttachShader(Program,VertexShader);
    glAttachShader(Program,FragmentShader);
    glLinkProgram(Program);
    ReportErrors(Program,"_P");

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
}

void Shader::ActivateShader()
{glUseProgram(Program);};

void Shader::DestroyShader()
{glDeleteProgram(Program);};

