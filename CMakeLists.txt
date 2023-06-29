cmake_minimum_required(VERSION 3.22)
project(Proj3Tester)

set(CMAKE_CXX_STANDARD 17)

add_executable(Proj3Tester main.cpp runTestVetor.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
include_directories(googletest/include googletest .)
add_executable(test_thash  runTestThash.cpp)
add_executable(test_vetor  runTestVetor.cpp)
target_link_libraries(test_thash gtest gtest_main)
target_link_libraries(test_vetor gtest gtest_main)