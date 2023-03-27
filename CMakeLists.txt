cmake_minimum_required(VERSION 3.15)
project(AIS1002-ProsjektOppgave)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

add_executable(test main.cpp chessBoardGeometry.h chessPiecesGeometry.h controls.h gameplay.h gameplay.cpp)
target_link_libraries(test PRIVATE threepp::threepp imgui::imgui assimp::assimp)
