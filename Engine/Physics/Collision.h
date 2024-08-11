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

//-----------------Collision.h------------------//
//  Author: Excilious
//  Date: 23/06/24
//  Abstraction: Header for collision script.
//
//----------------------------------------------//

#ifndef COLLISION_HEADER
#define COLLISION_HEADER

#include <iostream>
#include <vector>
#include "../Dependancies/glad/glad.h"
#include "../Dependancies/GLFW/glfw3.h"
#include "../Dependancies/glm/glm.hpp"

class Collision
{
    public:
        Collision();
        glm::vec3 BoxMin;
        glm::vec3 BoxMax;

        void PrecalculateBoxBounds(glm::vec3 Position, glm::vec3 Scale);
        void ResortVertices(std::vector<float> Vertices);
        bool IsPointWithinTriangles(glm::vec3 Point,glm::vec3 Vertices0, glm::vec3 Vertices1, glm::vec3 Vertices2);
        bool CollisionFromPoint(glm::vec3 Point);
        bool CollisionFromBounds(glm::vec3 BoundMin,glm::vec3 BoundMax);
        bool IsLevelCollidingWithPlayer(std::vector<float> Vertices);
        float Dot(glm::vec3 VectorA,glm::vec3 VectorB);

    private:
        int Count = 0;
        int Pass = 0;
        std::vector<float> VerticesContainer = {};
};

#endif
