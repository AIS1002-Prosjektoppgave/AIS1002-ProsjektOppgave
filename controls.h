#ifndef THREEPP_VCPKG_TEST_CONTROLS_H
#define THREEPP_VCPKG_TEST_CONTROLS_H

#include "chessBoardGeometry.h"

#include <GLFW/glfw3.h>
#include <threepp/controls/OrbitControls.hpp>
#include <threepp/threepp.hpp>
#include <functional>
#include <threepp/core/Raycaster.hpp>
#include <threepp/objects/Mesh.hpp>
#include <threepp/Canvas.hpp>
#include <memory>

using namespace threepp;

class Controls {
public:
    Controls(std::shared_ptr<Camera> camera, std::shared_ptr<Chessboard> chessboard, std::shared_ptr<Canvas> canvas, std::shared_ptr<Scene> scene)
            : camera_(std::move(camera)), chessboard_(std::move(chessboard)), canvas_(std::move(canvas)), scene_(std::move(scene))
    {
        // Get the GLFW window
        GLFWwindow* window = static_cast<GLFWwindow*>(canvas_->window_ptr());


        // Set the user pointer to this class
        glfwSetWindowUserPointer(window, this);

        // Register the mouse event handlers
        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            Controls* controls = static_cast<Controls*>(glfwGetWindowUserPointer(window));

            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
                double x, y;
                glfwGetCursorPos(window, &x, &y);
                controls->onMouseDown(Vector2(static_cast<float>(x), static_cast<float>(y)));
            } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
                double x, y;
                glfwGetCursorPos(window, &x, &y);
                controls->onMouseUp(Vector2(static_cast<float>(x), static_cast<float>(y)));
            }
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
            Controls* controls = static_cast<Controls*>(glfwGetWindowUserPointer(window));
            controls->onMouseMove(Vector2(static_cast<float>(x), static_cast<float>(y)));
        });
    }

    void onMouseDown(const Vector2 &pos) {
        mouseDown = true;
        mousePosition = pos;

        auto raycaster = std::make_shared<Raycaster>(camera_->position, Vector3(0, 0, -1));
        raycaster->setFromCamera(pos, camera_);

        auto &objects = scene_->children;

        for (auto &object: objects) {
            auto mesh = std::dynamic_pointer_cast<Mesh>(object);
            if (mesh && mesh->name.substr(0, 11) == "chess_piece") {
                auto intersects = raycaster->intersectObject(mesh.get());
                if (!intersects.empty()) {
                    selectedMesh = mesh.get();
                    dragStartPosition = pos;
                    dragOffset = selectedMesh->position - intersects[0].point;
                    break;
                }
            }
        }
    }

    void onMouseMove(const Vector2 &pos) {
        if (!selectedMesh || !mouseDown) return;

        auto intersection = getIntersection(pos);
        if (intersection) {
            auto newPosition = intersection->point + dragOffset;
            selectedMesh->position.setX(newPosition.x);
            selectedMesh->position.setZ(newPosition.z);
        }
    }

    void onMouseUp(const Vector2 &pos) {
        mouseDown = false;
        if (!selectedMesh) return;

        auto intersection = getIntersection(pos);
        if (intersection) {
            auto newPosition = intersection->point + dragOffset;
            selectedMesh->position.setX(newPosition.x);
            selectedMesh->position.setZ(newPosition.z);
        }

        // Perform any necessary actions after piece has been moved, such as checking for a valid move or updating the game state
        chessboard_->onPieceMoved(selectedMesh);

        // Clear the selected mesh
        selectedMesh = nullptr;
    }

private:
    std::shared_ptr<Camera> camera_;
    std::shared_ptr<Chessboard> chessboard_;
    std::shared_ptr<Canvas> canvas_;
    std::shared_ptr<Scene> scene_;

    Mesh *selectedMesh = nullptr;
    bool mouseDown = false;
    Vector2 mousePosition;
    Vector2 dragStartPosition;
    Vector3 dragOffset;

    std::optional<Intersection> getIntersection(const Vector2 &pos) {
        auto raycaster = std::make_shared<Raycaster>(camera_->position, Vector3(0, 0, 1));
        raycaster->setFromCamera(pos, camera_);
        auto intersects = raycaster->intersectObject(chessboard_->getBoardMesh().get());

        if (!intersects.empty()) {
            return intersects[0];
        } else {
            return std::nullopt;
        }
    }
};

#endif //THREEPP_VCPKG_TEST_CONTROLS_H

