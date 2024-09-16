#pragma once
#include "Model.h"

class Collision
{
    public:

    
    bool CheckCollision(const model& model1, const model& model2) {
        bool CollisionX = model1.PlayerPos.x + model1.BoundingBox.MinPos.x >= model2.PlayerPos.x
                        && model2.PlayerPos.x + model2.PlayerScale.x >= model1.PlayerPos.x;

        bool CollisionZ = model1.PlayerPos.z + model1.PlayerScale.z >= model2.PlayerPos.z
                        && model2.PlayerPos.z + model2.PlayerScale.z >= model1.PlayerPos.z;

        bool CollisionY = model1.PlayerPos.y + model1.PlayerScale.y >= model2.PlayerPos.y
                        && model2.PlayerPos.y + model2.PlayerScale.y >= model1.PlayerPos.y;

        return CollisionX && CollisionZ && CollisionY;
    }

    void CollisionCheck(std::vector<model*> AllModels, glm::vec3& Speed)
    {
        
        for (int i = 0; i < AllModels.size() -1; i++)
        {
            for (int j = i +1; j < AllModels.size(); j++)
            if (aabb::AABBIntersect(AllModels[i]->BoundingBox,AllModels[j]->BoundingBox))
            {
                std::cout << "hello felix is a massive bitch with big a" << std::endl;
                Speed *=  glm::vec3(-1.f);
            }
           
        }
    }

    
    
};