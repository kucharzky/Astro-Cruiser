add_executable(AstroCruiserTests "gtesty.cpp")

target_include_directories(AstroCruiserTests PRIVATE ${CMAKE_SOURCE_DIR})

target_include_directories(AstroCruiserTests PRIVATE ${RAYLIB_INCLUDE_DIR})

target_link_libraries(AstroCruiserTests PRIVATE AstroCruiserLib raylib gtest gtest_main)