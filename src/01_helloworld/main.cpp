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
 * 创建opengl窗口
 * @return
 */
int main_01()
{
    glfwInit();

    //设置主要次要版本
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
    //设置视口
    //glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
    glViewport(0, 0, 800, 600);

    //注册回调函数（窗口变化监听）
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //渲染循环
    //glfwWindowShouldClose 判断glfw是否被要求退出，是返回true
    while(!glfwWindowShouldClose(window))
    {
        //输入
        processInput(window);

        //渲染指令
        glClearColor(get_f(), get_f(), get_f(), get_f());
        glClear(GL_COLOR_BUFFER_BIT);

        //glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）
        //glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲）
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    //关闭glfw，清理资源
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, 800, 600);
}

void processInput(GLFWwindow *window)
{
    //判断是否按下esc
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

float get_f()
{
    // 使用随机设备作为种子
    std::random_device rd;
    std::mt19937 gen(rd());
    // 创建一个分布对象，指定范围为[0, 1]之间的浮点数
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    // 生成随机浮点数
    return dis(gen);
}