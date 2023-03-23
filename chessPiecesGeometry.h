#ifndef THREEPP_VCPKG_TEST_CHESSPIECESGEOMETRY_H
#define THREEPP_VCPKG_TEST_CHESSPIECESGEOMETRY_H

#include "threepp/threepp.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>

namespace ChessPiecesGeometry {

    // Base class for creating chess piece geometries
    class ChessPieceGeometry {
    public:
        ChessPieceGeometry(const std::string& filename, const threepp::Color& color) {
            geometry_ = loadStl(filename);
            material_ = threepp::MeshBasicMaterial::create();
            material_->color = color;
            mesh_ = threepp::Mesh::create(geometry_, material_);
            mesh_->scale.set(0.01, 0.01, 0.01);
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

    // Class for creating a white pawn geometry
    class WhitePawn : public ChessPieceGeometry {
    public:
        WhitePawn() : ChessPieceGeometry("/Users/kevinsilbernagel/CLionProjects/AIS1002-ProsjektOppgave/Pawn.stl", threepp::Color(0xffffff)) {}
    };

    // Class for creating a black pawn geometry
    class BlackPawn : public ChessPieceGeometry {
    public:
        BlackPawn() : ChessPieceGeometry("/Users/kevinsilbernagel/CLionProjects/AIS1002-ProsjektOppgave/Pawn.stl", threepp::Color(0x000000)) {}
        };
        // Class for creating a white queen geometry
        class WhiteQueen : public ChessPieceGeometry {
        public:
            WhiteQueen() : ChessPieceGeometry("/Users/kevinsilbernagel/CLionProjects/AIS1002-ProsjektOppgave/Queen.stl", threepp::Color(0xffffff)) {}
        };

// Class for creating a black queen geometry
        class BlackQueen : public ChessPieceGeometry {
        public:
            BlackQueen() : ChessPieceGeometry("/Users/kevinsilbernagel/CLionProjects/AIS1002-ProsjektOppgave/Queen.stl", threepp::Color(0x000000)) {}
        };

// Class for creating a white king geometry
        class WhiteKing : public ChessPieceGeometry {
        public:
            WhiteKing() : ChessPieceGeometry("/Users/kevinsilbernagel/CLionProjects/AIS1002-ProsjektOppgave/King.stl", threepp::Color(0xffffff)) {}
        };

// Class for creating a black king geometry
        class BlackKing : public ChessPieceGeometry {
        public:
            BlackKing() : ChessPieceGeometry("/Users/kevinsilbernagel/CLionProjects/AIS1002-ProsjektOppgave/King.stl", threepp::Color(0x000000)) {}
        };

// Class for creating a white bishop geometry
        class WhiteBishop : public ChessPieceGeometry {
        public:
            WhiteBishop() : ChessPieceGeometry("/Users/kevinsilbernagel/CLionProjects/AIS1002-ProsjektOppgave/Bishop.stl", threepp::Color(0xffffff)) {}
        };

// Class for creating a black bishop geometry
        class BlackBishop : public ChessPieceGeometry {
        public:
            BlackBishop() : ChessPieceGeometry("/Users/kevinsilbernagel/CLionProjects/AIS1002-ProsjektOppgave/Bishop.stl", threepp::Color(0x000000)) {}
        };

// Class for creating a white knight geometry
        class WhiteKnight : public ChessPieceGeometry {
        public:
            WhiteKnight() : ChessPieceGeometry("/Users/kevinsilbernagel/CLionProjects/AIS1002-ProsjektOppgave/Knight.stl", threepp::Color(0xffffff)) {}
        };

// Class for creating a black knight geometry
        class BlackKnight : public ChessPieceGeometry {
        public:
            BlackKnight() : ChessPieceGeometry("/Users/kevinsilbernagel/CLionProjects/AIS1002-ProsjektOppgave/Knight.stl", threepp::Color(0x000000)) {}
        };

// Class for creating a white rook geometry
        class WhiteRook : public ChessPieceGeometry {
        public:
            WhiteRook() : ChessPieceGeometry("/Users/kevinsilbernagel/CLionProjects/AIS1002-ProsjektOppgave/Rook.stl", threepp::Color(0xffffff)) {}
        };

// Class for creating a black rook geometry
        class BlackRook : public ChessPieceGeometry {
        public:
            BlackRook() : ChessPieceGeometry("/Users/kevinsilbernagel/CLionProjects/AIS1002-ProsjektOppgave/Rook.stl", threepp::Color(0x000000)) {}
        };
    };

#endif //THREEPP_VCPKG_TEST_CHESSPIECESGEOMETRY_H