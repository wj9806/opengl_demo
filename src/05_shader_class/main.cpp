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
    // ��ȡ��ǰ��ִ���ļ�����Ŀ¼��·��
    std::string exePath = __FILE__;
    size_t lastSlash = exePath.find_last_of('/');
    size_t lastBackslash = exePath.find_last_of('\\');

    // ���ݲ���ϵͳѡ��·���ָ���
#if defined(_WIN32)
    const char separator = '\\';
    size_t lastSeparator = lastBackslash;
#else
    const char separator = '/';
    size_t lastSeparator = lastSlash;
#endif

    std::string basePath = exePath.substr(0, lastSeparator + 1);

    // �����ļ�·��������
    std::string filePath = basePath + fileName;

    // ���ַ���ת��Ϊchar*���Ͳ�����
    char* result = new char[filePath.length() + 1];
    std::strcpy(result, filePath.c_str());
    return result;
}


int main()
{
    glfwInit();

    //������Ҫ��Ҫ�汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window window(800, 600);

    Shader shader(getFilePath("vertex.vs"), getFilePath("fragment.fs"));

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

        //glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ�
        //glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩
        glfwPollEvents();
        window.fwSwapBuffers();
    }
    return 0;
}
