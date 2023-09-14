# Pendulum Simulation Project

This project uses C++ and the Simple and Fast Media Library SFML for graphics. To minimize the barriers to entry for those of you that would like to join the project, this project is based on the SFML GitHub template: https://github.com/SFML/cmake-sfml-project

The template included:

- Basic CMake script to build your project and link SFML on any operating system. If you don't know what that is, it should be okay. If you run into issues, though, reach out!
- Basic [GitHub Actions](https://github.com/features/actions) script for all major platforms. (Not important for us).

## How to Use
(changed slightly from template readme)

1. To join this project, clone the repository to your machine. I recommend using visual studio or visual studio code to write your code, but whichever IDE you select should be okay.
1. To make changes, be sure to follow the proper git/github etiquette laid out in the video I shared in teams.
1. If you want to add or remove any .cpp files, change the source files listed in the [`add_executable`](CMakeLists.txt#L10) call in CMakeLists.txt to match the source files your project requires. If you plan on keeping the default main.cpp file then no changes are required.
1. Configure and build your project. Most popular IDEs support CMake projects with very little effort on your part.
    - [VS Code](https://code.visualstudio.com) via the [CMake extension](https://code.visualstudio.com/docs/cpp/cmake-linux)
    - [Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170)
    - [CLion](https://www.jetbrains.com/clion/features/cmake-support.html)
    - [Qt Creator](https://doc.qt.io/qtcreator/creator-project-cmake.html)

    Using CMake from the command line is straightforward as well.

    For a single-configuration generator (typically the case on Linux and macOS):
    ```
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ```

    For a multi-configuration generator (typically the case on Windows):
    ```
    cmake -S . -B build
    cmake --build build --config Release
    ```
1. Enjoy!

### To Change Compilers 
(kept from the template readme)

See the variety of [`CMAKE_<LANG>_COMPILER`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER.html) options.
In particular you'll want to modify `CMAKE_CXX_COMPILER` to point to the C++ compiler you wish to use.
