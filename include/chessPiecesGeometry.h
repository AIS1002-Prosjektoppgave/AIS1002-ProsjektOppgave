#ifndef THREEPP_VCPKG_TEST_CHESSPIECESGEOMETRY_H
#define THREEPP_VCPKG_TEST_CHESSPIECESGEOMETRY_H

#include <threepp/threepp.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <vector>
#include <threepp/core/Object3D.hpp>

namespace ChessPiecesGeometry {

    // Dinna classen oppretter geometrien for sjakkbrikkene og sjakkbrettet
    class ChessPieceGeometry : public threepp::Object3D {
    public:
        ChessPieceGeometry(const std::string& filename, const threepp::Color& color) {
            geometry_ = loadStl(filename);
            material_ = threepp::MeshBasicMaterial::create();
            material_->color = color;
            mesh_ = threepp::Mesh::create(geometry_, material_);
            name = "chess_piece";
            mesh_->scale.set(0.01, 0.01, 0.01);
            mesh_->renderOrder = 1;
        }

        [[nodiscard]] std::shared_ptr<threepp::Mesh> getMesh() const {
            return mesh_;
        }

        static std::vector<std::shared_ptr<ChessPieceGeometry>>& getAllPieces() {
            return allPieces;
        }

    private:
        std::shared_ptr<threepp::BufferGeometry> geometry_;
        std::shared_ptr<threepp::MeshBasicMaterial> material_;
        std::shared_ptr<threepp::Mesh> mesh_;
        static std::vector<std::shared_ptr<ChessPieceGeometry>> allPieces;

        static std::shared_ptr<threepp::BufferGeometry> loadStl(const std::string& filename) {
            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate);

            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
                std::cerr << "Failed to load STL file: " << importer.GetErrorString() << std::endl;
                exit(1);
            }

            aiMesh* mesh = scene->mMeshes[0];

            std::vector<float> vertices;
            std::vector<int> indices;

            vertices.reserve(mesh->mNumVertices * 3);
            for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
                vertices.push_back(mesh->mVertices[i].x);
                vertices.push_back(mesh->mVertices[i].y);
                vertices.push_back(mesh->mVertices[i].z);
            }

            indices.reserve(mesh->mNumFaces * 3);
            for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
                aiFace face = mesh->mFaces[i];
                for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                    indices.push_back(face.mIndices[j]);
                }
            }

            auto geometry = threepp::BufferGeometry::create();
            geometry->setAttribute("position", threepp::FloatBufferAttribute::create(vertices, 3));
            geometry->setIndex(threepp::IntBufferAttribute::create(indices, 1));

            return geometry;
        }
    };

    std::vector<std::shared_ptr<ChessPieceGeometry>> ChessPieceGeometry::allPieces = {};

    // Denne klassen legger til sjakkbrikken: hvit bonde
    class Pawn : public ChessPieceGeometry {
    public:
        Pawn(const threepp::Color& color) : ChessPieceGeometry("data/Pawn.stl", color) {}
    };

    // Denne klassen legger til sjakkbrikken: hvit dronning
    class Queen : public ChessPieceGeometry {
    public:
        Queen(const threepp::Color& color) : ChessPieceGeometry("data/King.stl", color) {}
    };

// Denne klassen legger til sjakkbrikken: hvit konge
    class King : public ChessPieceGeometry {
    public:
        King(const threepp::Color& color) : ChessPieceGeometry("data/Queen.stl", color) {}
    };

// Denne klassen legger til sjakkbrikken: hvit løper
    class Bishop : public ChessPieceGeometry {
    public:
        Bishop(const threepp::Color& color) : ChessPieceGeometry("data/Bishop.stl", color) {}
    };

// Denne klassen legger til sjakkbrikken: hvit hest
    class Knight : public ChessPieceGeometry {
    public:
        Knight(const threepp::Color& color) : ChessPieceGeometry("data/Knight.stl", color) {}
    };

// Denne klassen legger til sjakkbrikken: hvit tårn
    class Rook : public ChessPieceGeometry {
    public:
        Rook(const threepp::Color& color) : ChessPieceGeometry("data/Rook.stl", color) {}
    };
}

#endif //THREEPP_VCPKG_TEST_CHESSPIECESGEOMETRY_H