#pragma once

#ifdef YGUI_DLL_EXPORTS
#define YGUI_API __declspec(dllexport)
#else
#define YGUI_API __declspec(dllimport)
#endif

// render api
enum class YguiRenderAPI {
    OpenGL2,
    Vulkan
};


namespace YGUI {
    YGUI_API void Initialize();
    YGUI_API void NewFrame(float deltaTime, float displayWidth, float displayHeight);
    YGUI_API void EndFrame();
    YGUI_API void Shutdown();

    // ygui elements
    YGUI_API void DrawWindow(const char* title, bool* open);
    YGUI_API void EndWindow();
    YGUI_API bool DrawButton(const char* label, float width = 100.0f, float height = 30.0f);
    YGUI_API void DrawLabel(const char* fmt, ...);
    YGUI_API bool DrawTextBox(const char* label, char* buffer, size_t bufferSize);
    YGUI_API bool DrawCheckBox(const char* label, bool* value);
    YGUI_API bool DrawSliderFloat(const char* label, float* value, float min, float max);

    YGUI_API void DrawServerBrowser(bool* open);

    YGUI_API bool InitializeRenderBackend(YguiRenderAPI api);

    YGUI_API void AddMousePosEvent(float x, float y);
    YGUI_API void AddMouseButtonEvent(int button, bool down);
    YGUI_API void AddMouseWheelEvent(float wheelX, float wheelY);
    YGUI_API void AddKeyEvent(int keycode, bool down);
    YGUI_API void AddInputCharacter(unsigned int codepoint);
}
