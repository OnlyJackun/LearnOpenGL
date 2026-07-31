#include "glad/glad.h" //有坑，glfw3.h里包含的头文件再包含会报错，须在最前
#include "GLFW/glfw3.h"
#include <stdio.h>

int main()
{
    // 设置window某些标志必须在create前，之后无法更改
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // opengl需要一个具体的上下文，要先create window再立即绑context
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL_hello_triangle", nullptr, nullptr);
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
    // 编译着色器

    const GLchar *vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        void main()
        {
            gl_Position = vec4(position.x, position.y, position.z, 1.0f);
        }
    )";
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 理想情况下vertexShaderSource被分为很多段
    // 每段的指针按序存在一个array里
    // 然后向opengl传该array的指针
    // 由opengl从该array读取拼接编译
    // 1用来指明array长度
    // 第四个参数为着色器源码字符串长度(结尾没有\0时一定要算出来填上,
    // 有\0时可填可不填, 不填由gpu算长度, 填上则是直接读)
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
            FragColor = vec4(0.93f,0.0f, 0.0f, 1.0f);
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
    // 准备数据(存哪&如何访问)

    // vertex attribute object, 记录一个VBO及其所对应的数据的访问规则
    GLuint VAO1;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    // vertex buffer object, 真正存数据的, 可以是array, 代表连续多个
    GLuint VBO1;
    // VBO1就只存1, 它的ID
    glGenBuffers(1, &VBO1);
    // bind之后, 所有的操作的array buffer默认都是VBO1
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);

    // GLfloat triangleVertices[] = {
    //     -0.5f, -0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     0.0f, 0.5f, 0.0f};
    GLfloat rectangleVertices[] = {
        -0.5f, -0.5f, 0.0,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};

    GLuint rectangleIndices[] = {
        0, 2, 1,
        0, 2, 3};

    GLuint EBO1;
    glGenBuffers(1, &EBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);

    // the fourth parameter:
    // GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    // GL_STATIC_DRAW: the data is set only once and used many times.
    // GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    // glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

    // 配置vertex array格式
    // 配置到端口0(与顶点着色器相同)
    // 3维, GL_FLOAT类型, 不归一化
    // 相邻顶点间数据头部间隔长度, first数据相对数组头部的距离
    // 须在bindVBO和EBO之后, 这样VBO和EBO才会被记录
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    // 启用端口0, 这才传输数据, 可以只配置不启用
    glEnableVertexAttribArray(0);

    // 解绑VAO1, 终止记录
    glDisableVertexAttribArray(VAO1);

    // ===========================================
    // 渲染

    // 选择着色器
    glUseProgram(shaderProgram);
    // 绑定数据并配置访问方式(均记录在VAO1)
    glBindVertexArray(VAO1);
    // 正反面都只画顶点之间的线
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // =========================================

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.4f, 00.8f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 从第0个顶点开始画, 用3个顶点
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // 按照索引画, 一共要6个顶点, 索引的数据类型是GLuint, 第一个索引的offset为0
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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