#include "constants.h"
#include "game/game.h"

#include <imgui.h>
#include <raylib.h>
#include <rlImGui.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <queue>
#include <string>

void setup_camera(Camera3D &camera)
{
    camera.position = Vector3{constants::kCameraPositionX,
                              constants::kCameraPositionY,
                              constants::kCameraPositionZ};
    constexpr float kCameraTargetX{0.F};
    camera.target = Vector3{kCameraTargetX, 0.F, 0.F};
    camera.up = Vector3{0.F, 1.F, 0.F};
    camera.fovy = constants::kCameraFovY;
    camera.projection = CAMERA_PERSPECTIVE;
}

void update_cube(const float frame_time,
                 const Vector3 &cube_velocity,
                 Vector3 &cube_position)
{
    cube_position = Vector3{cube_position.x + frame_time * cube_velocity.x,
                            cube_position.y + frame_time * cube_velocity.y,
                            cube_position.z + frame_time * cube_velocity.z};
    if (cube_position.z > constants::kCubePositionMaxZ)
    {
        cube_position.z = constants::kCubePositionMinZ;
    }
}

int main()
{
    double tickTimer{0.0};
    std::queue<int> keyQueue = std::queue<int>();
    bool debugMenu = false;
    const Vector2 windowSize{
        Vector2{constants::kWindowWidth, constants::kWindowHeight}};
    RenderTexture gameTexture;
    RenderTexture debugTexture;

    SetWindowState(FLAG_MSAA_4X_HINT);
    InitWindow(static_cast<int>(windowSize.x),
               static_cast<int>(windowSize.y),
               constants::kTitle.c_str());
    rlImGuiSetup(true);

    gameTexture = LoadRenderTexture((int)windowSize.x, (int)windowSize.y);
    constexpr float kDebugScaleUp{1.5F};
    debugTexture =
        LoadRenderTexture(static_cast<int>(windowSize.x / kDebugScaleUp),
                          static_cast<int>(windowSize.y / kDebugScaleUp));

    const Rectangle source_rectangle{0,
                                     -windowSize.y,
                                     windowSize.x,
                                     -windowSize.y};
    const Rectangle destination_rectangle{0,
                                          0,
                                          windowSize.x / kDebugScaleUp,
                                          windowSize.y / kDebugScaleUp};
    Camera3D camera{};
    setup_camera(camera);

    constexpr int kMillisecondsPerSecond{1000};
    Vector3 cube_position{0.F, 0.F, 0.F};
    const Vector3 cube_velocity{Vector3{0.F, 0.F, constants::kCubeSpeed}};
    const Font font{LoadFont(ASSETS_PATH "ibm-plex-mono-v19-latin-500.ttf")};
    int selected_cube_colour{0};

    while (!WindowShouldClose())
    {
        const float frame_time{GetFrameTime()};

        if (GetTime() - tickTimer >
            static_cast<float>(kMillisecondsPerSecond) /
                static_cast<float>(constants::kTickrate) /
                static_cast<float>(kMillisecondsPerSecond))
        {
            tickTimer = GetTime();
            Game_Update(&keyQueue, &debugMenu);
        }

        keyQueue.push(GetKeyPressed());

        BeginDrawing();
        rlImGuiBegin();
        ClearBackground(DARKGRAY);

        if (debugMenu)
        {
            BeginTextureMode(gameTexture);
            ClearBackground(RAYWHITE);
            draw_scene(camera,
                       cube_position,
                       constants::kCubeColours[static_cast<size_t>(
                           selected_cube_colour)],
                       font);
            EndTextureMode();

            BeginTextureMode(debugTexture);
            DrawTexturePro(gameTexture.texture,
                           source_rectangle,
                           destination_rectangle,
                           {0, 0},
                           0.F,
                           RAYWHITE);
            EndTextureMode();

            Game_DrawDebug(selected_cube_colour);

            ImGui::Begin(
                "Game",
                &debugMenu,
                static_cast<uint8_t>( // NOLINT [hicpp-signed-bitwise]
                    ImGuiWindowFlags_AlwaysAutoResize) |
                    static_cast<uint8_t>(ImGuiWindowFlags_NoResize) |
                    static_cast<uint8_t>(ImGuiWindowFlags_NoBackground));
            rlImGuiImageRenderTexture(&debugTexture);
            ImGui::End();
        }
        else
        {
            ClearBackground(RAYWHITE);
            draw_scene(camera,
                       cube_position,
                       constants::kCubeColours[static_cast<size_t>(
                           selected_cube_colour)],
                       font);
        }
        rlImGuiEnd();
        EndDrawing();

        update_cube(frame_time, cube_velocity, cube_position);
    }
    return 0;
}
