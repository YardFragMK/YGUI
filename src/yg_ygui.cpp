#include "yg_ygui.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <stdarg.h>
#include <cstdio>

namespace YGUI {
    static ImU32 Color_Light = ImGui::ColorConvertFloat4ToU32(ImVec4(0.60f, 0.60f, 0.60f, 1.00f));
    static ImU32 Color_Dark = ImGui::ColorConvertFloat4ToU32(ImVec4(0.02f, 0.02f, 0.02f, 1.00f));
    static ImU32 Color_Shadow = ImGui::ColorConvertFloat4ToU32(ImVec4(0.15f, 0.03f, 0.03f, 1.00f));

    void DrawSunkenRect(ImDrawList* drawList, ImVec2 min, ImVec2 max) {
        drawList->AddLine(ImVec2(min.x, min.y), ImVec2(max.x - 1, min.y), Color_Dark);
        drawList->AddLine(ImVec2(min.x, min.y), ImVec2(min.x, max.y - 1), Color_Dark);
        drawList->AddLine(ImVec2(max.x - 1, min.y), ImVec2(max.x - 1, max.y - 1), Color_Light);
        drawList->AddLine(ImVec2(min.x, max.y - 1), ImVec2(max.x - 1, max.y - 1), Color_Light);
        if (max.x - min.x > 3.0f && max.y - min.y > 3.0f) {
            drawList->AddLine(ImVec2(min.x + 1, min.y + 1), ImVec2(max.x - 2, min.y + 1), Color_Shadow);
            drawList->AddLine(ImVec2(min.x + 1, min.y + 1), ImVec2(min.x + 1, max.y - 2), Color_Shadow);
        }
    }

    void Initialize() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 0.0f;
        style.FrameRounding = 0.0f;
        style.PopupRounding = 0.0f;
        style.ScrollbarRounding = 0.0f;
        style.GrabRounding = 0.0f;
        style.TabRounding = 0.0f;
        style.WindowBorderSize = 0.0f;
        style.FrameBorderSize = 0.0f;
        style.PopupBorderSize = 0.0f;
        style.WindowPadding = ImVec2(8.0f, 8.0f);
        style.FramePadding = ImVec2(6.0f, 4.0f);
        style.ItemSpacing = ImVec2(6.0f, 6.0f);
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

    void Draw3DRect(ImDrawList* drawList, ImVec2 min, ImVec2 max, bool pressed) {
        ImU32 topLeftColor = pressed ? Color_Dark : Color_Light;
        ImU32 bottomRightColor = pressed ? Color_Light : Color_Dark;
        drawList->AddLine(ImVec2(min.x, min.y), ImVec2(max.x - 1, min.y), topLeftColor);
        drawList->AddLine(ImVec2(min.x, min.y), ImVec2(min.x, max.y - 1), topLeftColor);
        drawList->AddLine(ImVec2(max.x - 1, min.y), ImVec2(max.x - 1, max.y - 1), bottomRightColor);
        drawList->AddLine(ImVec2(min.x, max.y - 1), ImVec2(max.x - 1, max.y - 1), bottomRightColor);
        if (max.x - min.x > 3.0f && max.y - min.y > 3.0f) {
            ImU32 innerTopLeft = pressed ? Color_Shadow : Color_Light;
            drawList->AddLine(ImVec2(min.x + 1, min.y + 1), ImVec2(max.x - 2, min.y + 1), innerTopLeft);
            drawList->AddLine(ImVec2(min.x + 1, min.y + 1), ImVec2(min.x + 1, max.y - 2), innerTopLeft);
        }
    }

    void NewFrame(float deltaTime, float displayWidth, float displayHeight) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(displayWidth, displayHeight);
        io.DeltaTime = deltaTime > 0.0f ? deltaTime : (1.0f / 60.0f);
        ImGui::NewFrame();
    }

    void EndFrame() {
        ImGui::Render();
    }

    void Shutdown() {
        ImGui::DestroyContext();
    }

    void DrawWindow(const char* title, bool* open) {
        ImGui::Begin(title, open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (!window->SkipItems) {
            Draw3DRect(ImGui::GetWindowDrawList(), window->Pos, ImVec2(window->Pos.x + window->Size.x, window->Pos.y + window->Size.y), false);
        }
    }

    void EndWindow() {
        ImGui::End();
    }

    bool DrawButton(const char* label, float width, float height) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems) return false;
        ImGuiContext& g = *GImGui;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = ImGui::CalcItemSize(ImVec2(width, height), label_size.x + g.Style.FramePadding.x * 2.0f, label_size.y + g.Style.FramePadding.y * 2.0f);
        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ImGui::ItemSize(size, g.Style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id)) return false;
        bool hovered = false;
        bool held = false;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
        ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
        window->DrawList->AddRectFilled(bb.Min, bb.Max, col);
        Draw3DRect(window->DrawList, bb.Min, bb.Max, held && hovered);
        ImVec2 text_pos(bb.Min.x + g.Style.FramePadding.x, bb.Min.y + g.Style.FramePadding.y);
        if (held && hovered) {
            text_pos.x += 1.0f;
            text_pos.y += 1.0f;
        }
        ImGui::RenderTextClipped(text_pos, ImVec2(bb.Max.x - g.Style.FramePadding.x, bb.Max.y - g.Style.FramePadding.y), label, NULL, &label_size, g.Style.ButtonTextAlign, &bb);
        return pressed;
    }

    void DrawLabel(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        ImGui::TextV(fmt, args);
        va_end(args);
    }

    bool DrawTextBox(const char* label, char* buffer, size_t bufferSize) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems) return false;
        bool changed = ImGui::InputText(label, buffer, bufferSize);
        ImGuiContext& g = *GImGui;
        ImVec2 rect_min = ImGui::GetItemRectMin();
        ImVec2 rect_max = ImGui::GetItemRectMax();
        float label_width = ImGui::CalcTextSize(label, NULL, true).x;
        float input_box_right = rect_max.x - (label_width > 0.0f ? label_width + g.Style.ItemInnerSpacing.x : 0.0f);
        DrawSunkenRect(window->DrawList, rect_min, ImVec2(input_box_right, rect_max.y));
        return changed;
    }

    bool DrawCheckBox(const char* label, bool* value) {
        return ImGui::Checkbox(label, value);
    }

    bool DrawSliderFloat(const char* label, float* value, float min, float max) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems) return false;
        ImGuiContext& g = *GImGui;
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0, 0, 0, 0));
        bool changed = ImGui::SliderFloat(label, value, min, max, "");
        ImGui::PopStyleColor(5);
        ImGuiID last_id = ImGui::GetItemID();
        ImVec2 rect_min = ImGui::GetItemRectMin();
        ImVec2 rect_max = ImGui::GetItemRectMax();
        ImRect bb(rect_min, rect_max);
        float label_width = ImGui::CalcTextSize(label, NULL, true).x;
        float slider_right = bb.Max.x - (label_width > 0.0f ? label_width + g.Style.ItemInnerSpacing.x : 0.0f);
        ImRect slider_bb(bb.Min, ImVec2(slider_right, bb.Max.y));
        float center_y = (slider_bb.Min.y + slider_bb.Max.y) * 0.5f;
        ImVec2 groove_min(slider_bb.Min.x, center_y - 2.0f);
        ImVec2 groove_max(slider_bb.Max.x, center_y + 2.0f);
        DrawSunkenRect(window->DrawList, groove_min, groove_max);
        float grab_w = 12.0f;
        float slider_width = slider_bb.Max.x - slider_bb.Min.x;
        float t = 0.0f;
        if (max > min) {
            float v_clamped = ImClamp(*value, min, max);
            t = (v_clamped - min) / (max - min);
            t = ImClamp(t, 0.0f, 1.0f);
        }
        float grab_x = slider_bb.Min.x + grab_w * 0.5f + t * (slider_width - grab_w);
        ImRect grab_bb(ImVec2(grab_x - grab_w * 0.5f, slider_bb.Min.y + 1.0f), ImVec2(grab_x + grab_w * 0.5f, slider_bb.Max.y - 1.0f));
        window->DrawList->AddRectFilled(grab_bb.Min, grab_bb.Max, ImGui::GetColorU32(ImGuiCol_Button));
        bool grab_active = (g.ActiveId == last_id);
        Draw3DRect(window->DrawList, grab_bb.Min, grab_bb.Max, grab_active);
        return changed;
    }

    void SameLine() {
        ImGui::SameLine();
    }

    void Separator() {
        ImGui::Separator();
    }

    void Spacing() {
        ImGui::Spacing();
    }
}
