#ifndef THREEPP_VCPKG_TEST_CHESSBOARDGEOMETRY_H
#define THREEPP_VCPKG_TEST_CHESSBOARDGEOMETRY_H

#include "threepp/threepp.hpp"

using namespace threepp;

// Chessboard geometry
class ChessboardGeometry {
public:
    static std::shared_ptr<Object3D> create() {
        auto board = Object3D::create();

        // Create the chessboard mesh
        auto whiteMaterial = MeshBasicMaterial::create();
        whiteMaterial->color = Color(0xd2b48c); // set to light wooden color

        // Create the black square mesh
        auto blackMaterial = MeshBasicMaterial::create();
        blackMaterial->color = Color(0x5D5346);

        std::map<std::string, std::shared_ptr<Mesh>> squareMeshes;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                auto squareGeometry = BoxGeometry::create(1, 0.2, 1);
                auto squareMaterial = (i + j) % 2 == 0 ? blackMaterial : whiteMaterial;
                auto squareMesh = Mesh::create(squareGeometry, squareMaterial);
                squareMesh->position.x = i - 3.5;
                squareMesh->position.y = 0;
                squareMesh->position.z = j - 3.5;
                auto squareName = std::string(1, 'A' + i) + std::to_string(j + 1);
                squareMesh->name = squareName;
                board->add(squareMesh);

                squareMeshes[squareName] = squareMesh;
            }
        }

        auto borderGeometry = BoxGeometry::create(9, 0.2, 9);
        auto borderMaterial = MeshBasicMaterial::create();
        borderMaterial->color = Color(0xd2b48c);
        auto borderMesh = Mesh::create(borderGeometry, borderMaterial);
        borderMesh->position.y = -0.1;
        board->add(borderMesh);

        chessSquares = squareMeshes;

        return board;
    }

    static std::map<std::string, std::shared_ptr<Mesh>> chessSquares;
};

std::map<std::string, std::shared_ptr<Mesh>> ChessboardGeometry::chessSquares;

#endif //THREEPP_VCPKG_TEST_CHESSBOARDGEOMETRY_H
