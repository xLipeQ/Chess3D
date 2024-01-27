#pragma once
#include "Model.h"
#include "ChessPiece.h"
#include "memory"
#define SIZE 8

class ChessBoard :
    public Model
{
private:

    // rows A-H
    // columns 1-8
    std::shared_ptr<ChessPiece> m_Board[SIZE][SIZE] = { nullptr };

public:
    
    ChessBoard(std::shared_ptr<Mesh> Mesh, std::shared_ptr<Texture> Tex, glm::vec3 pos);
    ~ChessBoard();

    void AddPiece(std::shared_ptr<ChessPiece> piece, int row, int column);

    void Draw(Shader& shader) const override;
};

