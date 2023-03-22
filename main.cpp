#include "example.h"
#include "chessBoardGeometry.h"
#include "Mouse.h"

using namespace threepp;
int main() {

    auto canvas = std::make_shared<Canvas>();
    auto renderer = std::make_shared<GLRenderer>(*canvas);
    renderer->setClearColor(Color::gray);

    auto camera = PerspectiveCamera::create();
    camera->position.y = 5;
    camera->position.z = 10;


    auto chessboard = std::make_unique<Chessboard>(std::move(canvas), std::move(renderer), std::move(camera));


    return 0;
}