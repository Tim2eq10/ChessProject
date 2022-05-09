#include "Quiz.h"
#include "sfml_views.h"

QuizCheck::QuizCheck(int amount_of_moves_, int number_)
{
	amount_of_moves = amount_of_moves_;
	number = number_;
	path = path_check[amount_of_moves] + std::to_string(number) + txt;
	required_moves = new std::string[2 * (long long)amount_of_moves - 1];
	if (amount_of_moves == 1)
		amount_of_tasks = 20;
	else if (amount_of_moves == 2)
		amount_of_tasks = 30;
	else if (amount_of_moves == 3)
		amount_of_tasks = 5;
	properties.black_king_motionless = false;
	properties.white_king_motionless = false;
}

QuizCheck::QuizCheck(int amount_of_moves_, std::string name_)
{
	if (amount_of_moves_)
	{
		amount_of_moves = amount_of_moves_;
		required_moves = new std::string[2 * amount_of_moves - 1];
	}
	else
		amount_of_moves = 0;

	path = path_custom[amount_of_moves] + name_ + txt;
	
	properties.black_king_motionless = false;
	properties.white_king_motionless = false;
}

QuizCheck::~QuizCheck()
{
	delete[] required_moves;
	required_moves = 0;
}

void QuizCheck::Move(sf::Vector2i mouse_pos)
{
	if (view_properties.transforming_pawn == 0 && in_field(mouse_pos) && !IsEndgame())
	{
		int i_ = mouse_pos.y / 100;
		int j_ = mouse_pos.x / 100;

		if (field[i_][j_].figure_color == properties.color)
		{
			figure_chosen.setPosition(sf::Vector2f((float)(100 * j_), (float)(100 * i_)));
			view_properties.start_pos_h = i_;
			view_properties.start_pos_w = j_;
			view_properties.choosed_figure_to_move = 1;
			view_properties.allowed = allowed_positions(i_, j_);
		}

		if (field[i_][j_].figure_color != properties.color && view_properties.choosed_figure_to_move)
		{
			int h1 = view_properties.start_pos_h;
			int w1 = view_properties.start_pos_w;
			view_properties.final_pos_h = i_;
			view_properties.final_pow_w = j_;
			std::cout << h1 << w1 << i_ << j_ << '\n';
			
			std::string s = "";
			s += '0' + h1;
			s += '0' + w1;
			s += '0' + i_;
			s += '0' + j_;
			std::cout << s << '\n';
			std::cout << required_moves[current_move] << '\n';
			if (s == required_moves[current_move])
			{
				update_figure_pos(h1, w1, i_, j_);

				view_properties.transforming_pawn =
					(i_ == (properties.color == white ? 0 : 7) && field[i_][j_].figure == pawn);

				current_move++;
				if (current_move < 2 * amount_of_moves - 1)
				{
					update_figure_pos(
						required_moves[current_move][0] - '0',
						required_moves[current_move][1] - '0',
						required_moves[current_move][2] - '0',
						required_moves[current_move][3] - '0'
					);
					current_move++;
				}
				if (current_move == 2 * amount_of_moves - 1)
					properties.color = opposite_color(properties.color);

				view_properties.check_warning_not_hidden = 0;
			}
			else
				amount_of_mistakes++;

			view_properties.choosed_figure_to_move = 0;
			view_properties.allowed = std::vector<sf::Vector2i>();
		}
	}
}

void QuizCheck::Create()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			delete_figure(i, j);
	current_move = 0;

	std::string figures[32];
	int amount = 0;
	std::string x;
	char color;
	
	std::ifstream fin;
	try
	{
		fin.open(path);
	}
	catch (std::istream::failure ex)
	{
		std::cerr << "Quiz : Exception ifstream " << ex.what() << '\n';
		std::cerr << "Quiz : Failed to load quiz from " << path;
		return;
	}

	fin >> color;
	properties.color = color;

	for (int i = 0; i < 2 * amount_of_moves - 1; i++)
		fin >> required_moves[i];
		
	while (fin >> x)
		figures[amount++] = x;
		
	for (int i = 0; i < amount; i++)
		set_figure(figures[i][0] - '0', figures[i][1] - '0', figures[i][3], figures[i][2]);

	std::cout << "Loaded quiz from " << path << '\n';
}

void QuizCheck::__StartGame(bool task_can_be_changed)
{
	using namespace sf;

	RenderWindow window(sf::VideoMode(8 * (ui)cell_size.x + 400, 8 * (ui)cell_size.y), "Chess created by Timur && Vladimir");
	window.setIcon(768, 768, icon.getPixelsPtr());

	InfoButton info_button(description_text[amount_of_moves]);
	HintButton hint_button(required_moves[0]);
	ChangeQuizButton prev_button("prev"), next_button("next");
	Mistakes mistakes;

	Text text_number(L"Задача №" + std::to_string(number), main_font, 25);
	text_number.setFillColor(Color::Black);
	text_number.setPosition(Vector2f(950, 50));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				Vector2i mouse_pos = Mouse::getPosition(window);

				Move(mouse_pos);

				info_button.Pressed(mouse_pos);
				hint_button.Pressed(mouse_pos);
				
				if (task_can_be_changed && (prev_button.Pressed(mouse_pos) || next_button.Pressed(mouse_pos)))
				{
					if (prev_button.Pressed(mouse_pos))
						number = (number == 1 ? amount_of_tasks : number - 1);
					if (next_button.Pressed(mouse_pos))
						number = (number == amount_of_tasks ? 1 : number + 1);

					path = path_check[amount_of_moves] + std::to_string(number) + txt;
					Create();
					view_properties.allowed = std::vector<Vector2i>();
					view_properties.choosed_figure_to_move = false;
					view_properties.check_warning_not_hidden = false;
					hint_button.update(required_moves[current_move]);
					text_number.setString(L"Задача №" + std::to_string(number));
				}

				if (current_move != 2 * amount_of_moves - 1)
					hint_button.update(required_moves[current_move]);

				while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
			}
		}
		window.clear();

		mistakes.update(amount_of_mistakes);

		Draw(window);
		DrawMenu(window, amount_of_moves);
		DrawTaggedCells(window);
		DrawTransformPawnMenu(window);
		if (task_can_be_changed)
		{
			prev_button.Draw(window);
			next_button.Draw(window);
		}
		hint_button.Draw(window);
		mistakes.Draw(window);
		info_button.Draw(window);

		window.draw(text_number);

		window.display();
	}
}

void QuizCheck::StartGame(int amount_of_moves)
{
	QuizCheck Quiz(amount_of_moves, 1);
	Quiz.Create();
	Quiz.__StartGame();
}
