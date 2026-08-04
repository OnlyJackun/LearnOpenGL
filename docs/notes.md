# Steps
0. Initialize
1. Create a window
2. Bind context
3. Load *GLLoader*
4. Set viewport
5. Bind some *CallbackFunc*
6. Compile shaders and link to shader programs
7. Organize and Pass data
8. Start the main loop

The sequence of the zeroth, first, second and third must not be changed. The fourth is suggested following the third. The eighth should be the last(No one will want to change it). And the sequence of rest can be changed.

# Detail
## Initialize
Include `glad.h` and `glfw3.h` head files.

Then `glfwInit();`.

> **Attention**
>   - `glad.h` is suggested being included before including `glfw3.h`.
>   - That's because they both include `gl.h`.And repeatedly including will case exception.
>   - Though the conflict is repaired in new version,
to be compatible with the old, including `glad.h` before `glfw3.h` is still strongly recommended.
>   - Like this:
>   ```cpp
>   #include <glad/glad.h>
>   #include <GLFW/glfw3.h>
>   
>   void main(){
>       glfwInit();
>   }
>   ```


## Create a window
First, we should set some flag, or `hint` we calling it, before creating a window. These hints can't be changed after creating the window, so we should do it before `glfwCreateWindow`. Like this:
```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```
> More window hints in [here](./WindowHints.md).

Then, create the window, and specify the width, height, title,monitor(to decide in which monitor the window will maximize) and another pointer of window(to share the same sources/context with it)
```cpp
GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpengGL", nullptr, nullptr);
```
Pay attention to the `window`, if it is null, it means creating window is unsuccessful.

## Bind context
What's the most important is that you should bind the window context to OpenGL.
```cpp
glfwMakeContextCurrent(window);
```
OpenGL needs a context to perform all operations.

## Load *GLLoader*
And what's also most import is that we need still a tool to find the address of specific functions of OpenGL. <br/>
In fact, OpenGL is just a standard, and the specific implementation is up to the specific driver manufacturer. <br/>
So we don't where are the functions at compile-time and need to query the address of the functions at run-time.

The tool is `glfwGetProcAddress`, but we need to pass it to `gladLoadGLLoader`, because glfw(focus on window in different OS more not GPU) is just used to manage windows, which interact with OS and can query the driver, and glad(focus on GPU more not OS) is exactly used to interact with GPU, but cannot query. Like this, but notice the type(just need to convert):
```cpp
gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
```