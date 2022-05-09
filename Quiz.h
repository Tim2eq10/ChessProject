#pragma once
#include "Board.h"

const std::string path_check[4] = {
	"",
	"check_one_move\\",
	"check_two_moves\\",
	"check_three_moves\\"
};
const std::string path_custom[4] = {
	"custom\\game\\",
	"custom\\check_one_move\\",
	"custom\\check_two_moves\\",
	"custom\\check_three_moves\\"
};
const std::string list = "list";
const std::string txt = ".txt";

class QuizCheck : public Board
{
private:
	int amount_of_mistakes = 0; 
	int amount_of_tasks = 0; 
	int number = -1; // номер задачи
	QuizCheck(int amount_of_moves, int number = -1);
	void Move(sf::Vector2i mouse_pos) override;
protected:
	std::string path = ""; //путь к файлу, из которого загружается задача
	int current_move = 0;  
	int amount_of_moves = 0; 
	std::string* required_moves = 0; 

	QuizCheck(int amount_of_moves, std::string name_);
	~QuizCheck();
	void Create() override;
	void __StartGame(bool task_can_be_changed = true);
public:
	static void StartGame(int amount_of_moves);
};
