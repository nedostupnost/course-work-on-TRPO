cmake_minimum_required(VERSION 3.10)
project(15Puzzle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)
include_directories(${PROJECT_SOURCE_DIR}/src/main)
include_directories(${PROJECT_SOURCE_DIR}/test)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/lib/drawer.cpp
    ${PROJECT_SOURCE_DIR}/src/lib/grid.cpp
    ${PROJECT_SOURCE_DIR}/src/lib/links.cpp
    ${PROJECT_SOURCE_DIR}/src/lib/logic.cpp
    ${PROJECT_SOURCE_DIR}/src/main/main.cpp
)

add_executable(15Puzzle ${SOURCES})

target_link_libraries(15Puzzle sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

set(TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/src/lib/drawer.cpp
    ${PROJECT_SOURCE_DIR}/src/lib/grid.cpp
    ${PROJECT_SOURCE_DIR}/src/lib/links.cpp
    ${PROJECT_SOURCE_DIR}/src/lib/logic.cpp
    ${PROJECT_SOURCE_DIR}/test/main.cpp
    ${PROJECT_SOURCE_DIR}/test/test.cpp
)

add_executable(RunTests ${TEST_SOURCES})

target_link_libraries(RunTests sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

enable_testing()

add_test(NAME RunTests COMMAND RunTests)
