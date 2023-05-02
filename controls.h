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
    }


    std::shared_ptr<Mesh> selectedMesh_ = nullptr;
    Mesh *selectedRawMesh_ = nullptr;

    Vector2 normalizeMouseCoordinates(const Vector2 &mousePosition) {
        Vector2 normalized;
        auto canvasSize = canvas_->getSize();
        normalized.x = (mousePosition.x / static_cast<float>(canvasSize.width)) * 2 - 1;
        normalized.y = -(mousePosition.y / static_cast<float>(canvasSize.height)) * 2 + 1;
        return normalized;
    }

        void update() {
        if (selectedRawMesh_) {
            Vector3 newPosition = selectedMeshOriginalPosition_ + dragOffset_;
            selectedRawMesh_->position.lerp(newPosition, 0.1);
        }
    }


    void onMouseDown(const Vector2 &mousePosition) {
        mouseDown_ = true;
        mousePosition_ = normalizeMouseCoordinates(mousePosition);

        auto normalizedMousePosition = normalizeMouseCoordinates(mousePosition);
        auto raycaster = std::make_shared<Raycaster>();
        raycaster->setFromCamera(normalizedMousePosition, camera_);
        auto intersects = raycaster->intersectObjects(scene_->children, true);

        for (const auto& intersection : intersects) {
            std::cout << "Intersected object name: " << intersection.object->name << std::endl;
        }
        for (const auto& intersection : intersects) {
            std::cout << "Intersected object type: " << typeid(*intersection.object).name() << std::endl;
            std::cout << "Intersected object position: (" << intersection.object->position.x << ", " << intersection.object->position.y << ", " << intersection.object->position.z << ")" << std::endl;
            std::cout << "Intersected object name: " << intersection.object->name << " position: (" << intersection.object->position.x << ", " << intersection.object->position.y << ", " << intersection.object->position.z << ")" << std::endl;
        }


        if (!intersects.empty()) {
            std::string squareName;
            if (auto mesh = dynamic_cast<threepp::Mesh *>(intersects[0].object)) {
                squareName = mesh->name;
            }
            if (!squareName.empty() && squareName.find("square") != std::string::npos) {
                if (!selectDestination_) {
                    std::string chessPieceName;
                    for (const auto &object : scene_->children) {
                        if (auto mesh = dynamic_cast<threepp::Mesh *>(object.get())) {
                            if (mesh->name.find("chess_piece") != std::string::npos) {
                                std::cout << "Piece: " << mesh->name << ", position: (" << mesh->position.x << ", " << mesh->position.y << ", " << mesh->position.z << ")" << std::endl;
                                std::cout << "Intersected square position: (" << intersects[0].point.x << ", " << intersects[0].point.y << ", " << intersects[0].point.z << ")" << std::endl;
                                if (mesh->position.x == intersects[0].point.x &&
                                    mesh->position.z == intersects[0].point.z) {
                                    chessPieceName = mesh->name;
                                    break;
                                }
                            }
                        }
                    }
                    const float threshold = 0.1;

                    for (const auto &object : scene_->children) {
                        if (auto mesh = dynamic_cast<threepp::Mesh *>(object.get())) {
                            if (mesh->name.find("chess_piece") != std::string::npos) {
                                std::cout << "Piece: " << mesh->name << ", position: (" << mesh->position.x << ", " << mesh->position.y << ", " << mesh->position.z << ")" << std::endl;
                                std::cout << "Intersected square position: (" << intersects[0].point.x << ", " << intersects[0].point.y << ", " << intersects[0].point.z << ")" << std::endl;
                                if (mesh->position.distanceTo(intersects[0].point) < threshold) {
                                    chessPieceName = mesh->name;
                                    break;
                                }
                            }
                        }
                    }




                } else {
// Move the selected chess piece to the square
                    threepp::Vector3 newPosition(intersects[0].point.x, selectedRawMesh_->position.y, intersects[0].point.z);
                    moveSelectedMeshTo(newPosition);
                    std::cout << "Moved mesh " << selectedRawMesh_->name << " to the new position" << std::endl;
                    selectedRawMesh_ = nullptr;
                    selectDestination_ = false;
                }
            }
        }
    }
    void moveSelectedMeshTo(const threepp::Vector3 &newPosition) {
        if (selectedRawMesh_) {
            selectedRawMesh_->position.set(newPosition.x, newPosition.y, newPosition.z);
        }
    }

    void onMouseMove(const Vector2 &mousePosition) {
        if (!selectedRawMesh_ || !mouseDown_) return;

        auto normalizedMousePosition = normalizeMouseCoordinates(mousePosition);
        auto raycaster = std::make_shared<Raycaster>();
        raycaster->setFromCamera(normalizedMousePosition, camera_);

        auto intersection = getIntersection(normalizedMousePosition);
        if (intersection) {
            auto newPosition = intersection->point;
            newPosition.y = selectedRawMesh_->position.y;
            moveSelectedMeshTo(newPosition);
        }
    }

    void onMouseUp() {
        if (mouseDown_ && selectedRawMesh_) {
            mouseDown_ = false;
            auto normalizedMousePosition = normalizeMouseCoordinates(mousePosition_);
            auto intersection = getIntersection(normalizedMousePosition);
            if (intersection) {
                threepp::Vector3 newPosition(intersection->point.x, selectedRawMesh_->position.y, intersection->point.z);
                moveSelectedMeshTo(newPosition);
                std::cout << "Released mesh " << selectedRawMesh_->name << " at new position" << std::endl;
            } else {
                // Move the mesh back to its original position
                selectedRawMesh_->position.set(selectedMeshOriginalPosition_.x, selectedMeshOriginalPosition_.y, selectedMeshOriginalPosition_.z);
                std::cout << "Released mesh " << selectedRawMesh_->name << " at original position" << std::endl;
            }
            selectedRawMesh_ = nullptr;
            selectDestination_ = false;
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
    bool selectDestination_ = false;
    std::shared_ptr<Object3D> selectedPiece = nullptr;
    Vector3 selectedMeshOriginalPosition_;
    std::optional<Intersection> getIntersection(const Vector2 &normalizedMousePosition) {
        auto raycaster = std::make_shared<Raycaster>();
        raycaster->setFromCamera(normalizedMousePosition, camera_);
        auto intersects = raycaster->intersectObjects(scene_->children, true);
        if (!intersects.empty()) {
            return intersects[0];
        }
        return std::nullopt;
    }
};
#endif //THREEPP_VCPKG_TEST_CONTROLS_H