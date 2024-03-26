<img src="./images/rodneylab-github-raylib-imgui.png" alt="Rodney Lab raylib-imgui Github banner">

<p align="center">
  <a aria-label="Open Rodney Lab site" href="https://rodneylab.com" rel="nofollow noopener noreferrer">
    <img alt="Rodney Lab logo" src="https://rodneylab.com/assets/icon.png" width="60" />
  </a>
</p>
<h1 align="center">
  raylib Dear ImGui
</h1>

# raylib-imgui

CMake project for building a debugging UI for a raylib game using Dear ImGui.
The code accompanies the Rodney Lab
<a aria-label="" href="https://rodneylab.com/using-raylib-with-dear-imgui/">article
on using raylib with Dear ImGui</a>, which provides some pointers on setting up
your debugging interface. If you have any questions, please drop a comment at
the bottom of that page.

## Usage

Requires [CMake](https://cmake.org/getting-started/) and a C++ compiler.

Clone the repo then run:

```shell
cmake . -B build
cmake --build build
./build/bin/RaylibImGuiApp
```

With the game running, press the <kbd>F9</kbd> key to bring up the debug
interface and close the preview, or use <kbd>F9</kbd> again to close it.

## Issues

Feel free to jump into the
[Rodney Lab matrix chat room](https://matrix.to/#/%23rodney:matrix.org).
