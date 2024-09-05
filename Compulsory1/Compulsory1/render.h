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
    model roofModel;
    std::vector<model*> models;
    // model ThePlane;
    // model PlayerBox;
    // model NpcBox;



    void render(GLFWwindow* window, unsigned int shaderProgram, float deltaTime, float lastFrame) {

        models.emplace_back(&floorModel);
        models.emplace_back(&roofModel);
        models.emplace_back(&SphereModel);
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
        floors.CreateFloor(roofModel);

        roofModel.PlayerPos = glm::vec3(2.f,5.f,0.f);
        SphereModel.PlayerPos = glm::vec3(0.f);

        

        // bool isMovingforward = true;
        //
        // float NpcXPos = 3.0f;
        // float NpcYPos = 0.0f;
        // float NpcZPos = f(NpcXPos);

        while (!glfwWindowShouldClose(window))
            {

            std::cout<<camera.yaw<< '\n';
            
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
            glUniform3fv(LightLoc, 1, glm::value_ptr(glm::vec3(5,20,0)));

            glLineWidth(3);
            

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

    /*if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        Player.PlayerPos +=  glm::vec3(1.f* deltaTime,0,0);
    if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        Player.PlayerPos +=  glm::vec3(0,0,-1.f* deltaTime);
    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)

    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        Player.PlayerPos +=  glm::vec3(0,0,1.f* deltaTime);*/

}
#endif //RENDER_H
