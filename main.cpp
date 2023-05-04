#include "chessPiecesGeometry.h"
#include "controls.h"
#include "threepp/threepp.hpp"
#include "threepp/controls/OrbitControls.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"

using namespace threepp;

//Her legges det til posisjonene for sjakkbrikkene samt at det opprettes en scene med forskjllige kontroll innstillinger
//Det er også inkludert en headeren controls.h for å legge til sjakkbrikke kontrollen
int main() {

    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.checkShaderErrors = true;
    renderer.setClearColor(Color(0x708090));

    auto camera = PerspectiveCamera::create();
    camera->position.set(0, 10, 0);
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

    auto whitePawn1 = std::make_shared<ChessPiecesGeometry::WhitePawn>();
    // Set the name for the white pawn
    whitePawn1->getMesh()->name = "chess_piece_white_pawn_1";
    whitePawn1->getMesh()->position.set(0, 0, -2.5);
    whitePawn1->getMesh()->scale.set(0.015, 0.015, 0.015);
    whitePawn1->getMesh()->rotation.set(math::PI/-2, 0, 0);

// Find the mesh with the corresponding name and add the white pawn mesh as its child
    auto squareMesh = ChessboardGeometry::chessSquares.find("H2")->second;
    squareMesh->add(whitePawn1->getMesh());

// Add the white pawn mesh directly to the scene
    scene->add(whitePawn1->getMesh());


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

        std::string getSquareName(int column, int row) {
            const std::vector<char> columnNames{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
            return std::string(1, columnNames[column]) + std::to_string(8 - row);
        }


        // Modify the constructor to accept scene and camera
        explicit MyListener(std::shared_ptr<Controls> controlsPtr, std::shared_ptr<threepp::Scene> scene, std::shared_ptr<threepp::Camera> camera, std::shared_ptr<Canvas> canvas)
                : controlsPtr(std::move(controlsPtr)), scene_(std::move(scene)), listenerCamera_(std::move(camera)), listenerCanvas_(std::move(canvas)) {
            chessPiecePositions["H2"] = "chess_piece_white_pawn_1";
        }

        void onMouseDown(int button, const Vector2 &pos) override {
            if (button == 0) { // Left mouse button
                controlsPtr->onMouseDown(pos);

                auto normalizedMousePosition = controlsPtr->normalizeMouseCoordinates(pos);
                auto raycaster = std::make_shared<Raycaster>();
                raycaster->setFromCamera(normalizedMousePosition, listenerCamera_);
                auto intersects = raycaster->intersectObjects(scene_->children, true);

                if (!intersects.empty()) {
                    const auto& intersection = intersects.front();
                    processMouseClick(intersection, listenerCamera_, scene_);
                }
            }
        }

        void processMouseClick(const Intersection &intersect, std::shared_ptr<threepp::Camera> &camera_, std::shared_ptr<threepp::Scene> &scene_) {
            std::cout << "Intersected object name: " << intersect.object->name << std::endl;

            const int gridSize = 8;
            const float squareSize = 1.0;
            const float boardStartX = 0.5;
            const float boardStartZ = -3.5;

            // Calculate the index of the intersected square
            int intersectedColumn = static_cast<int>(std::round((intersect.point.x - boardStartX) / squareSize));
            int intersectedRow = static_cast<int>(std::round((intersect.point.z - boardStartZ) / squareSize));
            int intersectedIndex = intersectedRow * gridSize + intersectedColumn;
            std::cout << "Intersected index: " << intersectedIndex << std::endl;

            std::string chessPieceName;

            // Find the chess piece in the chessPiecePositions map
            std::function<void(std::shared_ptr<threepp::Object3D>)> findChessPiece = [this, &chessPieceName](std::shared_ptr<threepp::Object3D> object) mutable {
                auto it = chessPiecePositions.find(object->name);
                if (it != chessPiecePositions.end()) {
                    chessPieceName = it->second;
                }
            };

            auto intersectObjectSharedPtr = std::shared_ptr<threepp::Object3D>(intersect.object, [](threepp::Object3D *) {});
            findChessPiece(intersectObjectSharedPtr);

            std::cout << "Chess piece on the intersected square: " << chessPieceName << std::endl;

            if (!pickedChessPiece) {
                // If there is no picked chess piece, pick up the chess piece on the intersected square
                if (!chessPieceName.empty()) {
                    pickedChessPiece = std::shared_ptr<threepp::Object3D>(scene_->getObjectByName(chessPieceName), [](threepp::Object3D *) {});
                    // Raise the picked chess piece to make it "invisible"
                    pickedChessPiece->position.y += 10;

                    // Remove the picked chess piece from the chessPiecePositions map
                    std::string currentSquare = getSquareName(intersectedColumn, intersectedRow);
                    chessPiecePositions.erase(currentSquare);
                }
            }
            else {
                // If there is a picked chess piece, place it on the intersected square
                float targetX = boardStartX + intersectedColumn * squareSize - 3.5;
                float targetZ = boardStartZ + intersectedRow * squareSize;
                pickedChessPiece->position.x = targetX;
                pickedChessPiece->position.z = targetZ;

                // Lower the picked chess piece back to its original height
                pickedChessPiece->position.y -= 10;

                // Update the chessPiecePositions map
                std::string targetSquare = getSquareName(intersectedColumn, intersectedRow);
                chessPiecePositions[targetSquare] = pickedChessPiece->name;

                // Clear the picked chess piece
                pickedChessPiece.reset();
            }

        }
    };

    Vector2 mouse{-Infinity<float>, -Infinity<float>};
    MouseMoveListener l([&](Vector2 pos) {
        auto size = canvas.getSize();
        mouse.x = (pos.x / static_cast<float>(size.width)) * 2 - 1;
        mouse.y = -(pos.y / static_cast<float>(size.height)) * 2 + 1;
    });

    MyListener k(controlsPtr, scene, camera, std::shared_ptr<Canvas>(&canvas, [](Canvas*){}));
    canvas.addMouseListener(&k);

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