#include "ChessboardGeometry.h"
#include "chessPiecesGeometry.h"
#include "threepp/threepp.hpp"
#include "threepp/controls/OrbitControls.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"

using namespace threepp;

int main() {

    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color(0x708090));

    auto camera = PerspectiveCamera::create();
    camera->position.set(0, 10, 5);
    camera->lookAt(Vector3());

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();

    auto chessboard = ChessboardGeometry::create();
    scene->add(chessboard);

    auto directionalLight = DirectionalLight::create(0xffffff, 0.5);
    directionalLight->position.set(1, 1, 1);
    scene->add(directionalLight);

    auto ambientLight = AmbientLight::create(0x404040);
    scene->add(ambientLight);

    auto whiteRook1 = std::make_shared<ChessPiecesGeometry::WhiteRook>();
    whiteRook1->getMesh()->position.set(-6.4, 0.1, -3.5);
    whiteRook1->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteRook1->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whiteRook2 = std::make_shared<ChessPiecesGeometry::WhiteRook>();
    whiteRook2->getMesh()->position.set(0.65, 0.1, -3.5);
    whiteRook2->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteRook2->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whiteKnight1 = std::make_shared<ChessPiecesGeometry::WhiteKnight>();
    whiteKnight1->getMesh()->position.set(3.80, 0.1, -3.5);
    whiteKnight1->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteKnight1->getMesh()->rotation.set(math::PI/-2, 0, math::PI);

    auto whiteKnight2 = std::make_shared<ChessPiecesGeometry::WhiteKnight>();
    whiteKnight2->getMesh()->position.set(0.75, 0.1, -3.5);
    whiteKnight2->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteKnight2->getMesh()->rotation.set(math::PI/-2, 0, math::PI);

    auto whiteBishop1 = std::make_shared<ChessPiecesGeometry::WhiteBishop>();
    whiteBishop1->getMesh()->position.set(-4.20, 0.1, -3.5);
    whiteBishop1->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteBishop1->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whiteBishop2 = std::make_shared<ChessPiecesGeometry::WhiteBishop>();
    whiteBishop2->getMesh()->position.set(0.85, 0.1, -3.5);
    whiteBishop2->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteBishop2->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whiteQueen = std::make_shared<ChessPiecesGeometry::WhiteQueen>();
    whiteQueen->getMesh()->position.set(-1.53, 0.1, -3.5);
    whiteQueen->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteQueen->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whiteKing = std::make_shared<ChessPiecesGeometry::WhiteKing>();
    whiteKing->getMesh()->position.set(0.18, 0.1, -3.5);
    whiteKing->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteKing->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whitePawn1 = std::make_shared<ChessPiecesGeometry::WhitePawn>();
    whitePawn1->getMesh()->position.set(0.10, 0.1, -2.5);
    whitePawn1->getMesh()->scale.set(0.015, 0.015, 0.015);
    whitePawn1->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whitePawn2 = std::make_shared<ChessPiecesGeometry::WhitePawn>();
    whitePawn2->getMesh()->position.set(-0.925, 0.1, -2.5);
    whitePawn2->getMesh()->scale.set(0.015, 0.015, 0.015);
    whitePawn2->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whitePawn3 = std::make_shared<ChessPiecesGeometry::WhitePawn>();
    whitePawn3->getMesh()->position.set(-1.960, 0.1, -2.5);
    whitePawn3->getMesh()->scale.set(0.015, 0.015, 0.015);
    whitePawn3->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whitePawn4 = std::make_shared<ChessPiecesGeometry::WhitePawn>();
    whitePawn4->getMesh()->position.set(-2.95, 0.1, -2.5);
    whitePawn4->getMesh()->scale.set(0.015, 0.015, 0.015);
    whitePawn4->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whitePawn5 = std::make_shared<ChessPiecesGeometry::WhitePawn>();
    whitePawn5->getMesh()->position.set(-3.94, 0.1, -2.5);
    whitePawn5->getMesh()->scale.set(0.015, 0.015, 0.015);
    whitePawn5->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whitePawn6 = std::make_shared<ChessPiecesGeometry::WhitePawn>();
    whitePawn6->getMesh()->position.set(-4.93, 0.1, -2.5);
    whitePawn6->getMesh()->scale.set(0.015, 0.015, 0.015);
    whitePawn6->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whitePawn7 = std::make_shared<ChessPiecesGeometry::WhitePawn>();
    whitePawn7->getMesh()->position.set(-5.95, 0.1, -2.5);
    whitePawn7->getMesh()->scale.set(0.015, 0.015, 0.015);
    whitePawn7->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whitePawn8 = std::make_shared<ChessPiecesGeometry::WhitePawn>();
    whitePawn8->getMesh()->position.set(-6.95, 0.1, -2.5);
    whitePawn8->getMesh()->scale.set(0.015, 0.015, 0.015);
    whitePawn8->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackRook1 = std::make_shared<ChessPiecesGeometry::BlackRook>();
    blackRook1->getMesh()->position.set(-6.4, 0.1, 3.5);
    blackRook1->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackRook1->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackRook2 = std::make_shared<ChessPiecesGeometry::BlackRook>();
    blackRook2->getMesh()->position.set(0.65, 0.1, 3.5);
    blackRook2->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackRook2->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackKnight1 = std::make_shared<ChessPiecesGeometry::BlackKnight>();
    blackKnight1->getMesh()->position.set(-0.75, 0.1, 3.5);
    blackKnight1->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackKnight1->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackKnight2 = std::make_shared<ChessPiecesGeometry::BlackKnight>();
    blackKnight2->getMesh()->position.set(-3.8, 0.1, 3.5);
    blackKnight2->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackKnight2->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackBishop1 = std::make_shared<ChessPiecesGeometry::BlackBishop>();
    blackBishop1->getMesh()->position.set(-4.20, 0.1, 3.5);
    blackBishop1->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackBishop1->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackBishop2 = std::make_shared<ChessPiecesGeometry::BlackBishop>();
    blackBishop2->getMesh()->position.set(0.85, 0.1, 3.5);
    blackBishop2->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackBishop2->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackQueen = std::make_shared<ChessPiecesGeometry::BlackQueen>();
    blackQueen->getMesh()->position.set(-1.53, 0.1, 3.5);
    blackQueen->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackQueen->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackKing = std::make_shared<ChessPiecesGeometry::BlackKing>();
    blackKing->getMesh()->position.set(0.18, 0.1, 3.5);
    blackKing->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackKing->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackPawn1 = std::make_shared<ChessPiecesGeometry::BlackPawn>();
    blackPawn1->getMesh()->position.set(0.10, 0.1, 2.5);
    blackPawn1->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackPawn1->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackPawn2 = std::make_shared<ChessPiecesGeometry::BlackPawn>();
    blackPawn2->getMesh()->position.set(-0.925, 0.1, 2.5);
    blackPawn2->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackPawn2->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackPawn3 = std::make_shared<ChessPiecesGeometry::BlackPawn>();
    blackPawn3->getMesh()->position.set(-1.960, 0.1, 2.5);
    blackPawn3->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackPawn3->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackPawn4 = std::make_shared<ChessPiecesGeometry::BlackPawn>();
    blackPawn4->getMesh()->position.set(-2.95, 0.1, 2.5);
    blackPawn4->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackPawn4->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackPawn5 = std::make_shared<ChessPiecesGeometry::BlackPawn>();
    blackPawn5->getMesh()->position.set(-3.94, 0.1, 2.5);
    blackPawn5->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackPawn5->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackPawn6 = std::make_shared<ChessPiecesGeometry::BlackPawn>();
    blackPawn6->getMesh()->position.set(-4.93, 0.1, 2.5);
    blackPawn6->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackPawn6->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackPawn7 = std::make_shared<ChessPiecesGeometry::BlackPawn>();
    blackPawn7->getMesh()->position.set(-5.95, 0.1, 2.5);
    blackPawn7->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackPawn7->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackPawn8 = std::make_shared<ChessPiecesGeometry::BlackPawn>();
    blackPawn8->getMesh()->position.set(-6.95, 0.1, 2.5);
    blackPawn8->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackPawn8->getMesh()->rotation.set(math::PI/-2, 0, 0);

    scene->add(whiteKing->getMesh());
    scene->add(whiteQueen->getMesh());
    scene->add(whiteRook1->getMesh());
    scene->add(whiteRook2->getMesh());
    scene->add(whiteKnight1->getMesh());
    scene->add(whiteKnight2->getMesh());
    scene->add(whiteBishop1->getMesh());
    scene->add(whiteBishop2->getMesh());
    scene->add(whitePawn1->getMesh());
    scene->add(whitePawn2->getMesh());
    scene->add(whitePawn3->getMesh());
    scene->add(whitePawn4->getMesh());
    scene->add(whitePawn5->getMesh());
    scene->add(whitePawn6->getMesh());
    scene->add(whitePawn7->getMesh());
    scene->add(whitePawn8->getMesh());
    scene->add(blackKing->getMesh());
    scene->add(blackQueen->getMesh());
    scene->add(blackQueen->getMesh());
    scene->add(blackRook1->getMesh());
    scene->add(blackRook2->getMesh());
    scene->add(blackKnight1->getMesh());
    scene->add(blackKnight2->getMesh());
    scene->add(blackBishop1->getMesh());
    scene->add(blackBishop2->getMesh());
    scene->add(blackPawn1->getMesh());
    scene->add(blackPawn2->getMesh());
    scene->add(blackPawn3->getMesh());
    scene->add(blackPawn4->getMesh());
    scene->add(blackPawn5->getMesh());
    scene->add(blackPawn6->getMesh());
    scene->add(blackPawn7->getMesh());
    scene->add(blackPawn8->getMesh());


    imgui_functional_context ui(canvas.window_ptr(), [&] {
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always, ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(230, 0), ImGuiCond_Always);
        ImGui::Begin("Chess Controls");
        controls.enabled = !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
        ImGui::Text("Press ESC to exit");
        ImGui::End();
    });

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&] {
        renderer.render(scene, camera);
        ui.render();
    });

    return 0;
}



