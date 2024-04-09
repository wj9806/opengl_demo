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

    // ���ݲ���ϵͳѡ��·���ָ���
#if defined(_WIN32)
    const char separator = '\\';
    size_t lastSeparator = lastBackslash;
#else
    const char separator = '/';
    size_t lastSeparator = lastSlash;
#endif

    std::string basePath = exePath.substr(0, lastSeparator + 1);

    // �����ļ�·��������
    std::string filePath = basePath + fileName;

    // ���ַ���ת��Ϊchar*���Ͳ�����
    char* result = new char[filePath.length() + 1];
    std::strcpy(result, filePath.c_str());
    return result;
}

void envInit()
{
    glfwInit();

    //������Ҫ��Ҫ�汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}