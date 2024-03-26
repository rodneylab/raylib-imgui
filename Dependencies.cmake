include(cmake/CPM.cmake)

function(raylib_imgui_setup_dependencies)
    message(STATUS "Include Dear ImGui")
    FetchContent_Declare(
        ImGui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG 277ae93c41314ba5f4c7444f37c4319cdf07e8cf) # v1.90.4
    FetchContent_MakeAvailable(ImGui)
    FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

    add_library(
        imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp)
    target_include_directories(imgui INTERFACE ${imgui_SOURCE_DIR})

    include(cmake/CPM.cmake)

    message(STATUS "Include dbg-macro")
    cpmaddpackage(
        "gh:sharkdp/dbg-macro#fb9976f410f8b29105818b20278cd0be0e853fe8"
    )# v0.5.1

    message(STATUS "Include fmtlib")
    cpmaddpackage("gh:fmtlib/fmt#e69e5f977d458f2650bb346dadf2ad30c5320281"
    )# 10.x

    message(STATUS "Include raylib")
    cpmaddpackage("gh:raysan5/raylib#ae50bfa2cc569c0f8d5bc4315d39db64005b1b0"
    )# v5.0

    message(STATUS "Include spdlog")
    cpmaddpackage("gh:gabime/spdlog#7c02e204c92545f869e2f04edaab1f19fe8b19fd"
    )# v1.13.0

    message(STATUS "Include rlImGui")
    FetchContent_Declare(
        rlImGui
        GIT_REPOSITORY https://github.com/raylib-extras/rlImGui
        GIT_TAG d765c1ef3d37cf939f88aaa272a59a2713d654c9)
    FetchContent_MakeAvailable(rlImGui)
    FetchContent_GetProperties(rlImGui SOURCE_DIR RLIMGUI_DIR)
    add_library(rlimgui STATIC ${rlimgui_SOURCE_DIR}/rlImGui.cpp)
    target_link_libraries(rlimgui PRIVATE imgui raylib)
    if(APPLE)
        target_link_libraries(rlimgui PUBLIC "-framework IOKit")
        target_link_libraries(rlimgui PUBLIC "-framework Cocoa")
        target_link_libraries(rlimgui PUBLIC "-framework OpenGL")
    endif()
    target_include_directories(rlimgui INTERFACE ${rlimgui_SOURCE_DIR})
endfunction()
