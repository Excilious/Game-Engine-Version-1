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

//-------------------Model.h--------------------//
//  Date: 06/04/24
//  Abstraction: Header file for the model script.
//
//----------------------------------------------//


#ifndef MODEL_HEADER
#define MODEL_HEADER

#include "jsonimport/json.h"
#include "Mesh.h"
#include <string.h>

using Json = nlohmann::json;

class Model
{
    public:
        Model(const char* NewFile,glm::quat Rotation,glm::vec3 Scale,glm::vec3 Position,unsigned int Instances = 1);
        void Draw(Shader& NewShader,Camera& NewCamera);
        glm::quat Rotation;
        glm::vec3 Scale;
        glm::vec3 Position;
        std::vector<glm::mat4> InstanceMatrix;
        
    private:
        const char* NewFile;
        std::vector<unsigned char> NewData;
        unsigned int Instances;
        Json JSON;

        std::vector<Mesh> NewMeshes;
        std::vector<glm::vec3> TranslationsMeshes;
        std::vector<glm::quat> RotationMeshes;
        std::vector<glm::vec3> ScaleMeshes;
        std::vector<glm::mat4> MatricesMeshes;
        
        std::vector<std::string> LoadedTextureName;
        std::vector<Texture> LoadedTexture;

        void LoadMesh(unsigned int IndicesMesh);
        void TraverseNode(unsigned int NextNode, glm::mat4 Matrix = glm::mat4(1.0f));
        
        std::vector<unsigned char> GetData();
        std::vector<float> GetFloats(Json Accessor);
        std::vector<GLuint> GetIndices(Json Accessor);
        std::vector<Texture> GetTextures();

        std::vector<Vertex> AssembleVertices
        (
            std::vector<glm::vec3> Position,
            std::vector<glm::vec3> Normal,
            std::vector<glm::vec2> TextureUV
        );
        
        std::vector<glm::mat4> GenerateInstanceMatrix(glm::quat Rotation,glm::vec3 Scale,glm::vec3 Position);
        std::vector<glm::vec2> FloatsGroupVec2(std::vector<float> FloatVector);
        std::vector<glm::vec3> FloatsGroupVec3(std::vector<float> FloatVector);
        std::vector<glm::vec4> FloatsGroupVec4(std::vector<float> FloatVector);

};

#endif
