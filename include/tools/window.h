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

    void fwSwapBuffers();

    GLFWwindow* getWindow();

    void processInput();

    int fwWindowShouldClose();
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif //OPENGL_DEMO_WINDOW_H
