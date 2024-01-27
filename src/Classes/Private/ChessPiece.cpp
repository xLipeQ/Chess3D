#include "../Public/ChessPiece.h"

ChessPiece::ChessPiece(std::shared_ptr<Mesh> Mesh, std::shared_ptr<Texture> Tex, ChessPieceType Type, ChessPieceColor color)
	: Model(Mesh, Tex)
{
	m_Type = Type;
	m_Color = color;
}

ChessPiece::~ChessPiece()
{
	Model::~Model();
}

