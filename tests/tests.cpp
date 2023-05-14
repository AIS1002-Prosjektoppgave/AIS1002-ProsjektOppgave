#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../include/controls.h"
#include "../include/chessBoardGeometry.h"
#include "../include/chessPiecesGeometry.h"
#include "../include/rules.h"


// Definerer en nødvendig stub-klasse direkte i denne filen
class StubPerspectiveCamera : public PerspectiveCamera {
public:
    StubPerspectiveCamera() : PerspectiveCamera(75, 1.0, 0.1, 1000) {} };

// Noen nødvendige objekter for testing
std::shared_ptr<threepp::Scene> scene = std::make_shared<threepp::Scene>();
threepp::Canvas canvas;

TEST_CASE("Controls Class Functionality", "[Controls]") {
    std::shared_ptr<PerspectiveCamera> camera = std::make_shared<StubPerspectiveCamera>();
    Controls controls(camera, canvas, scene);

    SECTION("Update Raycaster Line") {
        controls.updateRaycasterLine();
        auto positions = static_cast<threepp::TypedBufferAttribute<float> *>(controls.getRayLine()->geometry()->getAttribute<float>("position"))->array();
        REQUIRE(positions[0] == Approx(0.0f));
        REQUIRE(positions[1] == Approx(0.0f));
        REQUIRE(positions[2] == Approx(0.0f));
    }

    SECTION("Update Controls") {
        controls.update();
        REQUIRE(controls.selectedRawMesh_ == nullptr);
    }

    SECTION("Reset Selected Piece State") {
        controls.resetSelectedPieceState();
        REQUIRE(controls.selectedRawMesh_ == nullptr);
        REQUIRE(controls.getSelectDestination() == false);
    }

    SECTION("On Mouse Down") {
        threepp::Vector2 mousePos(500, 400);
        controls.onMouseDown(mousePos);
        REQUIRE(controls.getMouseDown() == true);
    }

    SECTION("Move Selected Mesh To") {
        auto mesh = threepp::Mesh::create();
        mesh->position.set(1.0f, 1.0f, 1.0f);
        controls.selectedRawMesh_ = mesh.get();
        controls.getSelectedMeshOriginalPosition() = mesh->position;
        threepp::Vector3 newPosition(2.0f, 2.0f, 2.0f);
        controls.moveSelectedMeshTo(newPosition);
        REQUIRE(controls.selectedRawMesh_->position.x == Approx(2.0f));
        REQUIRE(controls.selectedRawMesh_->position.y == Approx(0.0f));
        REQUIRE(controls.selectedRawMesh_->position.z == Approx(2.0f));
    }
}

TEST_CASE("ChessboardGeometry Class Functionality", "[ChessboardGeometry]") {
    auto chessBoard = ChessboardGeometry::create();

    SECTION("Nearest Square Calculation") {
        threepp::Vector3 position(2.3f, 0.f, 3.7f);
        threepp::Vector3 nearest = ChessboardGeometry::getNearestSquare(position);

        REQUIRE(nearest.x == Approx(2.5f));
        REQUIRE(nearest.y == Approx(0.0f));
        REQUIRE(nearest.z == Approx(3.5f));
    }
}

TEST_CASE("Chessboard Mesh Creation and Positioning", "[ChessboardGeometry]") {
    auto chessBoard = ChessboardGeometry::create();

    REQUIRE(chessBoard->children.size() == 65);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            auto squareName = std::string(1, 'A' + i) + std::to_string(j + 1);
            auto squareMesh = ChessboardGeometry::chessSquares[squareName];
            REQUIRE(squareMesh->position.x == Approx(i - 3.5f));
            REQUIRE(squareMesh->position.y == Approx(0.0f));
            REQUIRE(squareMesh->position.z == Approx(j - 3.5f));
        }
    }
}

TEST_CASE("Chessboard Square Color Assignment", "[ChessboardGeometry]") {
    auto chessBoard = ChessboardGeometry::create();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            auto squareName = std::string(1, 'A' + i) + std::to_string(j + 1);
            auto squareMesh = ChessboardGeometry::chessSquares[squareName];
            auto squareMaterial = dynamic_cast<MeshBasicMaterial*>(squareMesh->material());
            REQUIRE(squareMaterial != nullptr);
            if ((i + j) % 2 == 0) {
                REQUIRE(squareMaterial->color == Color(0x5D5346));
            } else {
                REQUIRE(squareMaterial->color == Color(0xd2b48c));
            }
        }
    }
}

TEST_CASE("Chessboard Border Creation and Positioning", "[ChessboardGeometry]") {
    auto chessBoard = ChessboardGeometry::create();

    auto borderMesh = chessBoard->children.back();
    auto borderMaterial = dynamic_cast<MeshBasicMaterial*>(borderMesh->material());

    REQUIRE(borderMesh->position.y == Approx(-0.1f));
    REQUIRE(borderMaterial != nullptr);
    REQUIRE(borderMaterial->color == Color(0xd2b48c));
}


using namespace ChessPiecesGeometry;

TEST_CASE("ChessPieceGeometry Tests", "[ChessPieceGeometry]") {

    SECTION("Creating a Pawn") {
        Pawn pawn(threepp::Color(1,1,1));
        REQUIRE(pawn.getMesh() != nullptr);
        REQUIRE(pawn.getMesh()->scale.x == Approx(0.015));
        REQUIRE(pawn.getMesh()->scale.y == Approx(0.015));
        REQUIRE(pawn.getMesh()->scale.z == Approx(0.015));
    }

    SECTION("Creating a Queen") {
        Queen queen(threepp::Color(1,1,1));
        REQUIRE(queen.getMesh() != nullptr);
        REQUIRE(queen.getMesh()->scale.x == Approx(0.015));
        REQUIRE(queen.getMesh()->scale.y == Approx(0.015));
        REQUIRE(queen.getMesh()->scale.z == Approx(0.015));
    }

    SECTION("Creating a King") {
        King king(threepp::Color(1,1,1));
        REQUIRE(king.getMesh() != nullptr);
        REQUIRE(king.getMesh()->scale.x == Approx(0.015));
        REQUIRE(king.getMesh()->scale.y == Approx(0.015));
        REQUIRE(king.getMesh()->scale.z == Approx(0.015));
    }

    SECTION("Creating a Bishop") {
        Bishop bishop(threepp::Color(1,1,1));
        REQUIRE(bishop.getMesh() != nullptr);
        REQUIRE(bishop.getMesh()->scale.x == Approx(0.015));
        REQUIRE(bishop.getMesh()->scale.y == Approx(0.015));
        REQUIRE(bishop.getMesh()->scale.z == Approx(0.015));
    }

    SECTION("Creating a Knight") {
        Knight knight(threepp::Color(1,1,1));
        REQUIRE(knight.getMesh() != nullptr);
        REQUIRE(knight.getMesh()->scale.x == Approx(0.015));
        REQUIRE(knight.getMesh()->scale.y == Approx(0.015));
        REQUIRE(knight.getMesh()->scale.z == Approx(0.015));
    }

    SECTION("Creating a Rook") {
        Rook rook(threepp::Color(1,1,1));
        REQUIRE(rook.getMesh() != nullptr);
        REQUIRE(rook.getMesh()->scale.x == Approx(0.015));
        REQUIRE(rook.getMesh()->scale.y == Approx(0.015));
        REQUIRE(rook.getMesh()->scale.z == Approx(0.015));
    }
}

TEST_CASE("Rules Class Functionality", "[Rules]") {

    std::map<std::string, std::string> chessPiecePositions;

    SECTION("Valid Pawn Move") {
        chessPiecePositions.clear();
        chessPiecePositions["E5"] = "white_pawn";
        REQUIRE(Rules::isValidMove("white_pawn", "E5", "E6", chessPiecePositions) == true);
        REQUIRE(Rules::isValidMove("white_pawn", "E5", "E4", chessPiecePositions) == false);
    }

    SECTION("Valid Rook Move") {
        chessPiecePositions.clear();
        chessPiecePositions["H1"] = "white_rook";
        REQUIRE(Rules::isValidMove("white_rook", "H1", "H8", chessPiecePositions) == true);
        REQUIRE(Rules::isValidMove("white_rook", "H1", "E5", chessPiecePositions) == false);
    }

    SECTION("Valid Knight Move") {
        chessPiecePositions.clear();
        chessPiecePositions["B1"] = "white_knight";
        REQUIRE(Rules::isValidMove("white_knight", "B1", "C3", chessPiecePositions) == true);
        REQUIRE(Rules::isValidMove("white_knight", "B1", "B2", chessPiecePositions) == false);
    }

    SECTION("Valid Bishop Move") {
        chessPiecePositions.clear();
        chessPiecePositions["C1"] = "white_bishop";
        REQUIRE(Rules::isValidMove("white_bishop", "C1", "G5", chessPiecePositions) == true);
        REQUIRE(Rules::isValidMove("white_bishop", "C1", "C4", chessPiecePositions) == false);
    }

    SECTION("Valid Queen Move") {
        chessPiecePositions.clear();
        chessPiecePositions["D1"] = "white_queen";
        REQUIRE(Rules::isValidMove("white_queen", "D1", "H5", chessPiecePositions) == true);
        REQUIRE(Rules::isValidMove("white_queen", "D1", "H6", chessPiecePositions) == false);
    }

    SECTION("Valid King Move") {
        chessPiecePositions.clear();
        chessPiecePositions["E1"] = "white_king";
        REQUIRE(Rules::isValidMove("white_king", "E1", "E2", chessPiecePositions) == true);
        REQUIRE(Rules::isValidMove("white_king", "E1", "E3", chessPiecePositions) == false);
    }

    SECTION("Invalid piece") {
        REQUIRE(Rules::isValidMove("white_unicorn", "A1", "A2", chessPiecePositions) == false);
    }

    SECTION("Outside of board") {
        REQUIRE(Rules::isWithinBoard("I9") == false);
    }

    SECTION("Square Occupied") {
        chessPiecePositions.clear();
        chessPiecePositions["E5"] = "white_pawn";
        bool isWhite;
        REQUIRE(Rules::isSquareOccupied("E5", chessPiecePositions, isWhite) == true);
        REQUIRE(isWhite == true);
        REQUIRE(Rules::isSquareOccupied("E6", chessPiecePositions, isWhite) == false);
    }
}


