//
// Created by wj on 2024/4/8.
//


#include "windows.h"
#include "window.h"
#include <iostream>
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, 800, 600);
}

Window::Window(int width, int height)
{
    this->window = glfwCreateWindow(width, height, "opengl-demo", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    //�����ӿ�
    //glViewport����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ���
    glViewport(0, 0, width, height);

    //ע��ص����������ڱ仯������
    fwSetFramebufferSizeCallback(framebuffer_size_callback);
}

Window::~Window()
{
    glfwTerminate();
}

static std::string calculateFrameRate() {
    static float framesPerSecond = 0.0f;       // This will store our fps
    static float lastTime = 0.0f;       // This will hold the time from the last frame
    float currentTime = GetTickCount() * 0.001f;
    ++framesPerSecond;
    static int temp = 0;
    if (currentTime - lastTime > 1.0f) {
        lastTime = currentTime;
        temp = int(framesPerSecond);
        framesPerSecond = 0;
    }
    return "opengl-demo fps: " + std::to_string(temp);
}

void Window::fwSwapBuffers()
{
    glfwSwapBuffers(window);
    setWindowTitle(calculateFrameRate().data());
}

void Window::fwPollEvents()
{
    glfwPollEvents();
}

GLFWframebuffersizefun Window::fwSetFramebufferSizeCallback(GLFWframebuffersizefun callback)
{
    return glfwSetFramebufferSizeCallback(window, callback);
}

GLFWwindow* Window::getWindow()
{
    return window;
}


void Window::processInput()
{
    //�ж��Ƿ���esc
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int Window::fwWindowShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::setWindowTitle(char * title)
{
    glfwSetWindowTitle(window, title);
}