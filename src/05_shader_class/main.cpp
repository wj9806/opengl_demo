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
            // 位置              // 颜色
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //绑定VAO
    glBindVertexArray(VAO);
    //绑定缓冲
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //设置顶点位置属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //设置顶点颜色属性指针
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    while(!window.fwWindowShouldClose())
    {
        //输入
        window.processInput();

        //渲染指令
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
