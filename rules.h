#ifndef CHESS_RULES_H
#define CHESS_RULES_H

#include <string>
#include <map>
#include <cmath>
#include <algorithm>

class Rules {
public:
    static bool isValidMove(const std::string &pieceName, const std::string &initialSquare, const std::string &targetSquare, const std::map<std::string, std::string> &chessPiecePositions) {
        if (!isWithinBoard(initialSquare) || !isWithinBoard(targetSquare)) {
            return false;
        }

        bool isWhite = (pieceName.find("white") != std::string::npos);

        if (pieceName == "white_pawn" || pieceName == "black_pawn") {
            return isValidPawnMove(initialSquare, targetSquare, chessPiecePositions, isWhite);
        } else if (pieceName == "white_rook" || pieceName == "black_rook") {
            return isValidRookMove(initialSquare, targetSquare, chessPiecePositions, isWhite);
        } else if (pieceName == "white_knight" || pieceName == "black_knight") {
            return isValidKnightMove(initialSquare, targetSquare);
        } else if (pieceName == "white_bishop" || pieceName == "black_bishop") {
            return isValidBishopMove(initialSquare, targetSquare, chessPiecePositions, isWhite);
        } else if (pieceName == "white_queen" || pieceName == "black_queen") {
            return isValidQueenMove(initialSquare, targetSquare, chessPiecePositions, isWhite);
        } else if (pieceName == "white_king" || pieceName == "black_king") {
            return isValidKingMove(initialSquare, targetSquare, chessPiecePositions, isWhite);
        } else {
            return false;
        }
    }

    static bool isValidPawnMove(const std::string &initialSquare, const std::string &targetSquare, const std::map<std::string, std::string> &chessPiecePositions, bool isWhite) {
        int rankDirection = isWhite ? 1 : -1;
        int rankMove = (targetSquare[1] - initialSquare[1]) * rankDirection;
        int fileMove = std::abs(targetSquare[0] - initialSquare[0]);

        if (rankMove == 1 && fileMove == 0) {
            bool isWhiteTmp;
            return !isSquareOccupied(targetSquare, chessPiecePositions, isWhiteTmp);
        } else if (rankMove == 2 && fileMove == 0 && (isWhite ? initialSquare[1] == '2' : initialSquare[1] == '7')) {
            std::string middleSquare = initialSquare.substr(0, 1) + static_cast<char>(initialSquare[1] + rankDirection);
            bool isWhiteTmp;
            return !isSquareOccupied(middleSquare, chessPiecePositions, isWhiteTmp) && !isSquareOccupied(targetSquare, chessPiecePositions, isWhiteTmp);
        } else if (rankMove == 1 && fileMove == 1) {
            bool isWhiteTmp;
            if (isSquareOccupied(targetSquare, chessPiecePositions, isWhiteTmp)) {
                return isWhiteTmp != isWhite;
            }
        }

        return false;
    }


    static bool isValidRookMove(const std::string &initialSquare, const std::string &targetSquare, const std::map<std::string, std::string> &chessPiecePositions, bool isWhite) {
        int rankMove = std::abs(targetSquare[1] - initialSquare[1]);
        int fileMove = std::abs(targetSquare[0] - initialSquare[0]);

        if (rankMove == 0 && fileMove > 0) {
            // Horizontal move
            int step = targetSquare[0] > initialSquare[0] ? 1 : -1;
            for (char file = initialSquare[0] + step; file != targetSquare[0]; file += step) {
                std::string square(1, file);
                square += initialSquare[1];
                bool isWhiteTmp;
                if (isSquareOccupied(square, chessPiecePositions, isWhiteTmp) && isWhiteTmp != isWhite) {
                    return false;
                }

            }
            return true;
        } else if (fileMove == 0 && rankMove > 0) {
            // Vertical move
            int step = targetSquare[1] > initialSquare[1] ? 1 : -1;
            for (char rank = initialSquare[1] + step; rank != targetSquare[1]; rank += step) {
                std::string square = initialSquare.substr(0, 1) + rank;
                if (isSquareOccupied(square, chessPiecePositions, isWhite)) {
                    return false;
                }
            }
            return true;
        } else {
            return false;
        }
    }

    static bool isValidKnightMove(const std::string &initialSquare, const std::string &targetSquare) {
        int rankMove = std::abs(targetSquare[1] - initialSquare[1]);
        int fileMove = std::abs(targetSquare[0] - initialSquare[0]);

        return (rankMove == 2 && fileMove == 1) || (rankMove == 1 && fileMove == 2);
    }

    static bool isValidBishopMove(const std::string &initialSquare, const std::string &targetSquare, const std::map<std::string, std::string> &chessPiecePositions, bool isWhite) {
        int rankMove = std::abs(targetSquare[1] - initialSquare[1]);
        int fileMove = std::abs(targetSquare[0] - initialSquare[0]);

        if (rankMove == fileMove) {
            int rankStep = targetSquare[1] > initialSquare[1] ? 1 : -1;
            int fileStep = targetSquare[0] > initialSquare[0] ? 1 : -1;
            char rank = initialSquare[1] + rankStep;
            char file = initialSquare[0] + fileStep;

            while (rank != targetSquare[1] && file != targetSquare[0]) {
                std::string square(1, file);
                square += rank;
                bool isWhiteTmp;
                if (isSquareOccupied(square, chessPiecePositions, isWhiteTmp) && isWhiteTmp != isWhite) {
                    return false;
                }

                rank += rankStep;
                file += fileStep;
            }
            return true;
        } else {
            return false;
        }
    }

    static bool isValidQueenMove(const std::string &initialSquare, const std::string &targetSquare, const std::map<std::string, std::string> &chessPiecePositions, bool isWhite) {
        return isValidRookMove(initialSquare, targetSquare, chessPiecePositions, isWhite) || isValidBishopMove(initialSquare, targetSquare, chessPiecePositions, isWhite);
    }

    static bool isValidKingMove(const std::string &initialSquare, const std::string &targetSquare, const std::map<std::string, std::string> &chessPiecePositions, bool isWhite) {
        int rankDifference = std::abs(targetSquare[1] - initialSquare[1]);
        int fileDifference = std::abs(targetSquare[0] - initialSquare[0]);

        if (rankDifference <= 1 && fileDifference <= 1) {
            bool isWhiteTmp;
            if (!isSquareOccupied(targetSquare, chessPiecePositions, isWhiteTmp) || (isWhiteTmp != isWhite)) {
                return true;
            }
        }

        return false;
    }

    static bool isSquareOccupied(const std::string &square, const std::map<std::string, std::string> &chessPiecePositions, bool &isWhite) {
        auto pieceIter = chessPiecePositions.find(square);
        if (pieceIter != chessPiecePositions.end()) {
            isWhite = (pieceIter->second.find("white") != std::string::npos);
            return true;
        }
        return false;
    }

    static bool isWithinBoard(const std::string &square) {
        if (square.size() != 2) {
            return false;
        }

        char file = square[0];
        char rank = square[1];

        return (file >= 'A' && file <= 'H' && rank >= '1' && rank <= '8');
    }
};

#endif // CHESS_RULES_H
