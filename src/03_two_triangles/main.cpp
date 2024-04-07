//
// Created by wj on 2024/4/7.
//
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <random>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

//������ɫ��Դ��
static const char * vertexShaderSource = "#version 330 core\n"
                                  "layout (location = 0) in vec3 aPos;\n"
                                  "void main()\n"
                                  "{\n"
                                  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                  "}\0";

//Ƭ����ɫ��Դ��
const char * fragmentShaderSource1 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\0";

//Ƭ����ɫ��Դ��
const char * fragmentShaderSource2 = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    FragColor = vec4(0.5f, 1.0f, 0.2f, 1.0f);\n"
                                     "}\0";

int main()
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

    //����ɫ��Դ�븽�ӵ���ɫ�������ϣ�Ȼ�������
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //����Ƿ����ɹ�
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Ƭ����ɫ��
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
    //��֮ǰ�������ɫ�����ӵ����������
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    //����
    glLinkProgram(shaderProgram1);

    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
    //������ɫ������
    glUseProgram(shaderProgram1);
    //ɾ����ɫ������
    glDeleteShader(fragmentShader1);

    shaderProgram2 = glCreateProgram();
    //��֮ǰ�������ɫ�����ӵ����������
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    //����
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
    //������ɫ������
    glUseProgram(shaderProgram2);
    //ɾ����ɫ������
    glDeleteShader(fragmentShader2);

    glDeleteShader(vertexShader);

    //��Ⱦѭ��
    //glfwWindowShouldClose �ж�glfw�Ƿ�Ҫ���˳����Ƿ���true
    while(!glfwWindowShouldClose(window))
    {
        //����
        processInput(window);

        //��Ⱦָ��
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

        //glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ�
        //glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(2, VAOS);
    glDeleteBuffers(2, VBOS);
    glDeleteProgram(shaderProgram1);
    glDeleteProgram(shaderProgram2);

    //�ر�glfw��������Դ
    glfwTerminate();
    return 0;
}