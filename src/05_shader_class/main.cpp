//
// Created by wj on 2024/4/8.
//

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include <iostream>
#include "window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

char* getFilePath(const char* fileName) {
    // 获取当前可执行文件所在目录的路径
    std::string exePath = __FILE__;
    size_t lastSlash = exePath.find_last_of('/');
    size_t lastBackslash = exePath.find_last_of('\\');

    // 根据操作系统选择路径分隔符
#if defined(_WIN32)
    const char separator = '\\';
    size_t lastSeparator = lastBackslash;
#else
    const char separator = '/';
    size_t lastSeparator = lastSlash;
#endif

    std::string basePath = exePath.substr(0, lastSeparator + 1);

    // 构建文件路径并返回
    std::string filePath = basePath + fileName;

    // 将字符串转换为char*类型并返回
    char* result = new char[filePath.length() + 1];
    std::strcpy(result, filePath.c_str());
    return result;
}


int main()
{
    glfwInit();

    //设置主要次要版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window window(800, 600);

    Shader shader(getFilePath("vertex.vs"), getFilePath("fragment.fs"));

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

        //glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）
        //glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲）
        glfwPollEvents();
        window.fwSwapBuffers();
    }
    return 0;
}
