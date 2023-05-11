#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../include/controls.h"
#include "../include/chessBoardGeometry.h"
#include "../include/chessPiecesGeometry.h"
#include "../include/rules.h"
#include <threepp/threepp.hpp>

// Define the stub class directly in this file
class StubPerspectiveCamera : public PerspectiveCamera {
public:
    StubPerspectiveCamera() : PerspectiveCamera(75, 1.0, 0.1, 1000) {
        // You might need to replace 75, 1.0, 0.1, 1000 with the actual default values for your PerspectiveCamera
    }
    // add stubs for any other methods that are in PerspectiveCamera but not in StubPerspectiveCamera
    // for example, if PerspectiveCamera has a method 'zoom', you'd add:
    // void zoom() override {}
};


// Mocking some necessary objects to test the functions
std::shared_ptr<StubPerspectiveCamera> camera = std::make_shared<StubPerspectiveCamera>();
std::shared_ptr<threepp::Scene> scene = std::make_shared<threepp::Scene>();
threepp::Canvas canvas;

TEST_CASE("Controls Class Functionality", "[Controls]") {
    std::shared_ptr<PerspectiveCamera> camera = std::make_shared<StubPerspectiveCamera>();
    Controls controls(camera, canvas, scene);

    SECTION("Normalize Mouse Coordinates") {
        // Assuming the canvas size is 1000x800
        // The center would then be at (500, 400)
        threepp::Vector2 mousePos(500, 400);
        threepp::Vector2 normalized = controls.normalizeMouseCoordinates(mousePos);

        REQUIRE(normalized.x == Approx(0));
        REQUIRE(normalized.y == Approx(0));
    }

    // More test sections for other functions...
}

TEST_CASE("ChessboardGeometry Class Functionality", "[ChessboardGeometry]") {
    auto chessBoard = ChessboardGeometry::create();

    SECTION("Nearest Square Calculation") {
        threepp::Vector3 position(2.3f, 0.f, 3.7f);
        threepp::Vector3 nearest = ChessboardGeometry::getNearestSquare(position);

        // Assuming the square size is 1.0
        REQUIRE(nearest.x == Approx(2.5f));
        REQUIRE(nearest.y == Approx(0.0f));
        REQUIRE(nearest.z == Approx(3.5f));
    }


}

TEST_CASE("A simple test", "[tag]") {
    int a = 2;
    int b = 3;
    REQUIRE(a + b == 5);
}