//
// Created by wj on 2024/4/3.
//

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <random>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

//������ɫ��Դ��
static const char *vertexShaderSource ="#version 330 core\n"
                                       "layout (location = 0) in vec3 aPos;\n"
                                       "layout (location = 1) in vec3 aColor;\n"
                                       "out vec3 ourColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   gl_Position = vec4(aPos, 1.0);\n"
                                       "   ourColor = aColor;\n"
                                       "}\0";

//Ƭ����ɫ��Դ��
static const char * fragmentShaderSource = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "in vec3 ourColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "    FragColor = vec4(ourColor, 1.0f);\n"
                                    "}\0";

/**
 * ��������   ---->  ������ɫ��   ----> ͼԪװ��  ---->  ������ɫ��   ---->  ��դ��   ---->   �ü�   ---->  Ƭ����ɫ��   ----> ���Ժͻ��
 */
int main04_2()
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

    float vertices[] = {
            // λ��              // ��ɫ
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
    };
    //����VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //��VAO
    glBindVertexArray(VAO);
    //�󶨻���
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //�������
    /**
     * glBufferData��һ��ר���������û���������ݸ��Ƶ���ǰ�󶨻���ĺ�����
     * ���ĸ�����ָ��������ϣ���Կ���ι������������:
     *   GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
     *   GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ
     *   GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //�������ǵ��������鵽һ�����������У���OpenGLʹ��

    //���ö���λ������ָ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //���ö�����ɫ����ָ��
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    //������ɫ��
    unsigned int vertexShader, fragmentShader;
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
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //������ɫ������
    unsigned int shaderProgram = 0;
    shaderProgram = glCreateProgram();
    //��֮ǰ�������ɫ�����ӵ����������
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //����
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
    //������ɫ������
    glUseProgram(shaderProgram);
    //ɾ����ɫ������
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //��Ⱦѭ��
    //glfwWindowShouldClose �ж�glfw�Ƿ�Ҫ���˳����Ƿ���true
    while(!glfwWindowShouldClose(window))
    {
        //����
        processInput(window);

        //��Ⱦָ��
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        //glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ�
        //glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    //�ر�glfw��������Դ
    glfwTerminate();
    return 0;
}

