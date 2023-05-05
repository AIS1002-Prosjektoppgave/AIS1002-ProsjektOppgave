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

        std::shared_ptr<threepp::Mesh> getMesh() const {
            return mesh_;
        }

    private:
        std::shared_ptr<threepp::BufferGeometry> geometry_;
        std::shared_ptr<threepp::MeshBasicMaterial> material_;
        std::shared_ptr<threepp::Mesh> mesh_;

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

    // Denne klassen legger til sjakkbrikken: hvit bonde
    class WhitePawn : public ChessPieceGeometry {
    public:
        WhitePawn() : ChessPieceGeometry("Pawn.stl", threepp::Color(0xffffff)) {}
    };

    // Denne klassen legger til sjakkbrikken: svarte bonde
    class BlackPawn : public ChessPieceGeometry {
    public:
        BlackPawn() : ChessPieceGeometry("Pawn.stl", threepp::Color(0x000000)) {}
    };
    // Denne klassen legger til sjakkbrikken: hvit dronning
    class WhiteQueen : public ChessPieceGeometry {
    public:
        WhiteQueen() : ChessPieceGeometry("King.stl", threepp::Color(0xffffff)) {}
    };

// Denne klassen legger til sjakkbrikken: svart dronning
    class BlackQueen : public ChessPieceGeometry {
    public:
        BlackQueen() : ChessPieceGeometry("King.stl", threepp::Color(0x000000)) {}
    };

// Denne klassen legger til sjakkbrikken: hvit konge
    class WhiteKing : public ChessPieceGeometry {
    public:
        WhiteKing() : ChessPieceGeometry("Queen.STL", threepp::Color(0xffffff)) {}
    };

// Denne klassen legger til sjakkbrikken: svart konge
    class BlackKing : public ChessPieceGeometry {
    public:
        BlackKing() : ChessPieceGeometry("Queen.STL", threepp::Color(0x000000)) {}
    };

// Denne klassen legger til sjakkbrikken: hvit løper
    class WhiteBishop : public ChessPieceGeometry {
    public:
        WhiteBishop() : ChessPieceGeometry("Bishop.STL", threepp::Color(0xffffff)) {}
    };

// Denne klassen legger til sjakkbrikken: svart løper
    class BlackBishop : public ChessPieceGeometry {
    public:
        BlackBishop() : ChessPieceGeometry("Bishop.STL", threepp::Color(0x000000)) {}
    };

// Denne klassen legger til sjakkbrikken: hvit hest
    class WhiteKnight : public ChessPieceGeometry {
    public:
        WhiteKnight() : ChessPieceGeometry("Knight.STL", threepp::Color(0xffffff)) {}
    };

// Denne klassen legger til sjakkbrikken: svart hest
    class BlackKnight : public ChessPieceGeometry {
    public:
        BlackKnight() : ChessPieceGeometry("Knight.STL", threepp::Color(0x000000)) {}
    };

// Denne klassen legger til sjakkbrikken: hvit tårn
    class WhiteRook : public ChessPieceGeometry {
    public:
        WhiteRook() : ChessPieceGeometry("Rook.STL", threepp::Color(0xffffff)) {}
    };

// Denne klassen legger til sjakkbrikken: svart tårn
    class BlackRook : public ChessPieceGeometry {
    public:
        BlackRook() : ChessPieceGeometry("Rook.STL", threepp::Color(0x000000)) {}
    };
}

#endif //THREEPP_VCPKG_TEST_CHESSPIECESGEOMETRY_H