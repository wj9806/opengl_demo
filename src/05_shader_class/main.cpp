//
// Created by wj on 2024/4/8.
//

#include "glad/glad.h"
#include "Shader.h"
#include "window.h"
#include "tools.h"

int main05()
{
    envInit();
    Window window(800, 600);
    std::string exePath = __FILE__;
    Shader shader(getFilePath(exePath, "vertex.glsl"), getFilePath(exePath, "fragment.glsl"));

    float vertices[] = {
            // λ��              // ��ɫ
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //��VAO
    glBindVertexArray(VAO);
    //�󶨻���
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //���ö���λ������ָ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //���ö�����ɫ����ָ��
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    while(!window.fwWindowShouldClose())
    {
        //����
        window.processInput();

        //��Ⱦָ��
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        window.fwPollEvents();
        window.fwSwapBuffers();
    }
    return 0;
}
