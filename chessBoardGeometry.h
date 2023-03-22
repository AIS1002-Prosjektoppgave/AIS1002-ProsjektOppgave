#ifndef THREEPP_VCPKG_TEST_CHESSBOARDGEOMETRY_H
#define THREEPP_VCPKG_TEST_CHESSBOARDGEOMETRY_H
#include <memory>
#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"
#include "example.h"
#include <vector>
#include <utility>
#include "threepp/Canvas.hpp"
#include "threepp/math/Vector3.hpp"
#include "threepp/core/Raycaster.hpp"
#include <cmath>
#include <iostream>

using namespace threepp;

class Chessboard {
public:

    Object3D* getObjectByName(const std::string& name) {
        for (const auto& child : children()) {
            if (child->name.compare(name) == 0) {
                return child.get();
            }
        }
        return nullptr;
    }

    float t = 0;
    std::vector<std::shared_ptr<threepp::Object3D>>& children() {return scene_.children;}

    Chessboard(std::shared_ptr<Canvas> canvas, std::shared_ptr<GLRenderer> renderer,
               std::shared_ptr<PerspectiveCamera> camera) :
            canvas_(std::move(canvas)), renderer_(std::move(renderer)), camera_(std::move(camera)) {
        init();

    }

    void init() {
        // Create the chessboard mesh
        auto whiteGeometry = BoxGeometry::create(8, 0.2, 8);
        auto whiteMaterial = MeshBasicMaterial::create();
        whiteMaterial->color = Color::white;
        auto whiteMesh = Mesh::create(whiteGeometry, whiteMaterial);
        whiteMesh->position.y = -0.1;
        scene_.add(whiteMesh);

        auto blackGeometry = BoxGeometry::create(1, 0.2, 1);
        auto blackMaterial = MeshBasicMaterial::create();
        blackMaterial->color = Color::black;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i + j) % 2 == 0) {
                    auto blackMesh = Mesh::create(blackGeometry, blackMaterial);
                    blackMesh->position.x = i - 3.5;
                    blackMesh->position.y = -0.09;
                    blackMesh->position.z = j - 3.5;
                    scene_.add(blackMesh);
                }
            }
        }


        // Add the chess pieces
        for (int i = 0; i < 2; i++) { // Legger til knight brikkene
            for (int j = 0; j < 2; j++) {
                auto knight = std::make_shared<Knight>();
                knight->mesh()->position.set(-2.5 + j * 5, 1, -3.5 + 7 * i);
                scene_.add(knight->mesh());
            }
        }



        for (int i = 0; i < 2; i++) {  // Legget til King brikkene
            auto king = std::make_shared<King>();
            king->mesh()->position.set(0.5, 0, -3.5 + 7 * i);
            scene_.add(king->mesh());
        }


        for (int i = 0; i < 8; i++) { // Legger til pawn brikker
            for (int j = 0; j < 2; j++) {
                auto pawn = std::make_shared<Pawn>();
                pawn->mesh()->position.set(i - 3.5, 1, -2.5 + j * 5);
                scene_.add(pawn->mesh());
            }
        }


        for (int i = 0; i < 2; i++) { // Legger til tårn brikkene
            for (int j = 0; j < 2; j++) {
                auto tower = std::make_shared<Tower>();
                tower->mesh()->position.set(-3.5 + j * 7, 1, -3.5 + 7 * i);
                scene_.add(tower->mesh());
            }
        }

        for (int i = 0; i < 2; i++) { // Legger til Rook (bishop, må bytte senere) brikker
            for (int j = 0; j < 2; j++) {
                auto rook = std::make_shared<Rook>();
                rook->mesh()->position.set(-1.5 + j * 3, 1, -3.5 + 7 * i);
                scene_.add(rook->mesh());
            }
        }


        for (int i = 0; i < 2; i++) { //Legger til Queen
            auto queen = std::make_shared<Queen>();
            queen->mesh()->position.set(-0.5, 1, -3.5 + 7 * i);
            scene_.add(queen->mesh());
        }


        // Set up the UI
        imgui_context_ = std::make_unique<imgui_functional_context>(
                canvas_->window_ptr(), [this] {
                    ImGui::Begin("Chessboard");
                    ImGui::Text("Chessboard Controls:");
                    ImGui::Checkbox("Enable Controls", &controls_enabled_);
                    ImGui::End();
                });

        // Set up the event listeners
        canvas_->onWindowResize([this](WindowSize size) {
            camera_->aspect = size.getAspect();
            camera_->updateProjectionMatrix();
            renderer_->setSize(size);
        });


        //sets upp mouse control
        Mesh* selectedMesh = nullptr;  // Declare selectedMesh at a higher scope level
        Vector3 dragOffset{0, 0, 0};
        Vector2 dragStartPosition{0, 0};
        auto getCellSize = Vector3(1, 0.2, 1);

        auto onMouseDown = [this, chessboard = this, &selectedMesh, &dragOffset, &dragStartPosition](int button, const Vector2 &pos) {
            if (button == 0) {
                // Check if the user clicked on a chess piece
                Raycaster raycaster;
                Vector2 mouse{-1, -1};
                MouseMoveListener l([&](Vector2 pos) {
                    // calculate mouse position in normalized device coordinates
                    // (-1 to +1) for both components
                    auto size = canvas_->getSize();
                    mouse.x = (pos.x / static_cast<float>(size.width)) * 2 - 1;
                    mouse.y = -(pos.y / static_cast<float>(size.height)) * 2 + 1;
                });

                raycaster.setFromCamera(mouse, camera_);
                auto& objects = chessboard->children();
                for (auto& object : objects) {
                    auto mesh = std::dynamic_pointer_cast<Mesh>(object);
                    if (mesh) {
                        if (mesh->name.substr(0, 11) == "chess_piece") {
                            auto intersects = raycaster.intersectObject(mesh.get());
                            if (!intersects.empty()) {
                                // Get the chess piece mesh by name
                                selectedMesh = dynamic_cast<Mesh*>(chessboard->getObjectByName(mesh->name));
                                dragStartPosition = pos;
                                dragOffset = selectedMesh->position - intersects[0].point;
                                break;
                            }
                        }
                    }
                }
            }
        };


        auto onMouseUp = [&selectedMesh](int button, const Vector2& pos) {
            if (selectedMesh) {
                // Deselect the mesh
                selectedMesh = nullptr;
            }
        };


        auto onMouseMove = [this, chessboard = this, &dragOffset, &selectedMesh, getCellSize](const Vector2 &pos, const Vector2 &delta) {
            if (selectedMesh) {
                // Move the selected mesh
                auto canvasSize = chessboard->canvas_->getSize();
                auto mousePosition = Vector2(pos.x / canvasSize.width, pos.y / canvasSize.height).multiplyScalar(2) - Vector2(1, 1);
                Raycaster raycaster;
                raycaster.setFromCamera(mousePosition, camera_);
                auto intersection = raycaster.intersectObject(selectedMesh);
                if (!intersection.empty()) {
                    auto position = intersection[0].point - dragOffset;
                    auto cellSize = getCellSize;
                    auto x = round(position.x / cellSize.x) * cellSize.x;
                    auto y = round(position.y / cellSize.y) * cellSize.y;
                    auto z = round(position.z / cellSize.z) * cellSize.z;
                    selectedMesh->position.set(x, y, z);
                }
            }
        };



        canvas_->animate([this](float dt) {

            t += dt;


            // Render the scene
            renderer_->render(&scene_, camera_.get());



            // Update the controls
            controls_.enabled = controls_enabled_;

            // Render the UI
            imgui_context_->render();
        });
    };


private:
    std::shared_ptr<Chessboard> chessboard_;
    std::shared_ptr<Canvas> canvas_;
    std::shared_ptr<GLRenderer> renderer_;
    std::shared_ptr<PerspectiveCamera> camera_;
    std::unique_ptr<imgui_functional_context> imgui_context_;
    Scene scene_;
    OrbitControls controls_{camera_, *canvas_};
    bool controls_enabled_ = true;
    std::shared_ptr<Object3D> selected_object_;
    Vector3 selected_object_position_;
    std::function<void(int, const Vector2&)> onMouseDown;
};


#endif //THREEPP_VCPKG_TEST_CHESSBOARDGEOMETRY_H