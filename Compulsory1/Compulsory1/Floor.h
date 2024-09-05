#pragma once
#include "Model.h"

    
   
    inline void CreateFloor(model& floorModel)
    { floorModel.vertices.emplace_back(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.f), glm::vec3(0.5f, 0.f, 0.6f));
        floorModel.vertices.emplace_back(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.f), glm::vec3(0.5f, 0.f, 0.6f));
        floorModel.vertices.emplace_back(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f), glm::vec3(0.5f, 0.f, 0.6f));
        floorModel.vertices.emplace_back(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.f), glm::vec3(0.5f, 0.f, 0.6f));

        floorModel.indices.emplace_back(0,1,3);
        floorModel.indices.emplace_back(1,2,3);
       // floorModel.indices.emplace_back(0,2,3);

        for (Triangle& index : floorModel.indices)
        {
            glm::vec3 normal = glm::cross(floorModel.vertices[index.B].XYZ - floorModel.vertices[index.A].XYZ, floorModel.vertices[index.C].XYZ - floorModel.vertices[index.A].XYZ);

            floorModel.vertices[index.A].Normals += glm::normalize(normal);
            floorModel.vertices[index.B].Normals += glm::normalize(normal);
            floorModel.vertices[index.C].Normals += glm::normalize(normal);
        }
        floorModel.Bind();
    }

