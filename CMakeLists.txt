cmake_minimum_required(VERSION 3.15)
project(AIS1002-ProsjektOppgave)

include(FetchContent)
FetchContent_Declare(
        catch
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.x
)

FetchContent_MakeAvailable(catch)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(my_app main.cpp include/chessBoardGeometry.h include/chessPiecesGeometry.h include/rules.h)
target_link_libraries(my_app PRIVATE threepp::threepp imgui::imgui assimp::assimp)

add_executable(tests tests/tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2 threepp::threepp)
