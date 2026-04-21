# Red-Black Tree Animator (红黑树动画演示工具)

## 项目简介

这是一个基于 C++ 开发的红黑树可视化工具。它利用 ImGui 构建交互界面，并使用 DirectX 11 进行硬件加速渲染，帮助用户直观地理解红黑树的插入、平衡与旋转过程。

## 核心功能

- **动态插入节点**：实时观察红黑树的平衡过程，包括变色、左旋、右旋等操作。
- **一体化界面**：整合控制面板与绘图区域，提供流畅的操作体验。
- **图例说明**：
  - 🔴 红色节点：表示双红冲突
  - ⚫ 黑色节点：表示平衡节点

## 技术栈

- **C++17**：核心逻辑实现
- **CMake**：跨平台构建系统
- **ImGui**：即时模式 GUI 框架
- **DirectX 11**：硬件加速图形渲染

## 如何构建

### 环境要求

- **操作系统**：Windows 10/11
- **编译器**：Visual Studio 2022 (MSVC)
- **构建工具**：CMake 3.20+

### 构建步骤

1. 克隆项目到本地：
   ```bash
   git clone <repository-url>
   cd RedBlackTree-Animator
   ```

2. 创建构建目录并配置 CMake：
   ```bash
   mkdir build && cd build
   cmake ..
   ```

3. 编译项目：
   ```bash
   cmake --build . --config Release
   ```

4. 运行程序：
   ```bash
   .\bin\Release\RedBlackTree-Animator.exe
   ```

## 使用说明

- 在控制面板中输入整数值，点击 **Insert** 按钮插入节点。
- 点击 **Clear** 按钮清空当前树。
- 使用 **+/-** 按钮调整输入值。

## 项目结构

```
RedBlackTree-Animator/
├── CMakeLists.txt      # CMake 构建配置
├── main.cpp            # 程序入口与 ImGui 初始化
├── RBTree.h            # 红黑树类声明
├── RBTree.cpp          # 红黑树核心逻辑实现
├── imgui/              # ImGui 库文件
│   ├── imgui.cpp
│   ├── imgui.h
│   ├── imgui_impl_dx11.cpp
│   ├── imgui_impl_win32.cpp
│   └── ...
└── README.md           # 项目说明文档
```

## 许可证

本项目仅供学习与研究使用。
