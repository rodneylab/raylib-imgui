#include "game.h"

#include "constants.h"

#include <fmt/format.h>
#include <imgui.h>
#include <raylib.h>

#include <queue>
#include <string>

void draw_scene(const Camera &camera,
                const Vector3 &cube_position,
                const Color &cube_colour,
                const Font &font)
{
    BeginMode3D(camera);
    DrawCube(cube_position,
             constants::kCubeSizeLength,
             constants::kCubeSizeLength,
             constants::kCubeSizeLength,
             cube_colour);
    DrawGrid(constants::kGridSlices, constants::kGridSpacing);
    DrawCubeWires(cube_position,
                  constants::kCubeSizeLength,
                  constants::kCubeSizeLength,
                  constants::kCubeSizeLength,
                  DARKGRAY);
    EndMode3D();
    const float kDefaultFontSize{10.F};
    DrawTextEx(font,
               "Press F9 for ImGui debug mode",
               Vector2{constants::kTextPositionX, constants::kTextPositionY},
               static_cast<float>(constants::kTextFontSize),
               static_cast<float>(constants::kTextFontSize) / kDefaultFontSize,
               DARKGRAY);
    DrawFPS(constants::kFPSPositionX, constants::kFPSPositionY);
}

int Game_GetTickrate()
{
    constexpr int kTickrate{128};
    return kTickrate;
}

void Game_Update(std::queue<int> *key_queue, bool *debug_menu)
{
    for (; !key_queue->empty(); key_queue->pop())
    {
        const int key{key_queue->front()};
        if (key == 0)
        {
            continue;
        }
        if (key == KEY_F9)
        {
            *(debug_menu) = !(*debug_menu);
        }
    }
}

void Game_DrawDebug(int &selected_cube_colour)
{
    ImGui::Begin("Game Tests");

    ImGui::Text("%s", // NOLINT [cppcoreguidelines-pro-type-vararg]
                fmt::format("FPS: {}", GetFPS()).c_str());

    if (ImGui::TreeNode("Cube colour"))
    {
        int index{0};
        for (const std::string &colour : constants::kCubeColourLabels)
        {
            ImGui::RadioButton(colour.c_str(), &selected_cube_colour, index);
            ++index;
        }
    }
    ImGui::End();
}
