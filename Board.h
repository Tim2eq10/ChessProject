#pragma once
#include <cstdlib>
#include <iostream> 
#include <string>
#include <fstream> 
#include <vector>
#include <map>

#include <SFML\Graphics.hpp>

const char black = 'B';
const char white = 'W';

const char empty_ = '0';
const char pawn = 'P';
const char horse = 'H';
const char king = 'K';
const char queen = 'Q';
const char elephant = 'E';
const char rook = 'R';

#define COORDS_ARGS int h1,int w1,int h2,int w2
#define COORDS_PARAMS h1, w1, h2, w2

typedef unsigned int ui;

class Board
{
private:

	class Cell 
	{
	public:
		bool occ = false; // (����. �� occupancy - ���������) (0-�� ������, 1-������)
		char figure_color = empty_; // white ��� black ��� empty_ (��.const)
		char figure = empty_; // ������ ��� empty_ (��. const)
	};
	class Properties
	{
	public:
		char color = white; //���� �����, ��� ��� ������

		bool left_white_rook_motionless = true; // ����������, ����������� ��� ������������� ���������
		bool right_white_rook_motionless = true;
		bool left_black_rook_motionless = true;
		bool right_black_rook_motionless = true;
		bool white_king_motionless = true;
		bool black_king_motionless = true;

		int en_passent_h = -1;
		int en_passent_w = -1;
	};
	class View_properties
	{
	public:
		std::vector<sf::Vector2i> allowed;
		int start_pos_h = 0, start_pos_w = 0;
		int final_pos_h = 0, final_pow_w = 0;
		int h_king = 0, w_king = 0;

		bool choosed_figure_to_move = false;
		bool check_warning_not_hidden = false;
		bool transforming_pawn = false;
	};
	
	bool CanMove(COORDS_ARGS); // ����� �� ��������� �������� ��� (��������� ����) 
	bool CanMoveFigure(COORDS_ARGS, char color); // ����� �� ������ ��������� �������� ��� 
												 // ��������� ����� ������� � ��������� ������� �������� � ����������� �� ������
												 // (�� ��������� ����)
	bool CanMovePawn(COORDS_ARGS, char color); 
	bool CanMoveHorse(COORDS_ARGS);
	bool CanMoveElephant(COORDS_ARGS);
	bool CanMoveRook(COORDS_ARGS);
	bool CanMoveQueen(COORDS_ARGS);
	bool CanMoveKing(COORDS_ARGS, char color);

	bool IsCheck(); //���� �� ��� �� ������ ����� properties.color � ������ ��������� �����
	bool IsCheckAfterMove(COORDS_ARGS); // ����� �� IsCheck() ����� ��������� ����
	bool IsCheckmate(); // ���� �� ��� � ������ ��������� �����
	bool IsStalemate(); // ���� �� ��� � ������ ��������� �����

	void Castling(COORDS_ARGS); // ������������ ����������� ����� ��� ���������, ���� ��� ���������
	void TransformPawn(sf::Vector2i mouse_pos); // ������������ ������������� �����, ���� ��� ���������
	void EnPassent(COORDS_ARGS); // ������ �� �������

protected:

	Cell field[8][8]; 
	Properties properties;
	View_properties view_properties;

	Board(); //����������� ����� ������ ����������, �� ����� ��� ������� 
			 //�������� ������� Board ��� ������
	static char opposite_color(char color);
	void set_figure(int h, int w, char figure, char figure_color);
	void delete_figure(int h, int w);
	void update_figure_pos(COORDS_ARGS);
	void WriteToFile(std::string path);
	std::vector<sf::Vector2i> allowed_positions(int h1, int h2);

	virtual void Create(); //�������� ����������� ��������� �����������
	virtual void Move(sf::Vector2i mouse_pos); // ��������� �������� ����������� 
						//����������� ������ � ������������ �����������

	bool IsEndgame(); //��������� ������� ����/����

	void Draw(sf::RenderWindow& window);
	void DrawTaggedCells(sf::RenderWindow& window); 
	void DrawMenu(sf::RenderWindow& window, int description_mode);
	void DrawTransformPawnMenu(sf::RenderWindow& window);

	void __StartGame();

public:

	static void StartGame();

};


