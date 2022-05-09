#pragma once
#include "Quiz.h"

class Custom : public QuizCheck
{
private:
	int gamemode = 0;
	Custom(int gamemode_, std::string name_);
public:
	static void Play(int gamemode_, std::string name_);
	static void Add(int gamemode_, std::string name_);
	static void Edit(int gamemode_, std::string name_, bool add = false);
};

