#pragma once

// render api
enum class YguiRenderAPI {
    OpenGL2,
    Vulkan
};


namespace YGUI {
    void Initialize();
    void NewFrame(float deltaTime, float displayWidth, float displayHeight);
    void EndFrame();
    void Shutdown();

    // ygui elements
    void DrawWindow(const char* title, bool* open);
    void EndWindow();
    bool DrawButton(const char* label, float width = 100.0f, float height = 30.0f);
    void DrawLabel(const char* fmt, ...);
    bool DrawTextBox(const char* label, char* buffer, size_t bufferSize);
    bool DrawCheckBox(const char* label, bool* value);
    bool DrawSliderFloat(const char* label, float* value, float min, float max);

    void DrawServerBrowser(bool* open);
}
