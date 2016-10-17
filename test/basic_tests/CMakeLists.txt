include_directories(${gtest_SOUCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBasicCubeTests CubeTests.cpp
                ../../src/Cube.cpp)

target_link_libraries(runBasicCubeTests gtest gtest_main)