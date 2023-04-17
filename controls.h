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

//lager klasse for flytting av sjakkbrikker (ikke helt implementert enda, men på saken:))
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
                }
            }
        }

        // Initialize the ray line
        auto material = LineBasicMaterial::create();
        material->color = 0xff0000; // Red color for the line
        auto geometry = std::make_shared<threepp::BufferGeometry>();
        geometry->setAttribute("position", threepp::TypedBufferAttribute<float>::create({0, 0, 0, 0, 0, 0}, 3));
        rayLine_ = threepp::Line::create(geometry, material);
        scene_->add(rayLine_);
        Vector3 forward;
        camera_->getWorldDirection(forward);
        updateRayLine(camera_->position, forward);
        scene_->add(rayLine_);

        for (const auto &object : scene_->children) {
            if (auto mesh = dynamic_cast<threepp::Mesh *>(object.get())) {
                if (mesh->name.find("chess_piece") != std::string::npos) {
                    mesh->castShadow = true;
                    mesh->receiveShadow = true;

                    // Create a bounding sphere for the chess piece
                    auto sphere = std::make_shared<Sphere>(mesh->position, 1.0f); // Adjust the radius based on your chess piece size
                    boundingSpheres_[mesh->name] = sphere;
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


    void moveSelectedMeshTo(const threepp::Vector3 &newPosition) {
        if (selectedRawMesh_) {
            selectedRawMesh_->position.set(newPosition.x, newPosition.y, newPosition.z);
        }
    }


    // funksjon for håndtering av trykt museknapp
    void onMouseDown(const Vector2 &mousePosition) {
        mouseDown_ = true;
        mousePosition_ = normalizeMouseCoordinates(mousePosition);

        // Convert the mouse coordinates to 3D space
        auto normalizedMousePosition = normalizeMouseCoordinates(mousePosition);


        // Use the 3D mouse coordinates for the raycasting
        auto raycaster = std::make_shared<Raycaster>();
        raycaster->setFromCamera(normalizedMousePosition, camera_);


        auto intersects = raycaster->intersectObjects(scene_->children, true);
        for (const auto& intersection : intersects) {
            std::cout << "Intersected object name: " << intersection.object->name << std::endl;
        }

        if (!intersects.empty()) {
            if (!selectDestination_) {
                for (const auto &intersection : intersects) {
                    if (auto mesh = dynamic_cast<threepp::Mesh *>(intersection.object)) {
                        std::cout << "Mesh name: " << mesh->name << std::endl;
                        std::cout << "chess_piece found at position: " << mesh->name.find("chess_piece") << std::endl;
                        if (mesh->name.find("chess_piece") != std::string::npos) {
                            selectedRawMesh_ = mesh;
                            selectedMeshOriginalPosition_ = mesh->position;
                            mesh->position.y = 15; // Move the mesh high above to make it "invisible" during the drag
                            dragOffset_ = selectedMeshOriginalPosition_ - intersection.point;
                            std::cout << "Selected mesh: " << selectedRawMesh_->name << std::endl;
                            selectDestination_ = true;
                            break; // Exit the loop after finding a valid chess piece
                        }
                    }
                }
            }

            else {
                threepp::Vector3 newPosition(intersects[0].point.x, intersects[0].point.y, intersects[0].point.z);
                moveSelectedMeshTo(newPosition);
                std::cout << "Moved mesh " << selectedRawMesh_->name << " to the new position" << std::endl;
                selectedRawMesh_ = nullptr;
                selectDestination_ = false;
            }

            // Update the ray line to start from the camera position and end at the intersection point
            updateRayLine(raycaster->ray.origin, raycaster->ray.direction);

            // Make the ray line visible
            rayLine_->visible = true;

        } else {
            selectedRawMesh_ = nullptr;
            // Hide the ray line
            rayLine_->visible = false;
        }
    }


    //håndtering for flytting av mus når museknapp er nedtrykt
    void onMouseMove(const Vector2 &mousePosition) {
        if (!selectedRawMesh_ || !mouseDown_) return;

        auto normalizedMousePosition = normalizeMouseCoordinates(mousePosition);
        auto raycaster = std::make_shared<Raycaster>();
        raycaster->setFromCamera(normalizedMousePosition, camera_);
        updateRayLine(raycaster->ray.origin, raycaster->ray.direction);

        auto intersection = getIntersection(normalizedMousePosition);
        if (intersection) {
            auto newPosition = intersection->point + dragOffset_;
            moveSelectedMeshTo(newPosition);
        }

        // Make the ray line visible
        rayLine_->visible = true;
    }

    //håndtering av når museknapp blir sluppet
    void onMouseUp() {
        if (mouseDown_ && selectedRawMesh_) {
            mouseDown_ = false;
            auto normalizedMousePosition = normalizeMouseCoordinates(mousePosition_);
            auto intersection = getIntersection(normalizedMousePosition);
            if (intersection) {
                threepp::Vector3 newPosition(intersection->point.x, intersection->point.y, intersection->point.z);
                selectedRawMesh_->position.set(newPosition.x, newPosition.y, newPosition.z);
                std::cout << "Released mesh " << selectedRawMesh_->name << " at new position" << std::endl;
            } else {
                // Move the mesh back to its original position
                selectedRawMesh_->position.set(selectedMeshOriginalPosition_.x, selectedMeshOriginalPosition_.y, selectedMeshOriginalPosition_.z);
                std::cout << "Released mesh " << selectedRawMesh_->name << " at original position" << std::endl;
            }
            selectedRawMesh_ = nullptr;
            selectDestination_ = false;

            // Hide the ray line
            rayLine_->visible = false;
        }
    }

    std::optional<Intersection> getIntersection(const Vector2 &mousePosition) {
        auto raycaster = std::make_shared<Raycaster>();
        raycaster->setFromCamera(mousePosition, camera_);

        std::optional<Intersection> closestIntersection;
        float closestDistance = std::numeric_limits<float>::max();

        for (const auto &entry : boundingSpheres_) {
            const auto &name = entry.first;
            const auto &sphere = entry.second;

            if (raycaster->ray.intersectsSphere(*sphere)) {
                Vector3 intersectionPoint; // Declare the intersectionPoint variable
                raycaster->ray.closestPointToPoint(sphere->center, intersectionPoint); // Pass intersectionPoint as the second argument
                float distance = intersectionPoint.distanceTo(raycaster->ray.origin);

                if (distance < closestDistance) {
                    closestDistance = distance;
                    closestIntersection = Intersection();
                    closestIntersection->distance = distance;
                    closestIntersection->point = intersectionPoint;
                    closestIntersection->object = scene_->getObjectByName(name);
                }
            }
        }

        return closestIntersection;
    }



//private medlemmer
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
    std::map<std::string, std::shared_ptr<Sphere>> boundingSpheres_;



    void updateRayLine(const Vector3 &origin, const Vector3 &direction, float length = 1000.0f) {
        std::vector<float> positions{
                origin.x, origin.y, origin.z,
                origin.x + direction.x * length, origin.y + direction.y * length, origin.z + direction.z * length
        };
        rayLine_->geometry()->setAttribute("position", threepp::TypedBufferAttribute<float>::create(positions, 3));
    }
};
#endif //THREEPP_VCPKG_TEST_CONTROLS_H