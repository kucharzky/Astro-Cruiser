# CMakeList.txt : CMake project for Astro Cruiser, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Astro Cruiser")

# Add source to this project's executable.
add_executable(AstroCruiser "Astro Cruiser.cpp" "Astro Cruiser.h" "button.cpp" "button.h" "player.h" "player.cpp" "game.h" "game.cpp" "projectile.h" "projectile.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AstroCruiser PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(raylib)

# Link the raylib library to the AstroCruiser executable.
target_link_libraries(AstroCruiser PRIVATE raylib)
file(COPY ${CMAKE_SOURCE_DIR}/txts DESTINATION ${CMAKE_BINARY_DIR})