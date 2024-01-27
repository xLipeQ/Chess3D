#include "../Public/ChessBoard.h"

ChessBoard::ChessBoard(std::shared_ptr<Mesh> Mesh, std::shared_ptr<Texture> Tex, glm::vec3 pos) : Model(Mesh, Tex, pos)
{

}

ChessBoard::~ChessBoard()
{
}

void ChessBoard::Draw(Shader& shader) const
{
	shader.SetUniform4f("u_Color", 0.4f, 0.4f, 0.4f, 1.f);
	Model::Draw(shader);

	// position of A1 sqaurre - center
	glm::vec3 A1Position(-3.5f, -1.9f, 3.5f);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (m_Board[i][j] == nullptr)
				continue;

			m_Board[i][j]->SetPosition(glm::vec3(A1Position.x + j*1.f, A1Position.y, A1Position.z - i*1.f));
			shader.Bind();
			if (m_Board[i][j]->m_Color == ChessPieceColor::White)
				shader.SetUniform4f("u_Color", 0.8f, 0.8f, 0.8f, 1.f);
			else
				shader.SetUniform4f("u_Color", 0.1f, 0.1f, 0.1f, 1.f);

			m_Board[i][j]->Draw(shader);
		}
	}
}

void ChessBoard::AddPiece(std::shared_ptr<ChessPiece> piece, int row, int column)
{
	if (row >= SIZE || row < 0)
		ASSERT("Invalid row in adding piece");
	if (column >= SIZE || column < 0)
		ASSERT("Invalid column in adding piece");

	m_Board[row][column] = piece;
}
