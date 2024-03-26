//
// Created by nosquad on 12/29/2023.
//

#ifndef BASE_RAYLIB_GAME_PROJECT_GAME_H
#define BASE_RAYLIB_GAME_PROJECT_GAME_H
#include <imgui.h>
#include <raylib.h>
#include <rlImGui.h>

#include <cstdio>
#include <queue>

void draw_scene(const Camera &camera,
                const Vector3 &cube_position,
                const Color &cube_colour,
                const Font &font);
//int Game_GetTickrate();
void Game_Update(std::queue<int> *key_queue, bool *debug_menu);
void Game_Draw();
void Game_DrawDebug(int &selected_cube_colour);

#endif //BASE_RAYLIB_GAME_PROJECT_GAME_H
