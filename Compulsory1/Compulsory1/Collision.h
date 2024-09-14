#pragma once
#include "Model.h"

class Collision
{
    public:

    
    bool CheckCollision(model& model1, model& model2)
    {
        bool CollisionX = model1.PlayerPos.x >= model2.PlayerPos.x
        && model2.PlayerPos.x >= model1.PlayerPos.x;

        bool CollisionZ = model1.PlayerPos.z >= model2.PlayerPos.z
        && model2.PlayerPos.z >= model1.PlayerPos.z;

        bool CollisionY = model1.PlayerPos.y >=model2.PlayerPos.y
        && model2.PlayerPos.y >=model1.PlayerPos.y;
        
        return CollisionX && CollisionZ && CollisionY;
    }

    
    void CollisionCheck(model& SphereModel,std::vector<model*> AllModels, glm::vec3& Speed)
    {
        float Distance;
        for (model* element : AllModels)
        {
            Distance = glm::distance(SphereModel.PlayerPos, element->PlayerPos);
        
            if (Distance < 0.1f && Distance != 0.f)
            {
                //Her skal collision kalkulasjon skje, men har bare -1 for å se om collision skjer i det hele tatt
            std::cout<<"Collision has happend"<<'\n';
                Speed *=  glm::vec3(-1.f);
            }
        }
    }

    
    
};