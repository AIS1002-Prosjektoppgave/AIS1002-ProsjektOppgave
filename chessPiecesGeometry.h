#ifndef CHESS_PIECES_GEOMETRY_H
#define CHESS_PIECES_GEOMETRY_H

#include <memory>
#include "threepp/threepp.hpp"

namespace ChessPiecesGeometry {

    class Pawn {
    public:
        Pawn(std::shared_ptr<threepp::Mesh> mesh) : mesh_(mesh) {}

        void setPosition(float x, float y, float z) {
            mesh_->position.set(x, y, z);
        }

        std::shared_ptr<threepp::Mesh> getMesh() const {
            return mesh_;
        }

    private:
        std::shared_ptr<threepp::Mesh> mesh_;
    };

    std::shared_ptr<Pawn> createPawn() {
        auto geometry = threepp::CylinderGeometry::create(0.5, 0.5, 1, 16);
        auto material = threepp::MeshStandardMaterial::create();
        material->color = threepp::Color::white;
        material->metalness = 0.5;
        material->roughness = 0.5;

        auto mesh = threepp::Mesh::create(geometry, material);
        auto pawn = std::make_shared<Pawn>(mesh);
        return pawn;
    }

} // namespace ChessPiecesGeometry

#endif