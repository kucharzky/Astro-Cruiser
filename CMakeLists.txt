cmake_minimum_required(VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Astro Cruiser")

# Poprawiona lista plików źródłowych dla testów
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MDd")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(tests)
# Dodaj pliki źródłowe dla głównego programu
add_library(AstroCruiserLib "button.cpp" "button.h" "player.h" "player.cpp" "game.h" "game.cpp" "projectile.h" "projectile.cpp" "decay.h" "decay.cpp" "asteroid.h" "asteroid.cpp" "enemy.h" "enemy.cpp" "ufo.h" "ufo.cpp")
add_executable(AstroCruiser "Astro Cruiser.cpp" "Astro Cruiser.h")
target_link_libraries(AstroCruiser PRIVATE AstroCruiserLib)

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_SHALLOW TRUE
)
FetchContent_GetProperties(raylib)
if(NOT raylib_POPULATED)
    FetchContent_Populate(raylib)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Znajdź katalog nagłówkowy raylib
find_path(RAYLIB_INCLUDE_DIR raylib.h HINTS ${raylib_SOURCE_DIR}/src)

# Dodaj katalog nagłówkowy raylib do ścieżek dla AstroCruiser
target_include_directories(AstroCruiser PRIVATE ${RAYLIB_INCLUDE_DIR})
# Dodaj katalog nagłówkowy raylib do ścieżek dla AstroCruiserLib
target_include_directories(AstroCruiserLib PUBLIC ${RAYLIB_INCLUDE_DIR})
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(AstroCruiser PRIVATE raylib)
# Poprawione linkowanie dla testów

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