# 🎨 Paint Application

A lightweight C++ drawing application built with **OpenGL**, **GLFW**, **Glad**, and **ImGui**.  
This project demonstrates real-time rendering, interactive GUI controls, and the fundamentals of a custom paint tool.

---

## Features
- **Drawing tools**: Pencil, Eraser   
- **Colors & Sizes**: Choose brush colors and adjust thickness  
- **Image Support**: Draw and save as an image   
- **Resizable canvas** with real-time updates  
- **Fast rendering** using OpenGL  
- **ImGui-powered GUI** for toolbars and options  

---

## Tech Stack
- **C++17**  
- **OpenGL** (rendering engine)  
- **GLFW** (window/context handling)  
- **Glad** (OpenGL function loader)  
- **ImGui** (graphical user interface)  

---

## Installation & Build

### Prerequisites
- Visual Studio with C++ Desktop Development  
- CMake (optional if you want cross-platform builds)  
- Windows (tested), but portable to Linux/macOS with minor changes  

### Steps (Windows / Visual Studio)
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/Paint.git
   cd Paint
   ```
2. Open `paintApplication.sln` in Visual Studio.  
3. Build the solution (`Ctrl + Shift + B`).  
4. Run the application (`F5`).  

Dependencies (GLFW, Glad, ImGui) are already included in the `Libraries/` and `Imgui/` folders.  

---

## Usage
- Select tools from the **toolbar (ImGui panel)**.  
- **Left Mouse Button** → draw with the selected tool.    
- Change **color & brush size** from the control panel.  
- Resize the window to adjust the canvas dynamically.