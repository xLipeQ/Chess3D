#pragma once
#include "Model.h"

enum ChessPieceType
{
    Pawn = 1,
    Knight = 2,
    Bishop = 3,
    King = 4,
    Rook = 5,
    Queen = 10
};

enum ChessPieceColor
{
    White = 1,
    Black = 2
};

class ChessPiece :
    public Model
{

public:
    ChessPieceType m_Type;
    ChessPieceColor m_Color;

    ChessPiece(std::shared_ptr<Mesh> Mesh, std::shared_ptr<Texture> Tex, ChessPieceType Type, ChessPieceColor color);
    ~ChessPiece();

};


