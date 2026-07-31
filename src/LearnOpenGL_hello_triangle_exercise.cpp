#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <stdio.h>

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL_hello_triangle_exercise", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0, 800, 600);

    void reportError(int error, const char *info);
    void changeViewport(GLFWwindow * window, int width, int height);

    glfwSetErrorCallback(reportError);
    glfwSetFramebufferSizeCallback(window, changeViewport);

    void processInput(GLFWwindow * window);

    const GLchar *vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 pos;
        void main(){
            gl_Position = vec4(pos, 1.0f);
        }
    )";

    const GLchar *fragmentShaderSource1 = R"(
        #version 330 core
        out vec4 FragColor;
        void main(){
            FragColor = vec4(0.9f, 0.0f, 0.0f, 1.0f);
        }
    )";

    const GLchar *fragmentShaderSource2 = R"(
        #version 330 core
        out vec4 FragColor;
        void main(){
            FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
        }
    )";

    GLuint vertexShader, fragmentShader1, fragmentShader2;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    GLuint shaderProgram1, shaderProgram2;
    shaderProgram1 = glCreateProgram();
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram1);
    glLinkProgram(shaderProgram2);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);

    GLuint VAO1, VAO2, VBO, EBO1, EBO2;
    glGenVertexArrays(1, &VAO1);
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO1);
    glGenBuffers(1, &EBO2);

    GLfloat vertices[] = {
        -0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f};

    GLuint indices1[] = {
        0, 1, 4,
        0, 5, 4};
    GLuint indices2[] = {
        1, 2, 3,
        1, 4, 3};

    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);
    glDisableVertexAttribArray(VAO1);

    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);
    glDisableVertexAttribArray(VAO2);

    while (!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.4f, 00.8f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(VAO1);
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(VAO2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void reportError(int error, const char *info)
{
    fprintf(stderr, "error: %d : %s", error, info);
}

void changeViewport(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}