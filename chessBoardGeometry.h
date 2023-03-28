#ifndef THREEPP_VCPKG_TEST_CHESSBOARDGEOMETRY_H
#define THREEPP_VCPKG_TEST_CHESSBOARDGEOMETRY_H

#include "threepp/threepp.hpp"
#include <vector>

using namespace threepp;


class ChessboardGeometry {
public:
    static std::shared_ptr<Object3D> create() {
        auto board = Object3D::create();

        // Create the chessboard mesh
        auto whiteGeometry = BoxGeometry::create(8, 0.2, 8);
        auto whiteMaterial = MeshBasicMaterial::create();
        whiteMaterial->color = Color(0xd2b48c); // set to light wooden color
        auto whiteMesh = Mesh::create(whiteGeometry, whiteMaterial);
        whiteMesh->position.y = 0;

        // Create white border mesh
        auto borderGeometry = BoxGeometry::create(8.01, 0.2, 8.01); // add thickness of +0.01
        auto borderMaterial = MeshBasicMaterial::create();
        borderMaterial->color = Color(0xd2b48c);
        auto borderMesh = Mesh::create(borderGeometry, borderMaterial);
        borderMesh->position.y = 0.111;

        // Add empty space within the border
        auto emptyGeometry = BoxGeometry::create(7.8, 0.2, 7.8);
        auto emptyMaterial = MeshBasicMaterial::create();
        emptyMaterial->color = Color::white;
        auto emptyMesh = Mesh::create(emptyGeometry, emptyMaterial);
        emptyMesh->position.y = 0.11;
        whiteMesh->add(emptyMesh);

        auto blackGeometry = BoxGeometry::create(1, 0.2, 1);
        auto blackMaterial = MeshBasicMaterial::create();
        blackMaterial->color = Color(0x5D5346);

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i + j) % 2 == 0) {
                    auto blackMesh = Mesh::create(blackGeometry, blackMaterial);
                    blackMesh->position.x = i - 3.5;
                    blackMesh->position.y = 0.01;
                    blackMesh->position.z = j - 3.5;
                    emptyMesh->add(blackMesh); // add black squares to the empty space within the border
                }
            }
        }

        board->add(whiteMesh);
        board->add(borderMesh);
        return board;
    }
};

#endif //THREEPP_VCPKG_TEST_CHESSBOARDGEOMETRY_H