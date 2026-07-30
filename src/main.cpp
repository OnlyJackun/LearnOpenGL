#include "glad/glad.h" //有坑，glfw3.h里包含的头文件再包含会报错，须在最前
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
    if (!window)
    {
        fprintf(stderr, "fail to create window");
        return -1;
    }
    glfwMakeContextCurrent(window);

    // opengl的具体实现由各自厂商实现，要运行时找驱动问地址， 要在所有gl-方法之前
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // 视口，opengl绘制的，窗口的部分区域，以窗口左下角为原点
    glViewport(0, 0, 800, 600);

    void changeViewport(GLFWwindow * window, int width, int height);
    void reportError(int error, const char *description);

    glfwSetFramebufferSizeCallback(window, changeViewport);
    glfwSetErrorCallback(reportError);

    void processInput(GLFWwindow * window);

    // =========================================

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    // vertex buffer object, 可以是array, 代表连续多个
    GLuint VBO;
    // 个数要与VBO/VBO[]长度相同
    // VBO用于存生成的buffer的地址
    glGenBuffers(1, &VBO);
    // 将VBO里存的地址所对应的buffer设为GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 上一步VBO所存地址所对应的buffer才被设为GL_ARRAY_BUFFER
    // 故此时GL_ARRAY_BUFFER特指VBO所存地址所对应的buffer
    // the fourth parameter:
    // GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    // GL_STATIC_DRAW: the data is set only once and used many times.
    // GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const GLchar *vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        void main()
        {
            GLPosition = vec4(position.x, position.y, position.z, 1.0);
        }
    )";
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 理想情况下vertexShaderSource被分为很多段
    // 每段的指针按序存在一个array里
    // 然后向opengl传该array的指针
    // 由opengl从该array读取拼接编译
    // 1用来指明array长度
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar info[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, info);
        fprintf(stderr, "shder compilation error: %s\n", info);
        return -1;
    }

    const GLchar *fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = ver4(0.0f,0.0f, 0.93f, 1.0f);
        }
    )";
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, info);
        fprintf(stderr, "shader program linking errer: %s", info);
        return -1;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // =========================================
    
    // =========================================

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.4f, 00.8f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // release resoureces, exit properly
    glfwTerminate();
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

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}