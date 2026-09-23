#include "yg_ygui.h"
#include "imgui.h"
#include <stdarg.h>
#include <cstdio>

namespace YGUI {

    void Initialize() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiStyle& style = ImGui::GetStyle();

        // Köşeler
        style.WindowRounding = 0.0f;
        style.FrameRounding = 0.0f;
        style.PopupRounding = 0.0f;
        style.ScrollbarRounding = 0.0f;
        style.GrabRounding = 0.0f;
        style.TabRounding = 0.0f;

        // Kalın ve net endüstriyel çizgiler
        style.WindowBorderSize = 1.0f;
        style.FrameBorderSize = 1.0f;
        style.PopupBorderSize = 1.0f;

        // İç boşlukları daraltır
        style.WindowPadding = ImVec2(8.0f, 8.0f);
        style.FramePadding = ImVec2(6.0f, 4.0f);
        style.ItemSpacing = ImVec2(6.0f, 6.0f);

        // Siyah, Bordo Kırmızısı ve Hafif Beyaz Renk Paleti
        ImVec4* colors = style.Colors;

        colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.98f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.95f);
        colors[ImGuiCol_Border] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

        colors[ImGuiCol_Text] = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);

        colors[ImGuiCol_FrameBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.35f, 0.10f, 0.10f, 1.00f);

        colors[ImGuiCol_TitleBg] = ImVec4(0.25f, 0.05f, 0.05f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.42f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.04f, 0.04f, 0.75f);

        colors[ImGuiCol_Button] = ImVec4(0.35f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.48f, 0.12f, 0.12f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.05f, 0.05f, 1.00f);

        colors[ImGuiCol_Header] = ImVec4(0.32f, 0.07f, 0.07f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.05f, 0.05f, 1.00f);

        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.35f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.48f, 0.12f, 0.12f, 1.00f);

        colors[ImGuiCol_SliderGrab] = ImVec4(0.42f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.55f, 0.12f, 0.12f, 1.00f);

        colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.42f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_TabActive] = ImVec4(0.32f, 0.07f, 0.07f, 1.00f);
    }

    void NewFrame(float deltaTime, float displayWidth, float displayHeight) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(displayWidth, displayHeight);
        io.DeltaTime = deltaTime;
        ImGui::NewFrame();
    }

    void EndFrame() {
        ImGui::Render();
    }

    void Shutdown() {
        ImGui::DestroyContext();
    }

    // Temel Bileşen Uygulamaları
    void DrawWindow(const char* title, bool* open) {
        ImGui::Begin(title, open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    }

    void EndWindow() {
        ImGui::End();
    }

    bool DrawButton(const char* label, float width, float height) {
        return ImGui::Button(label, ImVec2(width, height));
    }

    void DrawText(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        ImGui::TextV(fmt, args);
        va_end(args);
    }

    bool DrawTextBox(const char* label, char* buffer, size_t bufferSize) {
        return ImGui::InputText(label, buffer, bufferSize);
    }

    bool DrawCheckBox(const char* label, bool* value) {
        return ImGui::Checkbox(label, value);
    }

    bool DrawSliderFloat(const char* label, float* value, float min, float max) {
        return ImGui::SliderFloat(label, value, min, max);
    }

    void SameLine() { ImGui::SameLine(); }
    void Separator() { ImGui::Separator(); }
    void Spacing() { ImGui::Spacing(); }
}
