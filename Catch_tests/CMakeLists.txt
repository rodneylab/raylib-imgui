message(STATUS "Include Catch2")
cpmaddpackage("gh:catchorg/Catch2#fa43b77429ba76c462b1898d6cd2f2d7a9416b14"
)# v3.7.1

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)

add_executable(Catch_tests_run test.cpp)

target_link_libraries(Catch_tests_run PRIVATE raylib_imgui_compiler_flags)
target_link_libraries(Catch_tests_run PRIVATE Catch2::Catch2WithMain)
target_include_directories(Catch_tests_run PUBLIC "${PROJECT_SOURCE_DIR}/src")

include(Catch)
catch_discover_tests(Catch_tests_run)
