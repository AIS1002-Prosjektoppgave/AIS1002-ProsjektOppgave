// Created by Kevin Silbernagel on 02/03/2023.
//

#ifndef THREEPP_VCPKG_TEST_CHESSBOARDGEOMETRY_H
#define THREEPP_VCPKG_TEST_CHESSBOARDGEOMETRY_H

#include <memory>
#include "chessPiecesGeometry.h"
#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"


using namespace threepp;

class Chessboard {
public:
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

        auto pawn = ChessPiecesGeometry::createPawn();
        pawn->setPosition(0, 0.5, 0);
        scene_.add(pawn->getMesh());

        // Set up the UI
        imgui_context_ = std::make_unique<imgui_functional_context>(
                canvas_->window(), [this] {
                    ImGui::Begin("Chessboard");
                    ImGui::Text("Chessboard Controls:");
                    ImGui::Checkbox("Enable Controls", &controls_enabled_);
                    ImGui::End();
                });

        // Set up the event listeners
        canvas_->onResize([this](WindowSize size) {
            camera_->setAspect(size.getAspect());
            camera_->updateProjectionMatrix();
            renderer_->setSize(size);
        });

        canvas_->animate([this](float deltaTime) {
            // Render the scene
            renderer_->render(&scene_, camera_.get());


            // Update the chess pieces
            // ...

            // Update the controls
            controls_.setEnabled(controls_enabled_);
            controls_.update(deltaTime);

            // Render the UI
            imgui_context_->render();
        });
    }

    threepp::Scene& getScene() {
        return scene_;
    }

private:
    std::shared_ptr<Canvas> canvas_;
    std::shared_ptr<GLRenderer> renderer_;
    std::shared_ptr<PerspectiveCamera> camera_;
    threepp::Scene scene_;
    std::unique_ptr<imgui_functional_context> imgui_context_;
    OrbitControls controls_{camera_, *canvas_};
    bool controls_enabled_ = true;
};

#endif

/* int main() {
    auto canvas = std::make_shared<Canvas>();
    auto renderer = std::make_shared<GLRenderer
