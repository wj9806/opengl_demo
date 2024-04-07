//
// Created by wj on 2024/4/3.
//

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <random>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

float get_f();

/**
 * ����opengl����
 * @return
 */
int main_01()
{
    glfwInit();

    //������Ҫ��Ҫ�汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "opengl-demo", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //�����ӿ�
    //glViewport����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ���
    glViewport(0, 0, 800, 600);

    //ע��ص����������ڱ仯������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //��Ⱦѭ��
    //glfwWindowShouldClose �ж�glfw�Ƿ�Ҫ���˳����Ƿ���true
    while(!glfwWindowShouldClose(window))
    {
        //����
        processInput(window);

        //��Ⱦָ��
        glClearColor(get_f(), get_f(), get_f(), get_f());
        glClear(GL_COLOR_BUFFER_BIT);

        //glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ�
        //glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    //�ر�glfw��������Դ
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, 800, 600);
}

void processInput(GLFWwindow *window)
{
    //�ж��Ƿ���esc
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

float get_f()
{
    // ʹ������豸��Ϊ����
    std::random_device rd;
    std::mt19937 gen(rd());
    // ����һ���ֲ�����ָ����ΧΪ[0, 1]֮��ĸ�����
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    // �������������
    return dis(gen);
}