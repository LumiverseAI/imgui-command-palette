#pragma once

#include <imgui.h>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

// TODO support std::string_view
// TODO support function pointer callback in addition to std::function

enum ImCmdTextType
{
    ImCmdTextType_Regular,
    ImCmdTextType_Highlight,
    ImCmdTextType_COUNT,
};

enum ImCmdTextFlag
{
    /// Whether the text is underlined. Default false.
    ImCmdTextFlag_Underline,
    ImCmdTextFlag_COUNT,
};

namespace ImCmd
{
struct Command
{
    std::string Name;
    std::function<void()> InitialCallback;
    std::function<void(int selected_option)> SubsequentCallback;
    std::function<void()> TerminatingCallback;
};

// Initialization
struct Context;

/// Create a new context object. If there is currently no context bound, it will also be bound as the current context.
IMGUI_API Context* CreateContext();
/// Destroys the currently bound context.
IMGUI_API void DestroyContext();
IMGUI_API void DestroyContext(Context* context);

IMGUI_API void SetCurrentContext(Context* context);
IMGUI_API Context* GetCurrentContext();

// Command management
IMGUI_API void AddCommand(Command command);
IMGUI_API void RemoveCommand(const char* name);

// Styling
IMGUI_API bool GetStyleFlag(ImCmdTextType type, ImCmdTextFlag flag);
IMGUI_API void SetStyleFlag(ImCmdTextType type, ImCmdTextFlag flag, bool enabled);
IMGUI_API ImFont* GetStyleFont(ImCmdTextType type);
IMGUI_API void SetStyleFont(ImCmdTextType type, ImFont* font);
IMGUI_API ImU32 GetStyleColor(ImCmdTextType type);
IMGUI_API void SetStyleColor(ImCmdTextType type, ImU32 color);
IMGUI_API void ClearStyleColor(ImCmdTextType type); //< Clear the style color for the given type, defaulting to ImGuiCol_Text

// Command palette widget
IMGUI_API void SetNextCommandPaletteSearch(const char* text);
IMGUI_API void SetNextCommandPaletteSearchBoxFocused();
IMGUI_API void CommandPalette(const char* name);
IMGUI_API bool IsAnyItemSelected();

IMGUI_API void RemoveCache(const char* name);
IMGUI_API void RemoveAllCaches();

// Command palette widget in a window helper
IMGUI_API void SetNextWindowAffixedTop(ImGuiCond cond = 0);
IMGUI_API void CommandPaletteWindow(const char* name, bool* p_open);

// Command responses, only call these in command callbacks (except TerminatingCallback)
IMGUI_API void Prompt(std::vector<std::string> options);

} // namespace ImCmd
