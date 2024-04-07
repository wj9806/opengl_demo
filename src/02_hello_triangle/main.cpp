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

//������ɫ��Դ��
const char * vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                 "}\0";

//Ƭ����ɫ��Դ��
const char * fragmentShaderSource = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\0";

/**
 * ��������   ---->  ������ɫ��   ----> ͼԪװ��  ---->  ������ɫ��   ---->  ��դ��   ---->   �ü�   ---->  Ƭ����ɫ��   ----> ���Ժͻ��
 */
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

    //���嶥������
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

    //����VBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //��VAO
    glBindVertexArray(VAO);
    //�󶨻���
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //�󶨵�Ԫ�ػ������
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //�������
    /**
     * glBufferData��һ��ר���������û���������ݸ��Ƶ���ǰ�󶨻���ĺ�����
     * ���ĸ�����ָ��������ϣ���Կ���ι������������:
     *   GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
     *   GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ
     *   GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    //�������ǵ��������鵽һ�����������У���OpenGLʹ��
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //���������Ƶ�����
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //���ö�������ָ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    //������ɫ��
    unsigned int vertexShader, fragmentShader;
    int success;
    char infoLog[512];
    createShader(vertexShader, fragmentShader, success);

    //������ɫ������
    unsigned int shaderProgram = 0;
    shaderProgram = createAndLinkProgram(vertexShader, fragmentShader, success, infoLog, shaderProgram);

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
        //glDrawArrays(GL_LINE_LOOP, 0, 3);
        //glBindVertexArray(0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        //glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ�
        //glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    //�ر�glfw��������Դ
    glfwTerminate();
    return 0;
}


void
createShader(unsigned int &vertexShader, unsigned int &fragmentShader, int &success) {
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //����ɫ��Դ�븽�ӵ���ɫ�������ϣ�Ȼ�������
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //����Ƿ����ɹ�
    char infoLog[512];
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
}

unsigned int
createAndLinkProgram(unsigned int vertexShader, unsigned int fragmentShader, int &success, char *infoLog,
                      unsigned int shaderProgram) {
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
    return shaderProgram;
}
