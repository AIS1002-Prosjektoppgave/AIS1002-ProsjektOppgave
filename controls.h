#ifndef THREEPP_VCPKG_TEST_CONTROLS_H
#define THREEPP_VCPKG_TEST_CONTROLS_H

#include "chessBoardGeometry.h"
#include <threepp/controls/OrbitControls.hpp>
#include <threepp/threepp.hpp>
#include <functional>
#include <threepp/core/Raycaster.hpp>
#include <threepp/objects/Mesh.hpp>
#include <threepp/Canvas.hpp>
#include <memory>
#include <utility>
#include <iostream>

using namespace threepp;

class Controls {
public:
    Controls(std::shared_ptr<PerspectiveCamera>& camera, Canvas& canvas, std::shared_ptr<Scene> scene)
            : camera_(camera), canvas_(&canvas), scene_(std::move(scene))
    {
        // Find the chessboard mesh
        for (const auto& object : scene_->children) {
            if (auto mesh = std::dynamic_pointer_cast<Mesh>(object); mesh && mesh->name == "chessboard") {
                chessboard_ = mesh;
                break;
            }
        }
    }

    std::shared_ptr<Mesh> selectedMesh_ = nullptr;
    Mesh* selectedRawMesh_ = nullptr;

    void onMouseDown(const Vector2& mousePosition) {
        mouseDown_ = true;
        mousePosition_ = mousePosition;
        auto intersection = getIntersection(mousePosition_);
        if (intersection && intersection->object->parent->is<Mesh>()) {
            auto meshName = intersection->object->parent->name;
            if (meshName.find("chess_piece") != std::string::npos) {
                selectedRawMesh_ = dynamic_cast<Mesh*>(intersection->object->parent);
                dragOffset_ = selectedRawMesh_->position - intersection->point;
                std::cout << "Selected mesh: " << selectedRawMesh_->name << std::endl;
            }
        } else {
            selectedRawMesh_ = nullptr;
        }
    }

    void onMouseMove(const Vector2& pos)
    {
        if (!selectedRawMesh_ || !mouseDown_)
            return;

        auto intersection = getIntersection(pos);
        if (intersection) {
            auto newPosition = intersection->point + dragOffset_;
            selectedRawMesh_->position = newPosition; // update the position of the selected mesh
            std::cout << "Moved mesh " << selectedRawMesh_->name << " to position (" << newPosition.x << ", " << newPosition.y << ", " << newPosition.z << ")" << std::endl;
        }
    }

    void moveSelectedMeshTo(const Vector3& position) {
        if (selectedRawMesh_) {
            auto newPosition = Vector3(position.x, selectedRawMesh_->position.y, position.z);
            selectedRawMesh_->position.set(newPosition.x, newPosition.y, newPosition.z); // update the position of the selected mesh
            std::cout << "Moved mesh " << selectedRawMesh_->name << " to position (" << newPosition.x << ", " << newPosition.y << ", " << newPosition.z << ")" << std::endl;
        }
    }


    void onMouseUp() {
        if (mouseDown_) {
            mouseDown_ = false;
            auto intersection = getIntersection(mousePosition_);
            if (intersection) {
                Vector3 newPosition(selectedRawMesh_->position.x, selectedRawMesh_->position.y, selectedRawMesh_->position.z);
                moveSelectedMeshTo(newPosition);
                std::cout << "Released mesh " << selectedRawMesh_->name << std::endl;
            }
            selectedRawMesh_ = nullptr;
        }
    }

private:
    std::shared_ptr<Camera> camera_;
    std::shared_ptr<Mesh> chessboard_;
    Canvas* canvas_;
    std::shared_ptr<Scene> scene_;

    bool mouseDown_ = false;
    Vector2 mousePosition_;
    Vector3 dragOffset_;

    std::optional<Intersection> getIntersection(const Vector2& pos)
    {
        auto raycaster = std::make_shared<Raycaster>();
        raycaster->setFromCamera(pos, camera_);

        std::cout << "Raycaster:" << std::endl;
        std::cout << "  Origin: (" << raycaster->ray.origin.x << ", " << raycaster->ray.origin.y << ", " << raycaster->ray.origin.z << ")" << std::endl;
        std::cout << "  Direction: (" << raycaster->ray.direction.x << ", " << raycaster->ray.direction.y << ", " << raycaster->ray.direction.z << ")" << std::endl;

        // Intersect the ray with the chess pieces
        std::vector<std::shared_ptr<Mesh>> chessPieces;
        for (const auto& object : scene_->children) {
            if (auto mesh = std::dynamic_pointer_cast<Mesh>(object); mesh && mesh->name.find("chess_piece") != std::string::npos) {
                chessPieces.push_back(mesh);
            }
        }

        Intersection closestIntersection;
        double closestDistance = std::numeric_limits<double>::max();

        for (const auto& chessPiece : chessPieces) {
            auto intersects = raycaster->intersectObject(chessPiece.get());
            if (!intersects.empty() && intersects[0].distance < closestDistance) {
                closestIntersection = intersects[0];
                closestDistance = intersects[0].distance;
            }
        }

        if (closestDistance < std::numeric_limits<double>::max()) {
            std::cout << "Intersection:" << std::endl;
            std::cout << "  Distance: " << closestIntersection.distance << std::endl;
            std::cout << "  Point: (" << closestIntersection.point.x << ", " << closestIntersection.point.y << ", " << closestIntersection.point.z << ")" << std::endl;
            std::cout << "  Normal: (" << closestIntersection.face->normal.x << ", " << closestIntersection.face->normal.y << ", " << closestIntersection.face->normal.z << ")" << std::endl;
            return closestIntersection;
        }

        return std::nullopt;
    }

};
#endif //THREEPP_VCPKG_TEST_CONTROLS_H