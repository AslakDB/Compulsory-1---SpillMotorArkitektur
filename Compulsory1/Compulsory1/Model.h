//
// Created by askel on 4/8/2024.
//
#include <glad/glad.h>


#include <vector>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#ifndef MODEL_H
#define MODEL_H

class model
{
public:


unsigned int VBO, VAO, EBO;
    std::vector<Vertex> vertices;
    std::vector<Triangle> indices;
    bool isLine = false;


    glm::mat4 modelMatrix= glm::mat4(1.f);
    glm::vec3 PlayerPos = glm::vec3(0.f, 0.f,0.f);
    void Bind()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);


        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Triangle)* indices.size(), indices.data(), GL_STATIC_DRAW);


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);     glBindVertexArray(0);
    }
    void DrawMesh(unsigned int shaderProgram)
    {
        glUseProgram(shaderProgram);
        int modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBindVertexArray(VAO);

        if(isLine) {
            glDrawArrays(GL_LINES, 0, vertices.size());
            glBindVertexArray(0);

            return;
        }
        glDrawElements(GL_TRIANGLES, indices.size()* 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};
#endif //MODEL_H
