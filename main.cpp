#include <memory>
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
#include <threepp/threepp.hpp>

        class PawnGeometry : public BufferGeometry {
        public:
            PawnGeometry() : threepp::BufferGeometry() {
                const float height = 1.5f;
                const float radiusTop = 0.5f;
                const float radiusBottom = 1.0f;
                const int radialSegments = 16;

                // create top and bottom vertices
                Float32Array topVertices((radialSegments + 1) * 3);
                Float32Array bottomVertices((radialSegments + 1) * 3);
                for (int i = 0; i <= radialSegments; i++) {
                    float theta = i * (M_PI * 2 / radialSegments);
                    float x = sin(theta);
                    float z = cos(theta);

                    topVertices[i * 3] = x * radiusTop;
                    topVertices[i * 3 + 1] = height / 2;
                    topVertices[i * 3 + 2] = z * radiusTop;

                    bottomVertices[i * 3] = x * radiusBottom;
                    bottomVertices[i * 3 + 1] = -height / 2;
                    bottomVertices[i * 3 + 2] = z * radiusBottom;
                }

                // create indices for top and bottom faces
                Uint16Array topIndices(radialSegments * 3);
                Uint16Array bottomIndices(radialSegments * 3);
                for (int i = 0; i < radialSegments; i++) {
                    topIndices[i * 3] = 0;
                    topIndices[i * 3 + 1] = i + 1;
                    topIndices[i * 3 + 2] = i + 2;

                    bottomIndices[i * 3] = radialSegments + 1;
                    bottomIndices[i * 3 + 1] = i + 2 + radialSegments;
                    bottomIndices[i * 3 + 2] = i + 1 + radialSegments;
                }
                topIndices[radialSegments * 3 - 1] = 1;
                bottomIndices[radialSegments * 3 - 1] = radialSegments + 2;

                // set attributes and indices
                setAttribute("position", FloatBufferAttribute::create(topVertices.concatenate(bottomVertices), 3));
                setIndex(IntBufferAttribute::create(topIndices.concatenate(bottomIndices), 1));
            }
        };


        auto pawnGeometry = PawnGeometry::create(); // use the `create` function to create an instance of the `PawnGeometry` class
        auto pawnMaterial = MeshStandardMaterial::create();
        pawnMaterial->color = Color::white;
        auto pawnMesh = Mesh::create(pawnGeometry, pawnMaterial);
        pawnMesh->position = Vector3(-3.5, 0.25, -3.5);
        scene_.add(pawnMesh);







        // Set up the UI
        imgui_context_ = std::make_unique<imgui_functional_context>(
                canvas_->window_ptr(), [this] {
                    ImGui::Begin("Chessboard");
                    ImGui::Text("Chessboard Controls:");
                    ImGui::Checkbox("Enable Controls", &controls_enabled_);
                    ImGui::End();
                });

        // Set up the event listeners
        canvas_->onWindowResize([this](WindowSize size){
            camera_->aspect = size.getAspect();
            camera_->updateProjectionMatrix();
            renderer_->setSize(size);
        });

        canvas_->animate([this] {
            // Render the scene
            renderer_->render(&scene_, camera_.get());


            // Update the chess pieces
            // ...

            // Update the controls
            controls_.enabled = controls_enabled_;

            // Render the UI
            imgui_context_->render();
        });
    }

private:
    std::shared_ptr<Canvas> canvas_;
    std::shared_ptr<GLRenderer> renderer_;
    std::shared_ptr<PerspectiveCamera> camera_;
    Scene scene_;
    std::unique_ptr<imgui_functional_context> imgui_context_;
    OrbitControls controls_{camera_, *canvas_};
    bool controls_enabled_ = true;
};

int main() {
    auto canvas = std::make_shared<Canvas>();
    auto renderer = std::make_shared<GLRenderer>(*canvas);
    renderer->setClearColor(Color::gray);

    auto camera = PerspectiveCamera::create();
    camera->position.y = 5;
    camera->position.z = 10;

    auto chessboard = std::make_unique<Chessboard>(std::move(canvas), std::move(renderer), std::move(camera));

    return 0;
}
