#define _CRT_SECURE_NO_WARNINGS
#include <iostream> //Includes
#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "tinyexpr.h"
#pragma comment(lib, "opengl32.lib")

float EvaluateExpression(const char* expr) { //Function calculatoion
    int err;
    double res = te_interp(expr, &err);
    return (float)res;
}

void DrawButtCalc(const char* FourXFourMATRIX[4][4], char *input) { //Draw Button: 0, 1, 2, 3, ..., 9, +, -, *, / 
    for (int OneElements = 0; OneElements < 4; OneElements++) {
        for (int TwoElements = 0; TwoElements < 4; TwoElements++) {
            if (ImGui::Button(FourXFourMATRIX[OneElements][TwoElements], ImVec2(50, 50))) {
                strcat(input, FourXFourMATRIX[OneElements][TwoElements]);
            }
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }
}

void windowCalc() {
    //Initialisation GLFW and ImGUI
	glfwInit();
	GLFWwindow* windowCalculator = glfwCreateWindow(500, 500, "CALCULATOR", NULL, NULL);
	glfwMakeContextCurrent(windowCalculator);
	glfwSwapInterval(1);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(windowCalculator, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    //Important calculator variables
    char inputikkk[256] = "";
    float RESULTAT = 0.0;
    const char* Buttons[4][4] = {
    { "7", "8", "9", "/" },
    { "4", "5", "6", "*" },
    { "1", "2", "3", "-" },
    { "0", "(", ")", "+" },
    };
    //Main render loop/while
    while (!glfwWindowShouldClose(windowCalculator)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        ImGui::SetNextWindowPos(ImVec2(0, 0));//Set start position window
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

        ImGui::Begin("Calculator", nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoBackground |
            ImGuiWindowFlags_NoBringToFrontOnFocus
        );
        ImGui::Text("Task: %s", inputikkk);
        ImGui::Text("Result: %.3f", RESULTAT);
        DrawButtCalc(Buttons, inputikkk);
        if (ImGui::Button("=", ImVec2(75, 50))) { //Draw button =
            RESULTAT = EvaluateExpression(inputikkk);
        }
        ImGui::SameLine();
        if (ImGui::Button("C", ImVec2(75, 50))) { //Draw button Сlear
            inputikkk[0] = '\0';
            RESULTAT = 0.0f;
        }
        ImGui::SameLine();
        if (ImGui::Button("DEL", ImVec2(75, 50))) { //Draw button Delete
            int len = strlen(inputikkk);
            if (len > 0) inputikkk[len - 1] = '\0';
        }
        if (ImGui::IsKeyPressed(ImGuiKey_0)) strcat(inputikkk, "0"); //Registering keys from the keyboard
        if (ImGui::IsKeyPressed(ImGuiKey_1)) strcat(inputikkk, "1");
        if (ImGui::IsKeyPressed(ImGuiKey_2)) strcat(inputikkk, "2");
        if (ImGui::IsKeyPressed(ImGuiKey_3)) strcat(inputikkk, "3");
        if (ImGui::IsKeyPressed(ImGuiKey_4)) strcat(inputikkk, "4");
        if (ImGui::IsKeyPressed(ImGuiKey_5)) strcat(inputikkk, "5");
        if (ImGui::IsKeyPressed(ImGuiKey_6)) strcat(inputikkk, "6");
        if (ImGui::IsKeyPressed(ImGuiKey_7)) strcat(inputikkk, "7");
        if (ImGui::IsKeyPressed(ImGuiKey_8)) strcat(inputikkk, "8");
        if (ImGui::IsKeyPressed(ImGuiKey_9)) strcat(inputikkk, "9");
        if (ImGui::IsKeyPressed(ImGuiKey_KeypadAdd)) strcat(inputikkk, "+");
        if (ImGui::IsKeyPressed(ImGuiKey_Minus)) strcat(inputikkk, "-");
        if (ImGui::IsKeyPressed(ImGuiKey_Slash)) strcat(inputikkk, "/");
        if (ImGui::IsKeyPressed(ImGuiKey_Equal)) strcat(inputikkk, "=");
        if (ImGui::IsKeyPressed(ImGuiKey_Enter)) RESULTAT = EvaluateExpression(inputikkk);
        if (ImGui::IsKeyPressed(ImGuiKey_Backspace)) {
            int len = (int)strlen(inputikkk);
            if (len > 0) inputikkk[len - 1] = '\0';
        }
        ImGui::End(); //End render
        ImGui::Render();

        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(windowCalculator);
    }
    ImGui_ImplOpenGL3_Shutdown(); //Destroy/Close window
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(windowCalculator);
    glfwTerminate();
}
//IS NOT PROPAGANDA
//ЭТО НЕ ПРОПАГАНДА

//⚠️ Заранее извиняюсь за использование символа, напоминающего свастику. Я никого не хотел обидеть — это не пропаганда
//а высмеивание абсурда и превращение табу в шутку. Символ — мем, а не идеология.

//⚠️ I apologize in advance for the use of a symbol resembling a swastika. No offense intended — this is not propaganda, but satire.
//The goal is to mock absurdity and turn taboo into humor. This symbol is a meme, not an ideology.

// ||        ============
// ||        ||
// ||        ||
// ||        ||
// ||        ||
// ======================
//           ||        ||
//           ||        ||
//           ||        ||
//           ||        ||
//  ===========        ||

//Main
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    windowCalc(); //Call function draw window/calculator
}