#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Model.h"
#include "Floor.h"
#include "Sphere.h"

Sphere sphere;

#ifndef RENDER_H
#define RENDER_H
Camera camera;
Floor floors;
bool firstMouse = true;

float lastX = 960, lastY = 540;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void ProsessInput(GLFWwindow *window, float deltaTime);



struct Render {
bool inside;
    bool isMovingForward;

    model floorModel;
    model SphereModel;
    model SphereModel2;

   // for (int in = 0; in < 5; i++)
    
        //Creating the walls for collision, Z and X stands for X and X axis, N and P stands for the positive and negative axis on Z and X.
    model ZWallP;
    model ZWallN;
    model XWallP;
    model XWallN;
    
    std::vector<model*> models;
    // model ThePlane;
    // model PlayerBox;
    // model NpcBox;



    void render(GLFWwindow* window, unsigned int shaderProgram, float deltaTime, float lastFrame) {

        
        models.emplace_back(&floorModel);
        
        models.emplace_back(&SphereModel);
        models.emplace_back(&SphereModel2);
        
        models.emplace_back(&ZWallP);
        models.emplace_back(&ZWallN);
        models.emplace_back(&XWallP);
        models.emplace_back(&XWallN);
        // models.emplace_back(&PlayerBox);
        // models.emplace_back(&NpcGraph);
        // models.emplace_back(&NpcBox);

        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 projection;

        // CreateMeshPlane(ThePlane, 20, 20);
        //
        //
        //
        //
        // CreateMeshBox(PlayerBox);
        // CreateMeshBox(NpcBox);

        
      floors.CreateFloor(floorModel);
       sphere.CreateSphere(SphereModel);
       sphere.CreateSphere(SphereModel2);

        floors.CreateFloor(ZWallP);
        floors.CreateFloor(ZWallN);
        floors.CreateFloor(XWallP);
        floors.CreateFloor(XWallN);


        floorModel.PlayerPos = glm::vec3(0,-1,0);
       
        ZWallN.PlayerPos= glm::vec3(0, -1, -4.5f);
        ZWallN.PlayerRadians = 90;
        ZWallN.PlayerRotation = glm::vec3(1,0,0);
        ZWallN.PlayerScale = glm::vec3(1,1,0.1f);
        
        ZWallP.PlayerPos= glm::vec3(0, -1, 4.5f);
        ZWallP.PlayerRadians = -90;
        ZWallP.PlayerRotation = glm::vec3(1,0,0);
        ZWallP.PlayerScale = glm::vec3(1,1,0.1f);
        
        XWallN.PlayerPos= glm::vec3(-4.5, -1, 0);
        XWallN.PlayerRadians = -90;
        XWallN.PlayerRotation = glm::vec3(0,0,1);
        XWallN.PlayerScale = glm::vec3(0.1f,1,1.f);
        
        XWallP.PlayerPos= glm::vec3(4.5, -1, 0);
        XWallP.PlayerRadians = 90;
        XWallP.PlayerRotation = glm::vec3(0,0,1);
        XWallP.PlayerScale = glm::vec3(0.1f,1,1.f);
        
        SphereModel.PlayerPos = glm::vec3(1,-1,1);

        

        // bool isMovingforward = true;
        //
        // float NpcXPos = 3.0f;
        // float NpcYPos = 0.0f;
        // float NpcZPos = f(NpcXPos);

        while (!glfwWindowShouldClose(window))
            {

           // sphere.Move(SphereModel, deltaTime, sphere.Speed);
            //sphere.Move(SphereModel2, deltaTime,sphere.Speed);
            
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            ProsessInput(window, deltaTime);

            projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

            camera.tick(shaderProgram);

            /*for (auto element: ThePlane.indices) {
                calculateBarycentric(ThePlane.vertices[element.A], ThePlane.vertices[element.B]
                    ,ThePlane.vertices[element.C], PlayerBox.PlayerPos );
            }
            PlayerBox.modelMatrix = glm::translate(glm::mat4(1.f), PlayerBox.PlayerPos);*/




            /*MoveNPC(NpcBox, glm::vec3(NpcXPos, NpcYPos, NpcZPos));
            if (NpcXPos > 8.25f)
            {
                isMovingForward = false;
            }
            if (NpcXPos < 2.0f)
            {
                isMovingForward = true;
            }

            if (isMovingForward)
            {
                NpcXPos += 1 * deltaTime;
                NpcZPos = f(NpcXPos);
            }
            else
            {
                NpcXPos -= 1 * deltaTime;
                NpcZPos = f(NpcXPos);
            }


            for (auto element: ThePlane.indices) {
                calculateBarycentric(ThePlane.vertices[element.A], ThePlane.vertices[element.B]
                    ,ThePlane.vertices[element.C], NpcBox.PlayerPos );
            }

            NpcBox.modelMatrix = glm::translate(glm::mat4(1.f), NpcBox.PlayerPos);*/
            glClearColor(0.5f, 0.99f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            int viewLoc = glGetUniformLocation(shaderProgram, "viewPos");
            glUniform3fv(viewLoc, 1, glm::value_ptr(camera.cameraPos));

            int LightLoc = glGetUniformLocation(shaderProgram, "lightPos");
            glUniform3fv(LightLoc, 1, glm::value_ptr(glm::vec3(0,20,0)));

            glLineWidth(3);
            
            for (model* element : models)
            {
                element->CalcualteMatrix();
            }
            
            for (model* element: models) {
                element->DrawMesh(shaderProgram);
            }

            
            glfwSwapBuffers(window);
            glfwPollEvents();
            }
    }
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.yaw   += xoffset;
    camera.pitch += yoffset;

    if(camera.pitch > 89.0f)
        camera.pitch = 89.0f;
    if(camera.pitch < -89.0f)
        camera.pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    direction.y = sin(glm::radians(camera.pitch));
    direction.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    camera.cameraFront = glm::normalize(direction);
}


void ProsessInput(GLFWwindow *window, float deltaTime) {

    glm::vec3 cameraFrontXZ = glm::normalize(glm::vec3(camera.cameraFront.x, 0.0f, camera.cameraFront.z));

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5f * deltaTime ;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.cameraPos += cameraSpeed * cameraFrontXZ;
        /*Player.PlayerPos +=  cameraSpeed * cameraFrontXZ;*/}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
       { camera.cameraPos -= cameraSpeed * cameraFrontXZ;
        /*Player.PlayerPos -=  cameraSpeed * cameraFrontXZ;*/}
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        camera.cameraPos -= glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;
    /*Player.PlayerPos -=  glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;*/}
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        camera.cameraPos += glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;
    /*Player.PlayerPos +=  glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;*/}
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.cameraPos += cameraSpeed * camera.cameraUp; // Move camera up
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.cameraPos -= cameraSpeed * camera.cameraUp;

    if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        sphere.Speed = sphere.Speed * glm::vec3(-0.8f);
    /*if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        Player.PlayerPos +=  glm::vec3(0,0,-1.f* deltaTime);
    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)

    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        Player.PlayerPos +=  glm::vec3(0,0,1.f* deltaTime);*/

}
#endif //RENDER_H
