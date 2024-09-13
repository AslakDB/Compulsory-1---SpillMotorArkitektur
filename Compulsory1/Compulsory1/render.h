#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Model.h"
#include "Floor.h"
#include "Sphere.h"
#include "Collision.h"

Sphere sphere;
Collision coll;

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
  //  model SphereModel2;

   // for (int in = 0; in < 5; i++)
    
        //Creating the walls for collision, Z and X stands for X and X axis, N and P stands for the positive and negative axis on Z and X.
    model ZWallP;
    model ZWallN;
    model XWallP;
    model XWallN;
    
    std::vector<model*> models;



    void render(GLFWwindow* window, unsigned int shaderProgram, float deltaTime, float lastFrame) {

        
        models.emplace_back(&floorModel);
        
        models.emplace_back(&SphereModel);
        //models.emplace_back(&SphereModel2);
        
        models.emplace_back(&ZWallP);
        models.emplace_back(&ZWallN);
        models.emplace_back(&XWallP);
        models.emplace_back(&XWallN);
       

        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 projection;
        
      floors.CreateFloor(floorModel);
       sphere.CreateSphere(SphereModel);
     //  sphere.CreateSphere(SphereModel2);

        floors.CreateFloor(ZWallP);
        floors.CreateFloor(ZWallN);
        floors.CreateFloor(XWallP);
        floors.CreateFloor(XWallN);


        floorModel.PlayerPos = glm::vec3(0.f,0.f,0.f);
       
        ZWallN.PlayerPos= glm::vec3(0.f, 0, -4.5f);
        ZWallN.PlayerRotation = glm::vec3(90.f,0.f,0.f);
        ZWallN.PlayerScale = glm::vec3(1.f,1.f,0.1f);
        
        ZWallP.PlayerPos= glm::vec3(0.f, 0.f, 4.5f);
        ZWallP.PlayerRotation = glm::vec3(-90.f,0.f,0.f);
        ZWallP.PlayerScale = glm::vec3(1.f,1.f,0.1f);
        
        XWallN.PlayerPos= glm::vec3(-4.5f, 0.f, 0.f);
        XWallN.PlayerRotation = glm::vec3(0.f,0.f,-90.f);
        XWallN.PlayerScale = glm::vec3(0.1f,1.f,1.f);
        
        XWallP.PlayerPos= glm::vec3(4.5f, 0.f, 0.f);
        XWallP.PlayerRotation = glm::vec3(0.f,0.f,90.f);
        XWallP.PlayerScale = glm::vec3(0.1f,1.f,1.f);

        
      
        srand(time(NULL));  sphere.Speed.z  = 2;
        while (!glfwWindowShouldClose(window))
            {

            
          
           sphere.Move(SphereModel, deltaTime, sphere.Speed);
            //sphere.Move(SphereModel2, deltaTime,sphere.Speed);
            
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            ProsessInput(window, deltaTime);

            projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

            camera.tick(shaderProgram);

         
            glClearColor(0.5f, 0.99f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            int viewLoc = glGetUniformLocation(shaderProgram, "viewPos");
            glUniform3fv(viewLoc, 1, glm::value_ptr(camera.cameraPos));

            int LightLoc = glGetUniformLocation(shaderProgram, "lightPos");
            glUniform3fv(LightLoc, 1, glm::value_ptr(glm::vec3(0,10,0)));

            glLineWidth(3);
            
            for (model* element : models)
            {
                element->CalcualteMatrix();
            }
            
            for (model* element: models) {
                element->DrawMesh(shaderProgram);
            }


           for (model* element : models)
           {
               if (coll.CheckCollision(SphereModel, element));
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


}
#endif //RENDER_H
