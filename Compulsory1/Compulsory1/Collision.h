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

    
};