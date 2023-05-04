#ifndef THREEPP_VCPKG_TEST_CONTROLS_H
#define THREEPP_VCPKG_TEST_CONTROLS_H

#include "chessBoardGeometry.h"
#include "threepp/controls/OrbitControls.hpp"
#include "threepp/threepp.hpp"
#include "functional"
#include "threepp/core/Raycaster.hpp"
#include "threepp/objects/Mesh.hpp"
#include "threepp/Canvas.hpp"
#include "memory"
#include "iostream"
#include "vector"
#include "threepp/math/Vector3.hpp"
#include "threepp/cameras/PerspectiveCamera.hpp"
#include "threepp/core/BufferGeometry.hpp"
#include "threepp/core/BufferAttribute.hpp"


using namespace threepp;

class Controls {
public:
    Controls(std::shared_ptr<PerspectiveCamera> &camera, Canvas &canvas, std::shared_ptr<Scene> scene)
            : camera_(camera), canvas_(&canvas), scene_(std::move(scene)) {
        // Find the chessboard mesh
        for (const auto &object: scene_->children) {
            if (object->name == "chessboard") {
                chessboard_ = object;
                break;
            }
        }

        for (const auto &object: scene_->children) {
            if (auto mesh = dynamic_cast<threepp::Mesh*>(object.get())) {
                if (mesh->name.find("chess_piece") != std::string::npos) {
                    mesh->castShadow = true;
                    mesh->receiveShadow = true;
                    std::cout << "Chess piece: " << mesh->name << " position: (" << mesh->position.x << ", " << mesh->position.y << ", " << mesh->position.z << ")" << std::endl;
                }
            }
        }
        auto lineGeometry = BufferGeometry::create();
        auto lineMaterial = LineBasicMaterial::create();
        lineMaterial->color = Color(0xff0000);
        rayLine_ = Line::create(lineGeometry, lineMaterial);
        rayLine_->visible = true; // Set the visibility to true in the constructor
        scene_->add(rayLine_);
        updateRaycasterLine();
    }

    Mesh *selectedRawMesh_ = nullptr;

    Vector2 normalizeMouseCoordinates(const Vector2 &mousePosition) {
        Vector2 normalized;
        auto canvasSize = canvas_->getSize();
        normalized.x = (mousePosition.x / static_cast<float>(canvasSize.width)) * 2 - 1;
        normalized.y = -(mousePosition.y / static_cast<float>(canvasSize.height)) * 2 + 1;
        return normalized;
    }

    void updateRaycasterLine() {
        auto raycaster = std::make_shared<Raycaster>();
        raycaster->setFromCamera(mousePosition_, camera_);
        auto positions = std::vector<float>{
                raycaster->ray.origin.x,
                raycaster->ray.origin.y,
                raycaster->ray.origin.z,
                (raycaster->ray.origin + raycaster->ray.direction * 100.f).x,
                (raycaster->ray.origin + raycaster->ray.direction * 100.f).y,
                (raycaster->ray.origin + raycaster->ray.direction * 100.f).z
        };
        std::unique_ptr<threepp::BufferAttribute> positionAttribute = std::unique_ptr<threepp::BufferAttribute>(FloatBufferAttribute::create(positions, 3).release());
        rayLine_->geometry()->setAttribute("position", std::move(positionAttribute));
    }

    void update() {
        if (selectedRawMesh_) {
            Vector3 newPosition = selectedMeshOriginalPosition_ + dragOffset_;
            selectedRawMesh_->position.lerp(newPosition, 0.1);
        }
    }


    void resetSelectedPieceState() {
        selectedRawMesh_ = nullptr;
        selectDestination_ = false;
    }

    void onMouseDown(const Vector2 &mousePosition) {
        mouseDown_ = true;
        mousePosition_ = normalizeMouseCoordinates(mousePosition);

        updateRaycasterLine();

        auto normalizedMousePosition = normalizeMouseCoordinates(mousePosition);
        auto raycaster = std::make_shared<Raycaster>();
        raycaster->setFromCamera(normalizedMousePosition, camera_);
        auto intersects = raycaster->intersectObjects(scene_->children, true);

        threepp::Mesh *intersectedPiece = nullptr;
        threepp::Mesh *intersectedSquare = nullptr;

        for (const auto& intersection : intersects) {
            if (auto mesh = dynamic_cast<threepp::Mesh*>(intersection.object)) {
                if (mesh->name.find("chess_piece") != std::string::npos) {
                    intersectedPiece = mesh;
                    break;
                } else if (mesh->name.find("square") != std::string::npos) {
                    intersectedSquare = mesh;
                }
            }
        }

        if (intersectedPiece) {
            if (selectedRawMesh_ && selectDestination_) {
                if (intersectedPiece != selectedRawMesh_) {
                    resetSelectedPieceState();
                }
            }
            else {
                selectedRawMesh_ = intersectedPiece;
                selectedMeshOriginalPosition_ = intersectedPiece->position;
                selectDestination_ = true;
                selectedRawMesh_->position.y += 5.f;
            }
        }
        else if (intersectedSquare && selectDestination_) {
            ChessboardGeometry cbg;
            Vector3 nearestSquarePosition = cbg.getNearestSquare(intersectedSquare->position);
            moveSelectedMeshTo(nearestSquarePosition);
            std::cout << "Moved mesh " << selectedRawMesh_->name << " to the new position" << std::endl;
            resetSelectedPieceState();
        } else {
            resetSelectedPieceState();
        }
    }


    void moveSelectedMeshTo(const threepp::Vector3 &newPosition) {
        if (selectedRawMesh_) {
            selectedRawMesh_->position.set(newPosition.x, selectedMeshOriginalPosition_.y, newPosition.z);
        }
    }


private:
    std::shared_ptr<threepp::Line> rayLine_;
    std::shared_ptr<PerspectiveCamera> camera_;
    std::shared_ptr<Object3D> chessboard_;
    Canvas *canvas_;
    std::shared_ptr<Scene> scene_;
    bool mouseDown_ = false;
    Vector2 mousePosition_;
    Vector3 dragOffset_;
    std::shared_ptr<Object3D> selectedPiece = nullptr;
    Vector3 selectedMeshOriginalPosition_;
    bool selectDestination_ = false;

};
#endif //THREEPP_VCPKG_TEST_CONTROLS_H