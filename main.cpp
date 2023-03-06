#include <memory>
#include "threepp/threepp.hpp"
#include "chessBoardGeometry.h"
#include "chessPiecesGeometry.h"

int main(int argc, char **argv) {
    // Create the canvas and renderer
    auto canvas = std::make_shared<threepp::Canvas>();
    auto renderer = std::make_shared<threepp::GLRenderer>(canvas);

    // Create the camera
    auto camera = threepp::PerspectiveCamera::create(75, canvas->getAspect(), 0.1, 100);
    camera->position.z = 10;

    // Create the chessboard and pawn
    auto chessboard = std::make_shared<Chessboard>(canvas, renderer, camera);
    auto pawn = ChessPiecesGeometry::createPawn();
    pawn->setPosition(0, 0.5, 0);

    // Add the pawn to the scene
    chessboard->scene().add(pawn->getMesh());

    // Run the animation loop
    canvas->animate([&] {
        // Rotate the pawn
        pawn->getMesh()->rotation.y += 0.01;

        // Render the scene
        renderer->render(chessboard->getScene(), camera);
    });

    return 0;
}
