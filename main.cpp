#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <Imgui/imgui.h>
#include <Imgui/backends/imgui_impl_glfw.h>
#include <Imgui/backends/imgui_impl_opengl3.h>

#include "VAO.h"
#include "VBO.h"
#include "shaderClass.h"
#include "Vector3.h"
#include "Color4.h"
#include "modes.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

// -------------------------------------------------------- data --------------------------------------------------------

float mouseX = 0.0, mouseY = 0.0;
int startWindowX = 0, startWindowY = 0, windowWidth = 1280, windowHeight = 720;
int Size = 100, currentVBOIndex = 0;
bool fontInput = false;
float fontSize = 3.0f;
float fontThickness = 3.0f;
float eraserSize = 3.0f;
bool colorInput = false;
bool onUI = false;
bool currentMode = PENCIL;
Color4 color4(0.0f, 0.0f, 0.0f, 1.0f);
Color4 oldColor4(0.0f, 0.0f, 0.0f, 1.0f);
// input vertices
std::vector<std::vector<Vector3>> allVertices(Size);

// -------------------------------------------------------- data --------------------------------------------------------

// -------------------------------------------------------- callback functions --------------------------------------------------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}


void mouse_moved(GLFWwindow* window, double xpos, double ypos) {
    mouseX = xpos;
    mouseY = ypos;
    std::cout << "Cursor at: (" << xpos << ", " << ypos << ")\n";
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        std::cout << "Key pressed: " << key << std::endl;
        // click q to clear the window
        //if (key == GLFW_KEY_Q) {
        //    for (auto& Line : allVertices) {
        //        Line.clear();
        //    }
        //    Size = 100;
        //    allVertices.resize(Size);
        //    currentVBOIndex = 0;
        //}
        // click c to change the color
        //if (key == GLFW_KEY_C) {
        //    colorInput = true;
        //}
        //if (colorInput) {
        //    std::cout << "Enter R G B A: \n";
        //    std::cin >> color4.R >> color4.G >> color4.B >> color4.A;
        //    colorInput = false;
        //}
        // click b to use the Eraser
        //if (key == GLFW_KEY_B) {
        //    color4.R = 1.0f;
        //    color4.G = 1.0f;
        //    color4.B = 1.0f;
        //    color4.A = 1.0f;
        //}
        // click s to change the font thickness
        //if (key == GLFW_KEY_S) {
        //    fontInput = true;
        //}
        //if (fontInput) {
        //    std::cout << "Enter font thickness: \n";
        //    std::cin >> fontThickness;
        //    fontInput = false;
        //}
    }
    else if (action == GLFW_RELEASE) {
        std::cout << "Key released: " << key << std::endl;
    }
}
// -------------------------------------------------------- callback functions --------------------------------------------------------

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set OpenGL version (e.g., 3.3 Core)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Simple Drawing App", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Set context
    glfwMakeContextCurrent(window);

    // Initialize GLAD here!
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }
    
    glEnable(GL_PROGRAM_POINT_SIZE);

    // callback functions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_moved);
    glfwSetKeyCallback(window, key_callback);

    // ------------------------------------- vertex array object -------------------------------------
    VAO VAO1;
    VBO VBO1;
    VAO1.Bind();
    VAO1.LinkVBO(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*) 0);
    VAO1.LinkVBO(VBO1, 1, 4, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkVBO(VBO1, 2, 1, GL_FLOAT, 8 * sizeof(float), (void*)(7 * sizeof(float)));
    VAO1.Unbind();

    // ------------------------------------- shader program -------------------------------------

    Shader shaderProgram("default.vert", "default.frag");

    // ------------------------------------------------------------------------------------------

    // ------------------------------------- IMGUI Initialization -------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

     // ------------------------------------------------------------------------------------------

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        colorInput = false;
        fontInput = false;
        onUI = false;

        if (io.WantCaptureMouse)
            onUI = true;

        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        
        glfwGetWindowPos(window, &startWindowX, &startWindowY);

        if (currentMode == PENCIL) {
            fontThickness = fontSize;
        }
        else {
            fontThickness = eraserSize;
        }

        // ---------------------------------------------------------------------------------------------------------
        // Mouse events
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !onUI) {
            float ndcX = (2.0f * mouseX) / windowWidth - 1.0f;
            float ndcY = 1.0f - (2.0f * mouseY) / windowHeight;
            if (allVertices[currentVBOIndex].size() > 0) {
                if (allVertices[currentVBOIndex].back().x != ndcX || allVertices[currentVBOIndex].back().y != ndcY) {
                    allVertices[currentVBOIndex].push_back(Vector3(ndcX, ndcY, 0, color4, fontThickness));
                }
            }
            else {
                allVertices[currentVBOIndex].push_back(Vector3(ndcX, ndcY, 0, color4, fontThickness));
            }
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && !onUI) {
            currentVBOIndex++;
            if (currentVBOIndex >= Size) {
                Size *= 2;
                allVertices.resize(Size);
            }
        }
        // ---------------------------------------------------------------------------------------------------------

        VAO1.Bind();
        VBO1.Bind();
        shaderProgram.Activate();

        // Render background color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ---------- IMGUI --------------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // -------------------------------

        // Render user drawings
        for (int i = 0; i <= currentVBOIndex; i++) {
            if (allVertices[i].empty())
                continue;

            glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * allVertices[i].size(), allVertices[i].data(), GL_DYNAMIC_DRAW);
            if (allVertices[i].size() == 1) {
                glDrawArrays(GL_POINTS, 0, allVertices[i].size());
            }
            else {
                glLineWidth(allVertices[i].front().PointSize);
                glDrawArrays(GL_LINE_STRIP, 0, allVertices[i].size());
            }
        }
        // ---------- IMGUI --------------
        ImGui::Begin("Paint UI", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos(ImVec2(windowWidth - 330, 0));
        ImGui::SetWindowSize(ImVec2(330, 200));
        ImGui::Text("Welcome to Paint Application.");
        if (currentMode == PENCIL) {
            ImGui::SliderFloat("Font Size", &fontSize, 1.0f, 30.0f);
            ImGui::ColorEdit4("Color", &color4.R);
        }
        else {
            ImGui::SliderFloat("Eraser Size", &eraserSize, 1.0f, 50.0f);
        }
        if (ImGui::Button("Pencil")) {
            if (currentMode == ERASER) {
                color4 = oldColor4;
            }
            currentMode = PENCIL;
        }
        if (ImGui::Button("Eraser")) {
            if (currentMode == PENCIL) {
                oldColor4 = color4;
            }
            color4.R = 1.0f;
            color4.G = 1.0f;
            color4.B = 1.0f;
            color4.A = 1.0f;
            currentMode = ERASER;
        }
        if (ImGui::Button("Clear")) {
            for (auto& Line : allVertices) {
                Line.clear();
            }
            Size = 100;
            allVertices.resize(Size);
            currentVBOIndex = 0;
        }
        if (ImGui::Button("Save As Image")) {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);

            unsigned char* pixels = new unsigned char[width * height * 3];

            glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
            
            for (int y = 0; y < height / 2; ++y) {
                for (int x = 0; x < width * 3; ++x) {
                    std::swap(pixels[y * width * 3 + x], pixels[(height - 1 - y) * width * 3 + x]);
                }
            }

            stbi_write_png("PaintImage.png", width, height, 3, pixels, width * 3);

            delete[] pixels;
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // -------------------------------
        // Swap and poll
        glfwSwapBuffers(window);
        glfwPollEvents();
        //std::cout << "start at ( " << startWindowX << ", " << startWindowY << ")\n";
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    VAO1.Delete();
    VBO1.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}