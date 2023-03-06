//
// Created by Kevin Silbernagel on 02/03/2023.
//

#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <memory>
#include "threepp/threepp.hpp"

using namespace threepp;

test
class Knight {
public:
    Knight() {
        auto geometry = CylinderGeometry::create(0, 0.5, 1.5, 32, 1, true);
        auto material = MeshStandardMaterial::create();
        material->color = Color::white;
        material->metalness = 0.8;
        material->roughness = 0.4;

        auto base = CylinderGeometry::create(0.5, 0.5, 0.3, 32);
        auto baseMesh = Mesh::create(base, material);
        baseMesh->position.y = -0.8;

        auto head = SphereGeometry::create(0.5, 32, 32);
        auto headMesh = Mesh::create(head, material);
        headMesh->position.y = -0.1;

        auto top = ConeGeometry::create(0.5, 1, 32);
        auto topMesh = Mesh::create(top, material);
        topMesh->position.y = 0.4;

        mesh_ = Object3D::create();
        mesh_->add(baseMesh);
        mesh_->add(headMesh);
        mesh_->add(topMesh);
    }

    std::shared_ptr<Object3D> mesh() { return mesh_; }

private:
    std::shared_ptr<Object3D> mesh_;
};


class King {
public:
    King() {
        auto geometry = CylinderGeometry::create(0, 0.5, 1.3, 32, 1, true);
        auto material = MeshStandardMaterial::create();
        material->color = Color::white;
        material->metalness = 0.8;
        material->roughness = 0.4;

        auto base = CylinderGeometry::create(0.5, 0.5, 0.3, 32);
        auto baseMesh = Mesh::create(base, material);
        baseMesh->position.y = 0;

        auto head = SphereGeometry::create(0.6, 32, 32);
        auto headMesh = Mesh::create(head, material);
        headMesh->position.y = 0.7;

        auto top = CylinderGeometry::create(0.2, 0.2, 1.2, 32);
        auto topMesh = Mesh::create(top, material);
        topMesh->position.y = 1.6;

        mesh_ = Object3D::create();
        mesh_->add(baseMesh);
        mesh_->add(headMesh);
        mesh_->add(topMesh);
    }

    std::shared_ptr<Object3D> mesh() { return mesh_; }

private:
    std::shared_ptr<Object3D> mesh_;
};

class Pawn {
public:
    Pawn() {
        auto geometry = BoxGeometry::create(0.7, 0.7, 1.5);
        auto material = MeshStandardMaterial::create();
        material->color = Color::white;
        material->metalness = 0.8;
        material->roughness = 0.4;

        auto base = BoxGeometry::create(0.7, 0.7, 0.2);
        auto baseMesh = Mesh::create(base, material);
        baseMesh->position.y = -0.8;

        auto top = SphereGeometry::create(0.4, 32, 32);
        auto topMesh = Mesh::create(top, material);
        topMesh->position.y = 0;

        mesh_ = Object3D::create();
        mesh_->add(baseMesh);
        mesh_->add(topMesh);
    }

    std::shared_ptr<Object3D> mesh() { return mesh_; }

private:
    std::shared_ptr<Object3D> mesh_;
};


class Tower {
public:
    Tower() {
        auto bodyGeometry = BoxGeometry::create(0.6, 1.2, 0.6);
        auto bodyMaterial = MeshStandardMaterial::create();
        bodyMaterial->color = Color::white;
        bodyMaterial->metalness = 0.5;
        bodyMaterial->roughness = 0.5;

        auto roofGeometry = BoxGeometry::create(1.0, 0.4, 1.4);
        auto roofMaterial = MeshStandardMaterial::create();
        roofMaterial->color = Color::white;
        roofMaterial->metalness = 0.8;
        roofMaterial->roughness = 0.4;

        auto bodyMesh = Mesh::create(bodyGeometry, bodyMaterial);
        bodyMesh->position.y = -0.5;

        auto roofMesh = Mesh::create(roofGeometry, roofMaterial);
        roofMesh->position.y = 0.5;

        mesh_ = Object3D::create();
        mesh_->add(bodyMesh);
        mesh_->add(roofMesh);
    }

    std::shared_ptr<Object3D> mesh() { return mesh_; }

private:
    std::shared_ptr<Object3D> mesh_;
};


class Rook {
public:
    Rook() {
        auto geometry = BoxGeometry::create(1, 1, 2.5);
        auto material = MeshStandardMaterial::create();
        material->color = Color::white;
        material->metalness = 0.8;
        material->roughness = 0.4;

        auto base = BoxGeometry::create(1, 1, 0.2);
        auto baseMesh = Mesh::create(base, material);
        baseMesh->position.y = -0.5;

        auto top = BoxGeometry::create(0.8, 0.8, 0.8);
        auto topMesh = Mesh::create(top, material);
        topMesh->position.y = 0.6;

        mesh_ = Object3D::create();
        mesh_->add(baseMesh);
        mesh_->add(topMesh);
    }

    std::shared_ptr<Object3D> mesh() { return mesh_; }

private:
    std::shared_ptr<Object3D> mesh_;
};


class Queen {
public:
    Queen() {
        auto geometry = ConeGeometry::create(0, 0.8, 1.6, 32, 1, true);
        auto material = MeshStandardMaterial::create();
        material->color = Color::white;
        material->metalness = 0.8;
        material->roughness = 0.4;

        auto base = CylinderGeometry::create(0.5, 0.5, 0.3, 32);
        auto baseMesh = Mesh::create(base, material);
        baseMesh->position.y = -0.9;

        auto head = SphereGeometry::create(0.6, 32, 32);
        auto headMesh = Mesh::create(head, material);
        headMesh->position.y = -0.1;

        auto top = CylinderGeometry::create(0.5, 0.2, 1, 32);
        auto topMesh = Mesh::create(top, material);
        topMesh->position.y = 0.3;

        auto cross1 = BoxGeometry::create(0.1, 1, 0.1);
        auto crossMesh1 = Mesh::create(cross1, material);
        crossMesh1->position.set(0, 1, 0);

        auto cross2 = BoxGeometry::create(0.1, 1, 0.1);
        auto crossMesh2 = Mesh::create(cross2, material);
        crossMesh2->position.set(0, 1, 0);
        crossMesh2->rotation.z = math::PI / 4;

        auto cross3 = BoxGeometry::create(0.1, 1, 0.1);
        auto crossMesh3 = Mesh::create(cross3, material);
        crossMesh3->position.set(0, 1, 0);
        crossMesh3->rotation.z = -math::PI / 4;

        mesh_ = Object3D::create();
        mesh_->add(baseMesh);
        mesh_->add(headMesh);
        mesh_->add(topMesh);
        mesh_->add(crossMesh1);
        mesh_->add(crossMesh2);
        mesh_->add(crossMesh3);
    }

    std::shared_ptr<Object3D> mesh() { return mesh_; }

private:
    std::shared_ptr<Object3D> mesh_;
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
