cmake_minimum_required(VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Astro Cruiser")

# Poprawiona lista plików źródłowych dla testów
add_executable(AstroCruiserTests gtesty.cpp "Astro Cruiser.h" "button.h" "player.h"  "game.h" "projectile.h" "decay.h" "asteroid.h" "enemy.h" "ufo.h" "Astro Cruiser.cpp" "button.cpp" "player.cpp"  "game.cpp"  "projectile.cpp"  "decay.cpp" "asteroid.cpp" "enemy.cpp"  "ufo.cpp")

# Dodaj pliki źródłowe dla głównego programu
add_executable(AstroCruiser "Astro Cruiser.cpp" "Astro Cruiser.h" "button.cpp" "button.h" "player.h" "player.cpp" "game.h" "game.cpp" "projectile.h" "projectile.cpp" "decay.h" "decay.cpp" "asteroid.h" "asteroid.cpp" "enemy.h" "enemy.cpp" "ufo.h" "ufo.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AstroCruiser PROPERTY CXX_STANDARD 20)
  set_property(TARGET AstroCruiserTests PROPERTY CXX_STANDARD 17)
endif()

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
  # Ustawienie flagi RuntimeLibrary dla Google Test
  CMAKE_ARGS     -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDebugDLL # Dla Debug
  -DBUILD_SHARED_LIBS=ON
  -Dgtest_force_shared_crt=ON
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(AstroCruiser PRIVATE raylib)
# Poprawione linkowanie dla testów
target_link_libraries(AstroCruiserTests PRIVATE raylib gtest gtest_main)

if(EXISTS ${CMAKE_SOURCE_DIR}/textures)
  file(COPY ${CMAKE_SOURCE_DIR}/textures DESTINATION ${CMAKE_BINARY_DIR})
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/sounds)
  file(COPY ${CMAKE_SOURCE_DIR}/sounds DESTINATION ${CMAKE_BINARY_DIR})
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/textures)
  file(COPY ${CMAKE_SOURCE_DIR}/textures DESTINATION ${CMAKE_BINARY_DIR}/tests)
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/sounds)
  file(COPY ${CMAKE_SOURCE_DIR}/sounds DESTINATION ${CMAKE_BINARY_DIR}/tests)
endif()