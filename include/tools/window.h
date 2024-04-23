//
// Created by wj on 2024/4/8.
//

#ifndef OPENGL_DEMO_WINDOW_H
#define OPENGL_DEMO_WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window{
private:
    GLFWwindow* window;
public:
    Window(int width, int height);

    ~Window();

    void fwSwapBuffers();

    void fwPollEvents();

    GLFWframebuffersizefun fwSetFramebufferSizeCallback(GLFWframebuffersizefun callback);

    GLFWwindow* getWindow();

    void processInput();

    int fwWindowShouldClose();

    void setWindowTitle(char * title);
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif //OPENGL_DEMO_WINDOW_H
