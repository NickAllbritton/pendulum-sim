cmake_minimum_required(VERSION 3.16)
project(PendulumSim LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(pendulum src/main.cpp src/Simulation.cpp src/Menu.cpp src/World.cpp src/Button.cpp src/Pendulum.cpp src/Physics.cpp src/FrameTimer.cpp src/Indicator.cpp src/Graph.cpp)
target_link_libraries(pendulum PRIVATE sfml-graphics)
target_compile_features(pendulum PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET pendulum
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<BOOL:${ARCH_64BITS}>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:pendulum>
        VERBATIM)
endif()

install(TARGETS pendulum)
