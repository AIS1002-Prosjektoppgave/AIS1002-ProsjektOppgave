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
    whitePawn1->getMesh()->position.set(3.5, 0, -2.5);
    whitePawn1->getMesh()->scale.set(0.015, 0.015, 0.015);
    whitePawn1->getMesh()->rotation.set(math::PI/-2, 0, 0);

// Find the mesh with the corresponding name and add the white pawn mesh as its child
// Remove these lines
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
        std::shared_ptr<Controls> controlsPtr;
        std::shared_ptr<threepp::Scene> scene_;
        std::shared_ptr<threepp::Camera> listenerCamera_;

        // Modify the constructor to accept scene and camera
        explicit MyListener(std::shared_ptr<Controls> controlsPtr, std::shared_ptr<threepp::Scene> scene, std::shared_ptr<threepp::Camera> camera)
                : controlsPtr(std::move(controlsPtr)), scene_(std::move(scene)), listenerCamera_(std::move(camera)) {}

        void onMouseDown(int button, const Vector2 &pos) override {
            if (button == 0) { // Left mouse button
                controlsPtr->onMouseDown(pos);

                // New code snippet
                Raycaster raycaster;
                raycaster.setFromCamera(pos, listenerCamera_);

                std::vector<Intersection> intersects = raycaster.intersectObjects(scene_->children, true);

                if (!intersects.empty()) {
                    processMouseClick(intersects[0], listenerCamera_, scene_);
                }
            }
        };

// Moved onMouseClick function definition outside of onMouseDown
        void processMouseClick(Intersection &intersect, std::shared_ptr<threepp::Camera> &camera_, std::shared_ptr<threepp::Scene> &scene_) {
            std::cout << "Intersected object name: " << intersect.object->name << std::endl;

            const int gridSize = 8;
            const float squareSize = 1.0;
            const float boardStartX = 0.5;
            const float boardStartZ = -3.5;

            // Calculate the index of the intersected square
            int intersectedColumn = static_cast<int>((intersect.point.x - boardStartX) / squareSize);
            int intersectedRow = static_cast<int>((intersect.point.z - boardStartZ) / squareSize);
            int intersectedIndex = intersectedRow * gridSize + intersectedColumn;

            std::string chessPieceName;

            // Find the chess piece on the board
            for (const auto &object : scene_->children) {
                if (auto mesh = dynamic_cast<threepp::Mesh *>(object.get())) {
                    if (mesh->name.find("chess_piece") != std::string::npos) {
                        int pieceColumn = static_cast<int>((mesh->position.x - boardStartX) / squareSize);
                        int pieceRow = static_cast<int>((mesh->position.z - boardStartZ) / squareSize);
                        int pieceIndex = pieceRow * gridSize + pieceColumn;

                        if (pieceIndex == intersectedIndex) {
                            chessPieceName = mesh->name;
                            break;
                        }
                    }
                }
            }

            std::cout << "Chess piece on the intersected square: " << chessPieceName << std::endl;
        }


        explicit MyListener(std::shared_ptr<Controls> controlsPtr) : controlsPtr(std::move(controlsPtr)) {}


        void onMouseUp(int button, const Vector2 &pos) override {
            if (button != 0) { // Ventre mus knapp
                controlsPtr->onMouseUp();
            }
        }

        void onMouseMove(const Vector2 &pos) override {
            controlsPtr->onMouseMove(pos);
        }
    };

    Vector2 mouse{-Infinity<float>, -Infinity<float>};
    MouseMoveListener l([&](Vector2 pos) {
        auto size = canvas.getSize();
        mouse.x = (pos.x / static_cast<float>(size.width)) * 2 - 1;
        mouse.y = -(pos.y / static_cast<float>(size.height)) * 2 + 1;
    });

    MyListener k{controlsPtr, scene, camera};
    canvas.addMouseListener(&k);

    Raycaster raycaster;

    canvas.onWindowResize([&](WindowSize size) {
        raycaster.setFromCamera(mouse, camera);
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&] {
        controlsPtr->update();
        controls.update();
        renderer.render(scene, camera);
    });

    std::cout << "All objects in the scene:" << std::endl;
    for (const auto& object : scene->children) {
        std::cout << "Object name: " << object->name << " position: (" << object->position.x << ", " << object->position.y << ", " << object->position.z << ")" << std::endl;
    }

    canvas.animate([&] {
        controls.update();
        renderer.render(scene, camera);
    });

    return 0;
}