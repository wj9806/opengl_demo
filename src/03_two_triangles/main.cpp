//
// Created by wj on 2024/4/7.
//
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <random>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

//顶点着色器源码
static const char * vertexShaderSource = "#version 330 core\n"
                                  "layout (location = 0) in vec3 aPos;\n"
                                  "void main()\n"
                                  "{\n"
                                  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                  "}\0";

//片段着色器源码
const char * fragmentShaderSource1 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\0";

//片段着色器源码
const char * fragmentShaderSource2 = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    FragColor = vec4(0.5f, 1.0f, 0.2f, 1.0f);\n"
                                     "}\0";

int main()
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

    float vertices2[] = {
            -0.5f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            0.0f,  0.0f, 0.0f,
            0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };

    unsigned int VBOS[2], VAOS[2];
    glGenVertexArrays(2, VAOS);
    glGenBuffers(2, VBOS);

    glBindVertexArray(VAOS[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOS[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindVertexArray(VAOS[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOS[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    unsigned int vertexShader, fragmentShader1, fragmentShader2;
    int success;
    char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //把着色器源码附加到着色器对象上，然后编译它
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //检测是否编译成功
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //片段着色器
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);

    glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram1, shaderProgram2;

    shaderProgram1 = glCreateProgram();
    //把之前编译的着色器附加到程序对象上
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    //链接
    glLinkProgram(shaderProgram1);

    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
    //激活着色器程序
    glUseProgram(shaderProgram1);
    //删除着色器对象
    glDeleteShader(fragmentShader1);

    shaderProgram2 = glCreateProgram();
    //把之前编译的着色器附加到程序对象上
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    //链接
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
    //激活着色器程序
    glUseProgram(shaderProgram2);
    //删除着色器对象
    glDeleteShader(fragmentShader2);

    glDeleteShader(vertexShader);

    //渲染循环
    //glfwWindowShouldClose 判断glfw是否被要求退出，是返回true
    while(!glfwWindowShouldClose(window))
    {
        //输入
        processInput(window);

        //渲染指令
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram1);
        glBindVertexArray(VAOS[0]);
        glDrawArrays(GL_LINE_LOOP, 0, 3);
        glBindVertexArray(0);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOS[1]);
        glDrawArrays(GL_LINE_LOOP, 0, 3);
        glBindVertexArray(0);

        //glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）
        //glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲）
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(2, VAOS);
    glDeleteBuffers(2, VBOS);
    glDeleteProgram(shaderProgram1);
    glDeleteProgram(shaderProgram2);

    //关闭glfw，清理资源
    glfwTerminate();
    return 0;
}