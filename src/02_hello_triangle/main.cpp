//
// Created by wj on 2024/4/3.
//

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <random>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

unsigned int
createAndLinkProgram(unsigned int vertexShader, unsigned int fragmentShader, int &success, char *infoLog,
                      unsigned int shaderProgram);

void
createShader(unsigned int &vertexShader, unsigned int &fragmentShader, int &success);

//顶点着色器源码
const char * vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                 "}\0";

//片段着色器源码
const char * fragmentShaderSource = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\0";

/**
 * 顶点数组   ---->  顶点着色器   ----> 图元装配  ---->  几何着色器   ---->  光栅化   ---->   裁剪   ---->  片段着色器   ----> 测试和混合
 */
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

    //定义顶点数组
//    float vertices[] = {
//            -0.5f, -0.5f, 0.0f,
//            0.5f, -0.5f, 0.0f,
//            0.0f,  0.5f, 0.0f
//    };

    float vertices2[] = {
            -0.5f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };
    unsigned int indices[] = {
            0,1,2,
            2,3, 4
    };

    //创建VBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //绑定VAO
    glBindVertexArray(VAO);
    //绑定缓冲
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //绑定到元素缓冲对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //填充数据
    /**
     * glBufferData是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数。
     * 第四个参数指定了我们希望显卡如何管理给定的数据:
     *   GL_STATIC_DRAW ：数据不会或几乎不会改变。
     *   GL_DYNAMIC_DRAW：数据会被改变很多。
     *   GL_STREAM_DRAW ：数据每次绘制时都会改变。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    //复制我们的索引数组到一个索引缓冲中，供OpenGL使用
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //把索引复制到缓冲
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    //创建着色器
    unsigned int vertexShader, fragmentShader;
    int success;
    char infoLog[512];
    createShader(vertexShader, fragmentShader, success);

    //创建着色器程序
    unsigned int shaderProgram = 0;
    shaderProgram = createAndLinkProgram(vertexShader, fragmentShader, success, infoLog, shaderProgram);

    //渲染循环
    //glfwWindowShouldClose 判断glfw是否被要求退出，是返回true
    while(!glfwWindowShouldClose(window))
    {
        //输入
        processInput(window);

        //渲染指令
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_LINE_LOOP, 0, 3);
        //glBindVertexArray(0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        //glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）
        //glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲）
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    //关闭glfw，清理资源
    glfwTerminate();
    return 0;
}


void
createShader(unsigned int &vertexShader, unsigned int &fragmentShader, int &success) {
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //把着色器源码附加到着色器对象上，然后编译它
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //检测是否编译成功
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //片段着色器
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

unsigned int
createAndLinkProgram(unsigned int vertexShader, unsigned int fragmentShader, int &success, char *infoLog,
                      unsigned int shaderProgram) {
    shaderProgram = glCreateProgram();
    //把之前编译的着色器附加到程序对象上
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //链接
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
    //激活着色器程序
    glUseProgram(shaderProgram);
    //删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}
