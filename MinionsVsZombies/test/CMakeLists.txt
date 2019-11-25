cmake_minimum_required(VERSION 3.12)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing -Wno-int-to-pointer-cast")
set(CMAKE_VERBOSE_MAKEFILE on)

project(Unittest_MinionsVsZombies)
enable_testing()

SET(GTEST_LIBRARY "$ENV{GTEST_DIR}")

# reset linker flags; ARM + GTest doesn't work
SET(CMAKE_EXE_LINKER_FLAGS "${BASE_CMAKE_LINK_FLAGS}")
SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_CXX_COMPILER g++)

add_definitions(-DCODE_COMPILED_AS_PART_OF_TEST)

include_directories(${GTEST_LIBRARY}/include)
include_directories(../engine/include)

# compile including library source because it's cross-compiled
add_executable(unittest_MinionsVsZombies
        main.cpp
        TestFile.cpp)

target_link_libraries(unittest_MinionsVsZombies ${GTEST_LIBRARY}/build/libgtest.a ${GTEST_LIBRARY}/build/libgtest_main.a pthread)
