#include "Classes/Public/Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

#include "Classes/Public/Model.h"
#include "Classes/Public/Shader.h"
#include "Classes/Public/Camera.h"
#include "Classes/Public/Mesh.h"
#include "Classes/Public/ChessPiece.h"
#include "Classes/Public/ChessBoard.h"
#include "Classes/Public/MovingCar.h"

static enum FillingType
{
	Flat = 0,
	Gourond = 1,
	Phong = 2
};

static std::shared_ptr<ChessBoard> StartNewGame()
{
	std::shared_ptr<Texture> texture ( new Texture("res/textures/wood.jpg"));
	std::shared_ptr<Texture> chessboardtexture (new Texture("res/textures/board/chessboard.png"));

	std::shared_ptr<Mesh> pawnmesh(new Mesh("res/textures/pawn/pawn.obj"));
	std::shared_ptr<Mesh> bishopmesh (new Mesh("res/textures/bishop/bishop.obj"));
	std::shared_ptr<Mesh> knightmesh (new Mesh("res/textures/knight/knight.obj"));
	std::shared_ptr<Mesh> rookmesh (new Mesh("res/textures/rook/rook.obj"));
	std::shared_ptr<Mesh> queenmesh (new Mesh("res/textures/queen/queen.obj"));
	std::shared_ptr<Mesh> kingmesh (new Mesh("res/textures/king/king.obj"));
	std::shared_ptr<Mesh> boardmesh (new Mesh("res/textures/board/board.obj"));

	std::shared_ptr<ChessPiece> Pawn (new ChessPiece(pawnmesh, texture, ChessPieceType::Pawn, ChessPieceColor::White));
	std::shared_ptr<ChessPiece> Bishop (new ChessPiece(bishopmesh, texture, ChessPieceType::Bishop, ChessPieceColor::White));
	std::shared_ptr<ChessPiece> Knight (new ChessPiece(knightmesh, texture, ChessPieceType::Knight, ChessPieceColor::White));
	std::shared_ptr<ChessPiece> Rook (new ChessPiece(rookmesh, texture, ChessPieceType::Rook, ChessPieceColor::White));
	std::shared_ptr<ChessPiece> Queen (new ChessPiece(queenmesh, texture, ChessPieceType::Queen, ChessPieceColor::White));
	std::shared_ptr<ChessPiece> King (new ChessPiece(kingmesh, texture, ChessPieceType::King, ChessPieceColor::White));

	std::shared_ptr<ChessPiece> PawnBlack (new ChessPiece(pawnmesh, texture, ChessPieceType::Pawn, ChessPieceColor::Black));
	std::shared_ptr<ChessPiece> BishopBlack (new ChessPiece(bishopmesh, texture, ChessPieceType::Bishop, ChessPieceColor::Black));
	std::shared_ptr<ChessPiece> KnightBlack (new ChessPiece(knightmesh, texture, ChessPieceType::Knight, ChessPieceColor::Black));
	std::shared_ptr<ChessPiece> RookBlack (new ChessPiece(rookmesh, texture, ChessPieceType::Rook, ChessPieceColor::Black));
	std::shared_ptr<ChessPiece> QueenBlack (new ChessPiece(queenmesh, texture, ChessPieceType::Queen, ChessPieceColor::Black));
	std::shared_ptr<ChessPiece> KingBlack (new ChessPiece(kingmesh, texture, ChessPieceType::King, ChessPieceColor::Black));

	std::shared_ptr<ChessBoard> Board (new ChessBoard(boardmesh, chessboardtexture, glm::vec3(0, -2.f, 0.f)));

	Pawn->SetScale(glm::vec3(0.15f, 0.15f, 0.15f));
	Bishop->SetScale(glm::vec3(0.15f, 0.15f, 0.15f));
	Knight->SetScale(glm::vec3(0.15f, 0.15f, 0.15f));
	Rook->SetScale(glm::vec3(0.15f, 0.15f, 0.15f));
	Queen->SetScale(glm::vec3(0.15f, 0.15f, 0.15f));
	King->SetScale(glm::vec3(0.15f, 0.15f, 0.15f));

	PawnBlack->SetScale(glm::vec3(0.15f, 0.15f, 0.15f));
	BishopBlack->SetScale(glm::vec3(0.15f, 0.15f, 0.15f));
	KnightBlack->SetScale(glm::vec3(0.15f, 0.15f, 0.15f));
	RookBlack->SetScale(glm::vec3(0.15f, 0.15f, 0.15f));
	QueenBlack->SetScale(glm::vec3(0.15f, 0.15f, 0.15f));
	KingBlack->SetScale(glm::vec3(0.15f, 0.15f, 0.15f));
	
	Board->RotateY(glm::radians(-90.f));

	//white pieces
	Board->AddPiece(Rook, 0, 0);
	Board->AddPiece(Knight, 0, 1);
	Board->AddPiece(Bishop, 0, 2);
	Board->AddPiece(Queen, 0, 3);
	Board->AddPiece(King, 0, 4);
	Board->AddPiece(Bishop, 0, 5);
	Board->AddPiece(Knight, 0, 6);
	Board->AddPiece(Rook, 0, 7);
	for (int j = 0; j < 8; j++)
		Board->AddPiece(Pawn, 1, j);

	//black pieces
	Board->AddPiece(RookBlack, 7, 0);
	Board->AddPiece(KnightBlack, 7, 1);
	Board->AddPiece(BishopBlack, 7, 2);
	Board->AddPiece(QueenBlack, 7, 3);
	Board->AddPiece(KingBlack, 7, 4);
	Board->AddPiece(BishopBlack, 7, 5);
	Board->AddPiece(KnightBlack, 7, 6);
	Board->AddPiece(RookBlack, 7, 7);
	for (int j = 0; j < 8; j++)
		Board->AddPiece(PawnBlack, 6, j);

	return Board;
}

static void SwitchCamerasInput(std::vector<std::shared_ptr<Camera>>& cameras, GLFWwindow* window)
{
	// first camera
	if (glfwGetKey(window, GLFW_KEY_1))
	{
		Camera::SetWorkingCamera(cameras[0]);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_2))
	{
		Camera::SetWorkingCamera(cameras[1]);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_3))
	{
		Camera::SetWorkingCamera(cameras[2]);
		return;
	}
}

static void OtherInput(FillingType& type, bool& fog, GLFWwindow* window)
{
	// first camera
	if (glfwGetKey(window, GLFW_KEY_M))
	{
		fog = !fog;
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_F))
	{
		type = FillingType::Flat;
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_G))
	{
		type = FillingType::Gourond;
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_P))
	{
		type = FillingType::Phong;
		return;
	}
}

int main()
{
	#pragma region GLFW init
	// Initialize GLFW
	GLFWwindow* window;

	if(!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(Camera::Width, Camera::Height, "Chess 3D", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		return -2;

	std::cout << glGetString(GL_VERSION) << "\n";

	glEnable(GL_DEPTH_TEST);

	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA));
	glEnable(GL_BLEND);

#pragma endregion

	std::shared_ptr<ChessBoard> Board = StartNewGame();

	std::vector<std::shared_ptr<Shader>> Shaders;
	std::shared_ptr<Shader> FlatShader(new Shader("res/shaders/ModelFlat.shader"));
	std::shared_ptr<Shader> GourandShader(new Shader("res/shaders/ModelGourand.shader"));
	std::shared_ptr<Shader> PhongShader(new Shader("res/shaders/Model.shader"));

	Shaders.push_back(FlatShader);
	Shaders.push_back(GourandShader);
	Shaders.push_back(PhongShader);

	Renderer renderer;
	
	std::vector<std::shared_ptr<Camera>> Cameras;
	std::shared_ptr<Camera> Freecamera (new Camera(glm::vec3(2.f, 12.f, 25.f)));
	Freecamera->SetOrientation(-Freecamera->GetPosition());

	Camera::SetScrollInput(window);
	Camera::SetWorkingCamera(Freecamera);

	std::shared_ptr<Shader> lightShader (new Shader("res/shaders/Light.shader"));
	std::shared_ptr<Mesh> LightMesh (new Mesh("res/textures/light/lightbulb.obj"));
	std::shared_ptr<Model> LightBulb (new Model(LightMesh, nullptr, glm::vec3(-2.f, 2.f, 0.f)));
	std::shared_ptr<Model> LightBulb2 (new Model(LightMesh, nullptr, glm::vec3(2.f, 2.f, 0.f)));
	LightBulb->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	LightBulb2->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));

	std::shared_ptr<Mesh> CarMesh (new Mesh("res/textures/car/car.obj"));
	std::shared_ptr<Texture> texture (new Texture("res/textures/car/rust.jpg"));
	std::shared_ptr<Car> MovingCar ( new Car(CarMesh, texture, glm::vec3(10.f, 1.f, 0.f), glm::vec2(0.f, 0.f), 10.f, LightMesh));
	MovingCar->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	MovingCar->RotateZ(glm::radians(-30.f));

	Cameras.push_back(Freecamera);
	Cameras.push_back(MovingCar->GetAThirdCamera());
	Cameras.push_back(MovingCar->GetStaringCamera());

	typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::duration<float, std::milli> duration;

	static clock::time_point start = clock::now();
	duration elapsed = clock::now() - start;

	bool Fog = false;
	FillingType Type = FillingType::Phong;

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		SwitchCamerasInput(Cameras, window);
		OtherInput(Type, Fog, window);

		Shaders[(int)Type]->Bind();

		Camera::GetWorkingCamera()->Inputs(window);
		Camera::GetWorkingCamera()->Matrix(45.0f, 0.1f, 100.0f, *Shaders[(int)Type].get(), "u_camMatrix");

		Shaders[(int)Type]->SetUniform1i("u_FogEnabled", Fog);

		Shaders[(int)Type]->SetUniform4f("pointLights[0].m_LightColor", 1.f, 1.f, 1.f, 1.f);
		Shaders[(int)Type]->SetUniform3f("pointLights[0].m_LightPos", LightBulb->GetPosition());
		Shaders[(int)Type]->SetUniform1i("pointLights[0].m_PointLight", true);

		Shaders[(int)Type]->SetUniform4f("pointLights[1].m_LightColor", 1.f, 1.f, 1.f, 1.f);
		Shaders[(int)Type]->SetUniform3f("pointLights[1].m_LightPos", LightBulb2->GetPosition());
		Shaders[(int)Type]->SetUniform1i("pointLights[1].m_PointLight", true);

		Shaders[(int)Type]->SetUniform4f("pointLights[2].m_LightColor", 1.f, 1.f, 1.f, 1.f);
		Shaders[(int)Type]->SetUniform3f("pointLights[2].m_LightPos", MovingCar->GetLightBulb()->GetPosition());
		Shaders[(int)Type]->SetUniform1i("pointLights[2].m_PointLight", false);

		Shaders[(int)Type]->SetUniform3f("u_ViewPos", Camera::GetWorkingCamera()->GetPosition());
		Board->Draw(*Shaders[(int)Type]);
		duration elapsed = clock::now() - start;

		MovingCar->Tick(elapsed.count() / 100.f);
		MovingCar->Draw(*Shaders[(int)Type]);

		lightShader->Bind();
		Camera::GetWorkingCamera()->Matrix(45.0f, 0.1f, 100.0f, *lightShader, "u_camMatrix");
		lightShader->SetUniform4f("u_Color", 1.f, 1.f, 1.f, 1.f);
		LightBulb->Draw(*lightShader);

		lightShader->Bind();
		Camera::GetWorkingCamera()->Matrix(45.0f, 0.1f, 100.0f, *lightShader, "u_camMatrix");
		lightShader->SetUniform4f("u_Color", 1.f, 1.f, 1.f, 1.f);
		LightBulb2->Draw(*lightShader);

		lightShader->Bind();
		Camera::GetWorkingCamera()->Matrix(45.0f, 0.1f, 100.0f, *lightShader, "u_camMatrix");
		lightShader->SetUniform4f("u_Color", 1.f, 1.f, 1.f, 1.f);
		MovingCar->GetLightBulb()->Draw(*lightShader);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		
		// Take care of all GLFW events
		glfwPollEvents();

		start = clock::now();
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);

	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
