cmake_minimum_required(VERSION 4.4.0)
project(LearnOpenGL VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_subdirectory(external/glfw)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/glad.c
)

target_link_libraries(${PROJECT_NAME}
    glfw
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME}
        opengl32
        gdi32
    )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)