#include "glad/glad.h" //有坑，须在最前
#include "glfw/glfw3.h"
#include <stdio.h>

int main()
{
    // 设置window某些标志必须在create前，之后无法更改
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // opengl需要一个具体的上下文，要先create window再立即绑context
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // opengl的具体实现由各自厂商实现，要运行时找驱动问地址， 要在所有gl-方法之前
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // 视口，opengl绘制的，窗口的部分区域，以窗口左下角为原点
    glViewport(0, 0, 800, 600);

    void changeViewport(GLFWwindow *window, int width, int height);
    void reportError(int error, const char *description);

    glfwSetFramebufferSizeCallback(window, changeViewport);
    glfwSetErrorCallback(reportError);

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void changeViewport(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void reportError(int error, const char *description)
{
    fprintf(stderr, "error: %s\n", description);
}