//
// Created by wj on 2024/4/9.
//

#include "tools.h"
#include <string>
#include "GLFW/glfw3.h"

char* getFilePath(std::string& exePath, const char* fileName)
{
    size_t lastSlash = exePath.find_last_of('/');
    size_t lastBackslash = exePath.find_last_of('\\');

    // 根据操作系统选择路径分隔符
#if defined(_WIN32)
    const char separator = '\\';
    size_t lastSeparator = lastBackslash;
#else
    const char separator = '/';
    size_t lastSeparator = lastSlash;
#endif

    std::string basePath = exePath.substr(0, lastSeparator + 1);

    // 构建文件路径并返回
    std::string filePath = basePath + fileName;

    // 将字符串转换为char*类型并返回
    char* result = new char[filePath.length() + 1];
    std::strcpy(result, filePath.c_str());
    return result;
}

void envInit()
{
    glfwInit();

    //设置主要次要版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}