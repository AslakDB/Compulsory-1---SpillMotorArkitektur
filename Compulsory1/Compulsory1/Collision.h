#pragma once
#include "Model.h"

class Collision
{
public:

    void SphereSphereCollision(std::vector<model*> sphere_models)
    {
        float radius = 0.5f;
        glm::vec3 ClampedNormal = glm::vec3(0.f);
        for (int i = 0; i < sphere_models.size()-1; i++)
        {
            for (int j = i +1; j < sphere_models.size(); j++)
                if (glm::distance(sphere_models[i]->PlayerPos , sphere_models[j]->PlayerPos) < radius + radius )
                {
                    ClampedNormal = sphere_models[i]->PlayerPos- sphere_models[j]->PlayerPos;
                    ClampedNormal = glm::normalize(ClampedNormal);
                    std::cout<<"BallCollision"<<'\n';
                    sphere_models[i]->Velocity = glm::reflect(sphere_models[i]->Velocity, ClampedNormal);
                    sphere_models[j]->Velocity = glm::reflect(sphere_models[j]->Velocity, ClampedNormal);
                }
        }
    }

    void SphereBoxCollision(std::vector<model*> sphere_models, std::vector<model*> other_models)
    {
        float radius = 0.5f;
        glm::vec3 ClampedNormal = glm::vec3(0.f);
        for (int i = 0; i < sphere_models.size(); i++)
        {
            for (int j = i ; j < other_models.size(); j++)
            {
                
                /* if (glm::distance(sphere_models[i]->PlayerPos ,other_models[i]->BoundingBox.MaxPos) < radius)
                 {
             ClampedNormal = sphere_models[i]->PlayerPos- sphere_models[j]->PlayerPos;
                     ClampedNormal = glm::normalize(ClampedNormal);
                     
                     sphere_models[i]->Velocity = glm::reflect(sphere_models[i]->Velocity, ClampedNormal);
                     std::cout<<"BallBoxCollision"<<'\n';
                     sphere_models[i]->Velocity *= glm::vec3(-1.f);*/
                    glm::vec3 closestPoint = glm::clamp(sphere_models[i]->PlayerPos, other_models[i]->BoundingBox.MinPos,other_models[i]->BoundingBox.MaxPos);
                    glm::vec3 Distance= sphere_models[i]->PlayerPos - closestPoint;
                if (Distance.length()- radius < 0.f)
                {
                    std::cout<<"BallBoxCollision"<<'\n';
                }
                
            }   
        }
    
    }
    
    
    void CollisionCheck(std::vector<model*> AllModels)
    {
        glm::vec3 ClampedNormal = glm::vec3(0.f);
        for (int i = 0; i < AllModels.size() -1; i++)
        {
            for (int j = i +1; j < AllModels.size(); j++)
            if (aabb::AABBIntersect(AllModels[i]->BoundingBox,AllModels[j]->BoundingBox))
            {
                ClampedNormal = glm::clamp(glm::vec3(0.f),AllModels[j]->PlayerPos, AllModels[i]->PlayerPos);
                ClampedNormal = glm::normalize(ClampedNormal);
                std::cout<<"Collision"<<'\n';
                AllModels[i]->PlayerPos = AllModels[i]->PlayerPos;
                AllModels[i]->Velocity = glm::reflect(AllModels[i]->Velocity, ClampedNormal);
            }
           
        }
    }

  
};