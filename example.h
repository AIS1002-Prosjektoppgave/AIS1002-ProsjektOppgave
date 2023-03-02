//
// Created by Kevin Silbernagel on 02/03/2023.
//

#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <memory>
#include "threepp/threepp.hpp"

using namespace threepp;

class Cube {
public:
    Cube(std::shared_ptr<Canvas> canvas, std::shared_ptr<GLRenderer> renderer,
         std::shared_ptr<PerspectiveCamera> camera) :
            canvas_(std::move(canvas)), renderer_(std::move(renderer)), camera_(std::move(camera)) {
        init();
    }

    void init() {
        auto geometry = BoxGeometry::create(1, 1, 1);
        auto material = MeshBasicMaterial::create();
        material->color = Color::red;
        auto mesh = Mesh::create(geometry, material);
        scene_.add(mesh);

        // Set up the event listeners
        canvas_->onWindowResize([this](WindowSize size) {
            camera_->aspect = size.getAspect();
            camera_->updateProjectionMatrix();
            renderer_->setSize(size);
        });

        canvas_->animate([this] {
            // Render the scene
            renderer_->render(&scene_, camera_.get());
        });
    }

private:
    std::shared_ptr<Canvas> canvas_;
    std::shared_ptr<GLRenderer> renderer_;
    std::shared_ptr<PerspectiveCamera> camera_;
    Scene scene_;
};

#endif //EXAMPLE_H

/* int main() {
    auto canvas = std::make_shared<Canvas>();
    auto renderer = std::make_shared<GLRenderer>(*canvas);
    renderer->setClearColor(Color::gray);

    auto camera = PerspectiveCamera::create();
    camera->position.z = 3;

    auto cube = std::make_unique<Cube>(std::move(canvas), std::move(renderer), std::move(camera));

    return 0;
}
*/
