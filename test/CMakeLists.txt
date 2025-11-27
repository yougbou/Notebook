cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_FILES
        runAllTests.cpp
)


add_executable(runAllTests ${TEST_FILES})

target_link_libraries(runAllTests ${GTEST_BOTH_LIBRARIES} notebook_lib)



