#ifndef AIS1002_PROSJEKTOPPGAVE_CHESSPIECESGEOMETRY_H
#define AIS1002_PROSJEKTOPPGAVE_CHESSPIECESGEOMETRY_H

#include <threepp/threepp.hpp>
#include <threepp/extras/imgui/imgui_context.hpp>
#include <memory>

class ChessPiecesGeometry {
public:
    ChessPiecesGeometry() {
        std::shared_ptr<TextHandle> textHandle_;
        canvas_ = std::make_shared<Canvas>();
        renderer_ = std::make_shared<GLRenderer>(*canvas_);
        renderer_->setClearColor(Color::purple);

        camera_ = PerspectiveCamera::create();
        camera_->position.z = 5;

        controls_ = std::make_shared<OrbitControls>(camera_, *canvas_);

        scene_ = Scene::create();

        group_ = Object3D::create();
        scene_->add(group_);

        {
            auto geometry = BoxGeometry::create();
            auto material = MeshBasicMaterial::create();
            material->color = Color::green;
            auto mesh = Mesh::create(geometry, material);
            mesh->position.x = -1;
            group_->add(mesh);
        }

        {
            auto geometry = BoxGeometry::create();
            auto material = MeshBasicMaterial::create();
            material->color = Color::blue;
            auto mesh = Mesh::create(geometry, material);
            mesh->position.x = 1;
            group_->add(mesh);
        }

        renderer_->enableTextRendering();
        textHandle_ = std::make_shared<TextHandle>(renderer_->textHandle("Hello World"));
        textHandle_->setPosition(0, canvas_->getSize().height - 30);
        textHandle_->scale = 2;

        canvas_->onWindowResize([this](WindowSize size) {
            camera_->aspect = size.getAspect();
            camera_->updateProjectionMatrix();
            renderer_->setSize(size);
            textHandle_->setPosition(0, size.height - 30);
        });
    }

    void render() {
        canvas_->animate([this] {
            renderer_->render(scene_, camera_);
            controls_->update();

            textHandle_->render();

            group_->rotation.y += 0.01f;
        });
    }

private:
    std::shared_ptr<Canvas> canvas_;
    std::shared_ptr<GLRenderer> renderer_;
    std::shared_ptr<PerspectiveCamera> camera_;
    std::shared_ptr<OrbitControls> controls_;
    std::shared_ptr<Scene> scene_;
    std::shared_ptr<Object3D> group_;
};

#endif //AIS1002_PROSJEKTOPPGAVE_CHESSPIECESGEOMETRY_H
