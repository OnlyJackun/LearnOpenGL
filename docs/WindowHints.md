# Full window hint list
## Apply for window
| Hint | Description | Default | choice |
| :--- | :--- | :--- | :--- |
| **`GLFW_RESIZABLE`** | The window is resizable | `GL_TRUE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_VISIBLE`** | The window is visible  | `GL_TRUE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_DECORATED`** | The window is create with tile bar and frame | `GL_TRUE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_FOCUSED`** | The window will get focus after being created | `GL_TRUE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_AUTO_ICONIFY`** | Minimize after the window is closed | `GL_TRUE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_FLOATING`** | The window is at the top among all windows | `GL_FALSE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_MAXIMIZED`** | Maximize after the window is created | `GL_FALSE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_CENTER_CURSOR`** | Set the cursor at the middle of the window after creating the window | `GL_FALSE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_TRANSPARENT_FRAMEBUFFER`** | 帧缓冲是否支持透明（用于异形窗口）。 | `GL_FALSE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_FOCUS_ON_SHOW`** | 窗口显示时是否自动获得焦点。 | `GL_TRUE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_SCALE_TO_MONITOR`** | 窗口内容是否根据显示器缩放。 | `GL_FALSE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_RED_BITS`** | 颜色缓冲区**红**色通道的位深度。 | `8` | `0` 到 `INT_MAX` |
| **`GLFW_GREEN_BITS`** | 颜色缓冲区**绿**色通道的位深度。 | `8` | `0` 到 `INT_MAX` |
| **`GLFW_BLUE_BITS`** | 颜色缓冲区**蓝**色通道的位深度。 | `8` | `0` 到 `INT_MAX` |
| **`GLFW_ALPHA_BITS`** | 颜色缓冲区**Alpha**通道的位深度。 | `8` | `0` 到 `INT_MAX` |
| **`GLFW_DEPTH_BITS`** | 深度缓冲区的位深度（精度）。 | `24` | `0` 到 `INT_MAX` |
| **`GLFW_STENCIL_BITS`** | 模板缓冲区的位深度。 | `8` | `0` 到 `INT_MAX` |
| **`GLFW_ACCUM_RED_BITS`** | 累积缓冲区**红**色通道的位深度。 | `0` | `0` 到 `INT_MAX` |
| **`GLFW_ACCUM_GREEN_BITS`** | 累积缓冲区**绿**色通道的位深度。 | `0` | `0` 到 `INT_MAX` |
| **`GLFW_ACCUM_BLUE_BITS`** | 累积缓冲区**蓝**色通道的位深度。 | `0` | `0` 到 `INT_MAX` |
| **`GLFW_ACCUM_ALPHA_BITS`** | 累积缓冲区**Alpha**通道的位深度。 | `0` | `0` 到 `INT_MAX` |
| **`GLFW_AUX_BUFFERS`** | 辅助缓冲区的数量。 | `0` | `0` 到 `INT_MAX` |
| **`GLFW_SAMPLES`** | 多重采样抗锯齿（MSAA）的采样数。 | `0` | `0` 到 `INT_MAX` |
| **`GLFW_STEREO`** | 是否请求立体（3D）渲染。 | `GL_FALSE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_SRGB_CAPABLE`** | 帧缓冲是否支持 sRGB 色彩空间。 | `GL_FALSE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_DOUBLEBUFFER`** | 是否使用双缓冲。 | `GL_TRUE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_REFRESH_RATE`** | 全屏窗口的刷新率（Hz）。 | `GLFW_DONT_CARE` | 任意有效刷新率 |

## Apply for OpenGL Context
| 提示 (Hint) | 描述 | 默认值 | 可选值 |
| :--- | :--- | :--- | :--- |
| **`GLFW_CLIENT_API`** | 使用的图形 API。 | `GLFW_OPENGL_API` | `GLFW_OPENGL_API` or `GLFW_OPENGL_ES_API` |
| **`GLFW_CONTEXT_VERSION_MAJOR`** | OpenGL 主版本号。 | `1` | 任意有效主版本号 |
| **`GLFW_CONTEXT_VERSION_MINOR`** | OpenGL 次版本号。 | `0` | 任意有效次版本号 |
| **`GLFW_OPENGL_PROFILE`** | OpenGL 配置文件。 | `GLFW_OPENGL_ANY_PROFILE` | `GLFW_OPENGL_ANY_PROFILE`, `GLFW_OPENGL_COMPAT_PROFILE`, `GLFW_OPENGL_CORE_PROFILE` |
| **`GLFW_OPENGL_FORWARD_COMPAT`** | 是否请求向前兼容（禁用废弃功能）。 | `GL_FALSE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_OPENGL_DEBUG_CONTEXT`** | 是否创建调试上下文。 | `GL_FALSE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_CONTEXT_ROBUSTNESS`** | 上下文的健壮性策略。 | `GLFW_NO_ROBUSTNESS` | `GLFW_NO_ROBUSTNESS`, `GLFW_NO_RESET_NOTIFICATION`, `GLFW_LOSE_CONTEXT_ON_RESET` |
| **`GLFW_CONTEXT_RELEASE_BEHAVIOR`** | 上下文释放时的行为。 | `GLFW_RELEASE_BEHAVIOR_FLUSH` | `GLFW_RELEASE_BEHAVIOR_FLUSH` or `GLFW_RELEASE_BEHAVIOR_NONE` |
| **`GLFW_CONTEXT_NO_ERROR`** | 是否禁用 OpenGL 错误报告（可能提升性能）。 | `GL_FALSE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_CONTEXT_CREATION_API`** | 用于创建上下文的 API。 | `GLFW_NATIVE_CONTEXT_API` | `GLFW_NATIVE_CONTEXT_API` or `GLFW_EGL_CONTEXT_API` |

## Apply for special paltform
| 提示 (Hint) | 描述 | 默认值 | 可选值 |
| :--- | :--- | :--- | :--- |
| **`GLFW_COCOA_RETINA_FRAMEBUFFER`** | (macOS) 帧缓冲是否使用 Retina 分辨率。 | `GL_TRUE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_COCOA_FRAME_NAME`** | (macOS) 窗口的框架名称。 | `nil` | 字符串 |
| **`GLFW_COCOA_GRAPHICS_SWITCHING`** | (macOS) 是否允许自动切换显卡。 | `GL_FALSE` | `GL_TRUE` or `GL_FALSE` |
| **`GLFW_X11_CLASS_NAME`** | (X11) 窗口的 WM_CLASS 类名。 | 空字符串 | 字符串 |
| **`GLFW_X11_INSTANCE_NAME`** | (X11) 窗口的 WM_CLASS 实例名。 | 空字符串 | 字符串 |

## Addition
1.  **Reset Default Value**：调用 `glfwDefaultWindowHints()` 可以将所有提示恢复为默认值。
2.  **硬约束与软约束**：
    -   **硬约束**：`GLFW_STEREO`、`GLFW_OPENGL_PROFILE`、`GLFW_OPENGL_FORWARD_COMPAT` 等，必须精确满足，否则窗口创建会失败。
    -   **软约束**：`GLFW_RED_BITS`、`GLFW_DEPTH_BITS` 等，系统会尽量满足，若无法精确匹配，则使用最接近的值（妥协）。
3.  **查询属性**：窗口创建后，可以使用 `glfwGetWindowAttrib(window, hint)` 来查询实际生效的属性值。