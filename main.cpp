#include "chessPiecesGeometry.h"
#include "controls.h"
#include "rules.h"
#include <threepp/threepp.hpp>
#include <threepp/controls/OrbitControls.hpp>
#include <threepp/extras/imgui/imgui_context.hpp>

using namespace threepp;

//Her legges det til posisjonene for sjakkbrikkene samt at det opprettes en scene med forskjllige kontroll innstillinger
//Det er også inkludert en headeren controls.h for å legge til sjakkbrikke kontrollen
int main() {

    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.checkShaderErrors = true;
    renderer.setClearColor(Color(0x708090));

    auto camera = PerspectiveCamera::create();
    camera->position.set(0, 12, 0);
    camera->layers.enableAll();

    auto scene = Scene::create();

    camera->lookAt(scene->position);
    camera->updateProjectionMatrix();

    OrbitControls controls(camera, canvas);
    controls.enablePan = false;
    controls.enableZoom = true;
    controls.enableRotate = true;

    auto chessboard = ChessboardGeometry::create();
    chessboard->name = "chessboard";
    scene->add(chessboard);

    auto directionalLight = DirectionalLight::create(0xffffff, 0.5);
    directionalLight->position.set(1, 1, 1);
    scene->add(directionalLight);
    auto ambientLight = AmbientLight::create(0x404040);
    scene->add(ambientLight);
    auto controlsPtr = std::make_shared<Controls>(camera, canvas, scene);

    imgui_functional_context ui(canvas.window_ptr(), [&] {
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always, ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(230, 0), ImGuiCond_Always);
        ImGui::Begin("Chess Controls");
        ImGui::Text("Press ESC to exit");
        ImGui::End();
    });

    struct MyListener : MouseListener {

        std::map<std::string, std::string> chessPiecePositions;
        std::shared_ptr<Controls> controlsPtr;
        std::shared_ptr<threepp::Scene> scene_;
        std::shared_ptr<threepp::Camera> listenerCamera_;
        std::shared_ptr<Canvas> listenerCanvas_;
        std::shared_ptr<threepp::Object3D> pickedChessPiece;
        std::string initialSquare;
        std::shared_ptr<threepp::Object3D> chessboard;


        std::string getSquareName(int column, int row) {
            const std::vector<char> columnNames{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
            return std::string(1, columnNames[column]) + std::to_string(8 - row);
        }

        // Modify the constructor to accept scene and camera
        explicit MyListener(std::shared_ptr<Controls> controlsPtr, std::shared_ptr<threepp::Scene> scene,
                            std::shared_ptr<threepp::Camera> camera, std::shared_ptr<Canvas> canvas)
                : controlsPtr(std::move(controlsPtr)), scene_(std::move(scene)), listenerCamera_(std::move(camera)),
                  listenerCanvas_(std::move(canvas)) {
            chessPiecePositions["H2"] = "chess_piece_white_pawn_1"; chessPiecePositions["G2"] = "chess_piece_white_pawn_2";
            chessPiecePositions["F2"] = "chess_piece_white_pawn_3"; chessPiecePositions["E2"] = "chess_piece_white_pawn_4";
            chessPiecePositions["D2"] = "chess_piece_white_pawn_5"; chessPiecePositions["C2"] = "chess_piece_white_pawn_6";
            chessPiecePositions["B2"] = "chess_piece_white_pawn_7"; chessPiecePositions["A2"] = "chess_piece_white_pawn_8";
            chessPiecePositions["A1"] = "chess_piece_white_rook_1"; chessPiecePositions["B1"] = "chess_piece_white_bishop_1";
            chessPiecePositions["C1"] = "chess_piece_white_knight_2"; chessPiecePositions["D1"] = "chess_piece_white_king";
            chessPiecePositions["E1"] = "chess_piece_white_queen"; chessPiecePositions["F1"] = "chess_piece_white_knight_1";
            chessPiecePositions["G1"] = "chess_piece_white_bishop_2"; chessPiecePositions["H1"] = "chess_piece_white_rook_2";

            chessPiecePositions["A8"] = "chess_piece_black_rook_1";
            chessPiecePositions["B8"] = "chess_piece_black_bishop_1"; chessPiecePositions["C8"] = "chess_piece_black_knight_2";
            chessPiecePositions["D8"] = "chess_piece_black_king"; chessPiecePositions["E8"] = "chess_piece_black_queen";
            chessPiecePositions["F8"] = "chess_piece_black_knight_1"; chessPiecePositions["G8"] = "chess_piece_black_bishop_2";
            chessPiecePositions["H8"] = "chess_piece_black_rook_2"; chessPiecePositions["H7"] = "chess_piece_black_pawn_1";
            chessPiecePositions["G7"] = "chess_piece_black_pawn_2"; chessPiecePositions["F7"] = "chess_piece_black_pawn_3";
            chessPiecePositions["E7"] = "chess_piece_black_pawn_4"; chessPiecePositions["D7"] = "chess_piece_black_pawn_5";
            chessPiecePositions["C7"] = "chess_piece_black_pawn_6"; chessPiecePositions["B7"] = "chess_piece_black_pawn_7";
            chessPiecePositions["A7"] = "chess_piece_black_pawn_8";
        }

        void onMouseDown(int button, const Vector2 &pos) override {
            if (button == 0) { // Left mouse button
                controlsPtr->onMouseDown(pos);

                auto normalizedMousePosition = controlsPtr->normalizeMouseCoordinates(pos);
                auto raycaster = std::make_shared<Raycaster>();
                raycaster->setFromCamera(normalizedMousePosition, listenerCamera_);
                auto intersects = raycaster->intersectObjects(scene_->children, true);

                std::sort(intersects.begin(), intersects.end(), [](const Intersection &a, const Intersection &b) {
                    return a.distance < b.distance;
                });

                if (!intersects.empty()) {
                    const auto &intersection = intersects.front();

                    // Only process mouse click on chess squares or chess pieces
                    if (ChessboardGeometry::chessSquares.find(intersection.object->name) != ChessboardGeometry::chessSquares.end() ||
                        chessPiecePositions.find(intersection.object->name) != chessPiecePositions.end()) {
                        processMouseClick(intersection, listenerCamera_, scene_);
                    }
                } else {
                    // Deselect the picked chess piece if clicking outside the board
                    if (pickedChessPiece) {
                        pickedChessPiece->position.y -= 50;
                        pickedChessPiece.reset();
                    }
                }
            }
        }

        void processMouseClick(const Intersection &intersect, std::shared_ptr<threepp::Camera> &camera_,
                               std::shared_ptr<threepp::Scene> &scene_) {

            std::cout << "Intersected object name: " << intersect.object->name << std::endl;
            const float squareSize = 1.0;
            const float boardStartX = 0.5;
            const float boardStartZ = -3.5;

            // Calculate the index of the intersected square
            int intersectedColumn = static_cast<int>(std::round((intersect.point.x - boardStartX) / squareSize));
            int intersectedRow = static_cast<int>(std::round((intersect.point.z - boardStartZ) / squareSize));

            // Get the name of the square
            std::string squareName = getSquareName(intersectedColumn, intersectedRow);

            // Check if the intersected object is a chess piece
            if (chessPiecePositions.find(intersect.object->name) != chessPiecePositions.end()) {
                squareName = intersect.object->name;
            }

            // Find the chess piece on the intersected square
            auto it = chessPiecePositions.find(squareName);
            std::string chessPieceName;
            if (it != chessPiecePositions.end()) {
                chessPieceName = it->second;
            }

            // Find the chess piece in the chessPiecePositions map
            std::function<void(std::shared_ptr<threepp::Object3D>)> findChessPiece = [this, &chessPieceName](
                    std::shared_ptr<threepp::Object3D> object) mutable {
                while (object) {
                    auto it = chessPiecePositions.find(object->name);
                    if (it != chessPiecePositions.end()) {
                        chessPieceName = it->second;
                        break;
                    }
                    object = std::shared_ptr<threepp::Object3D>(object->parent, [](threepp::Object3D*) {});
                }
            };

            auto intersectObjectSharedPtr = std::shared_ptr<threepp::Object3D>(intersect.object,
                                                                               [](threepp::Object3D *) {});
            findChessPiece(intersectObjectSharedPtr);
            std::cout << "Chess piece on the intersected square: " << chessPieceName << std::endl;
            if (!pickedChessPiece) {

                // If there is no picked chess piece, pick up the chess piece on the intersected square
                if (!chessPieceName.empty()) {
                    pickedChessPiece = std::shared_ptr<threepp::Object3D>(scene_->getObjectByName(chessPieceName),
                                                                          [](threepp::Object3D *) {});
                    // Raise the picked chess piece to make it "invisible"
                    pickedChessPiece->position.y += 50;

                    // Remember the initial square of the picked chess piece
                    initialSquare = intersect.object->name;
                }

            } else {
                std::string targetSquare = getSquareName(intersectedColumn, intersectedRow);

                // If there is a picked chess piece and it's not the same square, place it on the intersected square
                if (pickedChessPiece->name != chessPieceName) {
                    float targetX = boardStartX + intersectedColumn * squareSize - 3.5;
                    float targetZ = boardStartZ + intersectedRow * squareSize;

                    // Apply the offset for bishops, knights, and kings
                    if (pickedChessPiece->name == "chess_piece_black_bishop_1" ||
                        pickedChessPiece->name == "chess_piece_black_bishop_2" ||
                        pickedChessPiece->name == "chess_piece_white_bishop_1" ||
                        pickedChessPiece->name == "chess_piece_white_bishop_2") {
                        targetX += 1.825;
                    } else if (pickedChessPiece->name == "chess_piece_black_knight_1" ||
                               pickedChessPiece->name == "chess_piece_black_knight_2"){
                        targetX += 1.25;
                    } else if (pickedChessPiece->name == "chess_piece_white_knight_1" || pickedChessPiece->name == "chess_piece_white_knight_2") {
                        targetX += 5.75;
                    } else if (pickedChessPiece->name == "chess_piece_black_king" || pickedChessPiece->name == "chess_piece_white_king") {
                        targetX += 2.46;
                    } else if (pickedChessPiece->name == "chess_piece_black_rook_1" || pickedChessPiece->name == "chess_piece_black_rook_2" ||
                               pickedChessPiece->name == "chess_piece_white_rook_1" || pickedChessPiece->name == "chess_piece_white_rook_2") {
                        targetX += 0.625;
                    } else if (pickedChessPiece->name == "chess_piece_black_queen" || pickedChessPiece->name == "chess_piece_white_queen") {
                        targetX += 3.14;
                    }

                    pickedChessPiece->position.x = targetX;
                    pickedChessPiece->position.z = targetZ;

                    // Lower the picked chess piece back to its original height
                    pickedChessPiece->position.y -= 50;

                    // Update the chessPiecePositions map
                    if (!chessPieceName.empty()) {
                        chessPiecePositions.erase(targetSquare); // Remove the chess piece at the target
                        scene_->remove(scene_->getObjectByName(chessPieceName)); // Remove the captured piece from the scene
                    }

                    chessPiecePositions[targetSquare] = pickedChessPiece->name;

                    // Remove the picked chess piece from its old position in the map
                    if (initialSquare != targetSquare) {
                        chessPiecePositions.erase(initialSquare);
                    }
                    // Clear the picked chess piece and initial square
                    pickedChessPiece.reset();
                    initialSquare = "";
                }
            }
        }
    };

    auto myListener = std::make_shared<MyListener>(controlsPtr, scene, camera, std::shared_ptr<Canvas>(&canvas, [](Canvas*){}));
    canvas.addMouseListener(myListener.get());

    for (int i = 0; i < 8; ++i) {
        auto whitePawn = std::make_shared<ChessPiecesGeometry::WhitePawn>();
        whitePawn->getMesh()->name = "chess_piece_white_pawn_" + std::to_string(i + 1);
        whitePawn->getMesh()->position.set(0.0f - i, 0, -2.5);
        whitePawn->getMesh()->scale.set(0.015, 0.015, 0.015);
        whitePawn->getMesh()->rotation.set(math::PI / -2, 0, 0);
        scene->add(whitePawn->getMesh());
    }

    for (int i = 0; i < 8; ++i) {
        auto blackPawn = std::make_shared<ChessPiecesGeometry::BlackPawn>();
        blackPawn->getMesh()->name = "chess_piece_black_pawn_" + std::to_string(i + 1);
        blackPawn->getMesh()->position.set(0.0f - i, 0, 2.5);
        blackPawn->getMesh()->scale.set(0.015, 0.015, 0.015);
        blackPawn->getMesh()->rotation.set(math::PI / -2, 0, 0);
        scene->add(blackPawn->getMesh());
    }

    auto whiteRook1 = std::make_shared<ChessPiecesGeometry::WhiteRook>();
    whiteRook1->getMesh()->name = "chess_piece_white_rook_1";
    whiteRook1->getMesh()->position.set(-6.4, 0.1, -3.5);
    whiteRook1->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteRook1->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whiteRook2 = std::make_shared<ChessPiecesGeometry::WhiteRook>();
    whiteRook2->getMesh()->name = "chess_piece_white_rook_2";
    whiteRook2->getMesh()->position.set(0.65, 0.1, -3.5);
    whiteRook2->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteRook2->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whiteKnight1 = std::make_shared<ChessPiecesGeometry::WhiteKnight>();
    whiteKnight1->getMesh()->name = "chess_piece_white_knight_1";
    whiteKnight1->getMesh()->position.set(3.80, 0.1, -3.5);
    whiteKnight1->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteKnight1->getMesh()->rotation.set(math::PI/-2, 0, math::PI);

    auto whiteKnight2 = std::make_shared<ChessPiecesGeometry::WhiteKnight>();
    whiteKnight2->getMesh()->name = "chess_piece_white_knight_2";
    whiteKnight2->getMesh()->position.set(0.75, 0.1, -3.5);
    whiteKnight2->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteKnight2->getMesh()->rotation.set(math::PI/-2, 0, math::PI);

    auto whiteBishop1 = std::make_shared<ChessPiecesGeometry::WhiteBishop>();
    whiteBishop1->getMesh()->name = "chess_piece_white_bishop_1";
    whiteBishop1->getMesh()->position.set(-4.20, 0.1, -3.5);
    whiteBishop1->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteBishop1->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whiteBishop2 = std::make_shared<ChessPiecesGeometry::WhiteBishop>();
    whiteBishop2->getMesh()->name = "chess_piece_white_bishop_2";
    whiteBishop2->getMesh()->position.set(0.85, 0.1, -3.5);
    whiteBishop2->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteBishop2->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whiteQueen = std::make_shared<ChessPiecesGeometry::WhiteQueen>();
    whiteQueen->getMesh()->name = "chess_piece_white_queen";
    whiteQueen->getMesh()->position.set(0.18, 0.1, -3.5);
    whiteQueen->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteQueen->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto whiteKing = std::make_shared<ChessPiecesGeometry::WhiteKing>();
    whiteKing->getMesh()->name = "chess_piece_white_king";
    whiteKing->getMesh()->position.set(-1.55, 0.1, -3.5);
    whiteKing->getMesh()->scale.set(0.015, 0.015, 0.015);
    whiteKing->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackRook1 = std::make_shared<ChessPiecesGeometry::BlackRook>();
    blackRook1->getMesh()->name = "chess_piece_black_rook_1";
    blackRook1->getMesh()->position.set(-6.4, 0.1, 3.5);
    blackRook1->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackRook1->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackRook2 = std::make_shared<ChessPiecesGeometry::BlackRook>();
    blackRook2->getMesh()->name = "chess_piece_black_rook_2";
    blackRook2->getMesh()->position.set(0.65, 0.1, 3.5);
    blackRook2->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackRook2->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackKnight1 = std::make_shared<ChessPiecesGeometry::BlackKnight>();
    blackKnight1->getMesh()->name = "chess_piece_black_knight_1";
    blackKnight1->getMesh()->position.set(-0.75, 0.1, 3.5);
    blackKnight1->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackKnight1->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackKnight2 = std::make_shared<ChessPiecesGeometry::BlackKnight>();
    blackKnight2->getMesh()->name = "chess_piece_black_knight_2";
    blackKnight2->getMesh()->position.set(-3.8, 0.1, 3.5);
    blackKnight2->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackKnight2->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackBishop1 = std::make_shared<ChessPiecesGeometry::BlackBishop>();
    blackBishop1->getMesh()->name = "chess_piece_black_bishop_1";
    blackBishop1->getMesh()->position.set(-4.20, 0.1, 3.5);
    blackBishop1->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackBishop1->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackBishop2 = std::make_shared<ChessPiecesGeometry::BlackBishop>();
    blackBishop2->getMesh()->name = "chess_piece_black_bishop_2";
    blackBishop2->getMesh()->position.set(0.85, 0.1, 3.5);
    blackBishop2->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackBishop2->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackQueen = std::make_shared<ChessPiecesGeometry::BlackQueen>();
    blackQueen->getMesh()->name = "chess_piece_black_queen";
    blackQueen->getMesh()->position.set(0.18, 0.1, 3.5);
    blackQueen->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackQueen->getMesh()->rotation.set(math::PI/-2, 0, 0);

    auto blackKing = std::make_shared<ChessPiecesGeometry::BlackKing>();
    blackKing->getMesh()->name = "chess_piece_black_king";
    blackKing->getMesh()->position.set(-1.55, 0.1, 3.5);
    blackKing->getMesh()->scale.set(0.015, 0.015, 0.015);
    blackKing->getMesh()->rotation.set(math::PI/-2, 0, 0);

    scene->add(blackKing->getMesh());
    scene->add(blackQueen->getMesh());
    scene->add(blackRook1->getMesh());
    scene->add(blackRook2->getMesh());
    scene->add(blackKnight1->getMesh());
    scene->add(blackKnight2->getMesh());
    scene->add(blackBishop1->getMesh());
    scene->add(blackBishop2->getMesh());
    scene->add(whiteRook1->getMesh());
    scene->add(whiteRook2->getMesh());
    scene->add(whiteKnight1->getMesh());
    scene->add(whiteKnight2->getMesh());
    scene->add(whiteBishop1->getMesh());
    scene->add(whiteBishop2->getMesh());
    scene->add(whiteKing->getMesh());
    scene->add(whiteQueen->getMesh());


    Vector2 mouse{-Infinity<float>, -Infinity<float>};
    MouseMoveListener l([&](Vector2 pos) {
        auto size = canvas.getSize();
        mouse.x = (pos.x / static_cast<float>(size.width)) * 2 - 1;
        mouse.y = -(pos.y / static_cast<float>(size.height)) * 2 + 1;
    });

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&] {
        controlsPtr->update();
        controls.update();
        renderer.render(scene, camera);
    });

    return 0;
}