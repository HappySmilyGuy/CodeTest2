include_directories(${gtest_SOUCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runTests tests.cpp )

target_link_libraries(runTests gtest gtest_main)
