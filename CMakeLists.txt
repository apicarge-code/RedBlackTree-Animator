cmake_minimum_required(VERSION 3.10)
project(RedBlackTree-Animator)

# 1. 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. 包含头文件搜索路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imgui)

# 3. 收集所有需要编译的源文件
set(SOURCES
    main.cpp
    RBTree.cpp
    # 核心 ImGui 源码
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    # ImGui 平台后端
    imgui/imgui_impl_win32.cpp
    imgui/imgui_impl_dx11.cpp
)

# 4. 生成可执行程序（WIN32 标志：告诉链接器这是 GUI 程序，不创建控制台窗口）
add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

# 5. 链接 Windows 系统库（DX11 运行必备）
target_link_libraries(${PROJECT_NAME} 
    d3d11 
    d3dcompiler 
    dwmapi 
    comctl32
)

# 6. 设置输出目录（方便你找 .exe）
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")