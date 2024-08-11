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

//-----------------Collision.cpp------------------//
//  Author: Excilious
//  Date: 23/06/24
//  Abstraction: Handles all world collisions.
//
//----------------------------------------------//

#include "Collision.h"
#include <math.h>

Collision::Collision()
{}

void Collision::PrecalculateBoxBounds(glm::vec3 Position, glm::vec3 Scale)
{
    BoxMax.x = Position.x + Scale.x/2;
    BoxMax.y = Position.y + Scale.y/2;
    BoxMax.z = Position.z + Scale.z/2;
    BoxMin.x = Position.x - Scale.x/2;
    BoxMin.y = Position.y - Scale.y/2;
    BoxMin.z = Position.z - Scale.z/2;
}

void Collision::ResortVertices(std::vector<float> Vertices)
{
    for (int x = 0; x < Vertices.size(); x++)
    {
        if (Count >= 3 && Pass >= 1)
        {
            std::cout << VerticesContainer.data()[0] << " " << VerticesContainer.data()[1] << " " << VerticesContainer.data()[2] << "\n";
            VerticesContainer = {};
            Count = 0;
            Pass = 0;
        }
        Pass++;
        Count++;
        VerticesContainer.push_back(Vertices.data()[x]);
    }
}

float Collision::Dot(glm::vec3 VectorA,glm::vec3 VectorB)
{return VectorA.x * VectorB.x + VectorA.y * VectorB.y + VectorA.z * VectorB.z;}

bool Collision::IsPointWithinTriangles(glm::vec3 Point,glm::vec3 Vertices0, glm::vec3 Vertices1, glm::vec3 Vertices2)
{
    glm::vec3 DistanceA = Vertices1-Vertices0;
    glm::vec3 DistanceB = Vertices2-Vertices0;
    glm::vec3 DistanceC = Point - Vertices0;

    float DotA = Dot(DistanceB,DistanceB);
    float DotB = Dot(DistanceB,DistanceA);
    float DotC = Dot(DistanceB,DistanceC);
    float DotD = Dot(DistanceA,DistanceA);
    float DotE = Dot(DistanceA,DistanceC);

    float Inverse = 1.0f/(DotA*DotD-DotB*DotB);
    float ProductA = (DotD*DotC-DotB*DotE)*Inverse;
    float ProductB = (DotA*DotE-DotB*DotC)*Inverse;
    return (ProductA >= 0) && (ProductB >= 0) && (ProductA + ProductB <= 1);
}

bool Collision::IsLevelCollidingWithPlayer(std::vector<float> Vertices)
{
    return false;
}

bool Collision::CollisionFromPoint(glm::vec3 Point)
{
    return (
        Point.x >= BoxMin.x &&
        Point.x <= BoxMax.x &&
        Point.y >= BoxMin.y &&
        Point.y <= BoxMax.y &&
        Point.z >= BoxMin.z &&
        Point.z <= BoxMax.z
    );
}

bool Collision::CollisionFromBounds(glm::vec3 BoundMin,glm::vec3 BoundMax)
{
    return (
        BoxMin.x <= BoundMax.x &&
        BoxMax.x >= BoundMin.x &&
        BoxMin.y <= BoundMax.y &&
        BoxMax.y >= BoundMin.y &&
        BoxMin.z <= BoundMax.z &&
        BoxMax.z >= BoundMin.z
    );
}
