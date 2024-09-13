#pragma once
#include "Model.h"

class Collision
{
    public:

    Collision();
    
    bool CheckCollision(model& model1, model& model2)
    {
        bool CollisionX = model1.PlayerPos.x >= model2.PlayerPos.x
        && model2.PlayerPos.x >= model1.PlayerPos.x;

        bool CollisionZ = model1.PlayerPos.z >= model2.PlayerPos.z
        && model2.PlayerPos.z >= model1.PlayerPos.z;

        return CollisionX && CollisionZ;
    }

    void CollisionCheck(model& SphereModel,std::vector<model*> AllModels)
    {
        float Distance;
        for (model* element : AllModels)
        {
            Distance = glm::distance(SphereModel.PlayerPos, element->PlayerPos);
        
            if (Distance < 0.1f)
            {
                //Her skal collision calkulasjonen skje, men har bare -1 for å se om collision skjer i det hele tatt
                //Speed *= glm::vec3(-1.f);
            }
        }
    }
};