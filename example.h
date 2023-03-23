//
// Created by Kevin Silbernagel on 02/03/2023.
//
/*
#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <memory>
#include "threepp/threepp.hpp"
#include <threepp/textures/Texture.hpp>
#include <threepp/materials/MeshStandardMaterial.hpp>


using namespace threepp;

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
 #include "threepp/threepp.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>

using namespace threepp;

std::shared_ptr<BufferGeometry> loadStl(const std::string &filename) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filename, aiProcess_Triangulate);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Failed to load STL file: " << importer.GetErrorString() << std::endl;
        exit(1);
    }

    aiMesh *mesh = scene->mMeshes[0];

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

    auto geometry = BufferGeometry::create();
    geometry->setAttribute("position", FloatBufferAttribute::create(vertices, 3));
    geometry->setIndex(IntBufferAttribute::create(indices, 1));

    return geometry;
}

int main() {
    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color(0x808080));

    auto camera = PerspectiveCamera::create();
    camera->position.set(0, 0, 1);
    camera->lookAt(Vector3(0, 0, 0));

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();

    auto geometry = loadStl("/Users/kevinsilbernagel/CLionProjects/AIS1002-ProsjektOppgave/Knight.stl");

    auto material = MeshBasicMaterial::create();
    material->color = Color(0xffffff);
    auto mesh = Mesh::create(geometry, material);
    mesh->scale.set(0.01, 0.01, 0.01);
    scene->add(mesh);

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&] {
        renderer.render(scene, camera);
    });

    return 0;
}

*/
#include "ChessboardGeometry.h"
#include "chessPiecesGeometry.h"
#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"

using namespace threepp;

int main() {

    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color(0x708090));

    auto camera = PerspectiveCamera::create();
    camera->position.set(0, 20, 20);
    camera->lookAt(Vector3());

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();

    auto chessboard = ChessboardGeometry::create();
    scene->add(chessboard);

    auto directionalLight = DirectionalLight::create(0xffffff, 0.5);
    directionalLight->position.set(1, 1, 1);
    scene->add(directionalLight);

    auto ambientLight = AmbientLight::create(0x404040);
    scene->add(ambientLight);

    std::vector<std::shared_ptr<ChessPiece>> pieces = {
            std::make_shared<Pawn>(),
            std::make_shared<Rook>(),
            std::make_shared<Knight>(),
            std::make_shared<Bishop>(),
            std::make_shared<Queen>(),
            std::make_shared<King>(),
    };

    for (size_t i = 0; i < pieces.size(); ++i) {
        pieces[i]->mesh()->position.set(-3 + i * 1.5, 0.1, -4);
        scene->add(pieces[i]->mesh());
    }

    imgui_functional_context ui(canvas.window_ptr(), [&] {
        ImGui::SetNextWindowPos({0, 0}, 0, {0, 0});
        ImGui::SetNextWindowSize({230, 0}, 0);
        ImGui::Begin("Chess Controls");
        controls.enabled = !ImGui::IsWindowHovered();
        ImGui::Text("Press ESC to exit");
        ImGui::End();
    });

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&] {
        renderer.render(scene, camera);
        ui.render();
    });

    return 0;
}
