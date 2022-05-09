#include "Custom.h"
#include "sfml_views.h"

Custom::Custom(int gamemode_, std::string name_) : QuizCheck(gamemode_, name_)
{
	gamemode = gamemode_;
}

void Custom::Play(int gamemode_, std::string name_)
{
	Custom Desk(gamemode_, name_);
	Desk.Create();
	if (gamemode_ == 0)
		Desk.Board::__StartGame();
	else
		Desk.__StartGame(false);
}

void Custom::Add(int gamemode_, std::string name_)
{
	Edit(gamemode_, name_, true);
}

void Custom::Edit(int gamemode_, std::string name_, bool add)
{
	using namespace sf;
	using namespace std;

	Custom user(gamemode_, name_);
	if (!add)
		user.Create();

	//переменные дл€ установки фигур
	bool setting_figures = true;
	Vector2i figures_start_pos(850, 75);
	Button delete_button(path_ultimate + "del_fig.png",
		Vector2f(figures_start_pos.x + 230.0f, figures_start_pos.y + 8.0f),
		Vector2f(50, 50));
	GameMenuButton end_set_figures(path_ultimate + "dark_plank.jpg", L"«акончить выбор фигур", Vector2f(850, 425), Vector2f(325, 50));

	//переменные дл€ установки начального цвета
	bool setting_start_color = true;
	Text start_color_text(L"¬ыберите начальный цвет", main_font, 25);
	start_color_text.setFillColor(Color::Black);
	start_color_text.setStyle(Text::Bold);
	start_color_text.setPosition(Vector2f(850, 75));
	Button white_color(path_ultimate + "white_square.jpg", Vector2f(900, 125), Vector2f(100, 100));
	Button black_color(path_ultimate + "black_square.jpg", Vector2f(1025, 125), Vector2f(100, 100));

	//переменные дл€ установки желаемых ходов
	bool setting_moves = gamemode_ > 0; //если не свободна€ игра
	int entered_amount_of_moves = 0;
	Text enter_turn(L"—делайте желаемый ход", main_font, 25);
	enter_turn.setFillColor(Color::Black);
	enter_turn.setStyle(Text::Bold);
	enter_turn.setPosition(Vector2f(860, 75));
	int amount_of_moves = 2 * gamemode_ - 1;
	
	GameMenuButton save(path_ultimate + "dark_plank.jpg", L"—охранить расстановку", Vector2f(850, 425), Vector2f(325, 50));
	
	RenderWindow window(sf::VideoMode(8 * (ui)cell_size.x + 400, 8 * (ui)cell_size.y), "Chess created by Timur && Vladimir");

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

				int i_ = mouse_pos.y / 100;
				int j_ = mouse_pos.x / 100;

				if (setting_figures)
				{
					if (in_field(mouse_pos))
					{
						figure_chosen.setPosition(sf::Vector2f((float)(100 * j_), (float)(100 * i_)));
						user.view_properties.start_pos_h = i_;
						user.view_properties.start_pos_w = j_;
						user.view_properties.choosed_figure_to_move = 1;
					}
					if (user.view_properties.choosed_figure_to_move)
					{
						if (mouse_pos.x >= figures_start_pos.x && mouse_pos.y >= figures_start_pos.y &&
							mouse_pos.x <= figures_start_pos.x + 225 && mouse_pos.y <= figures_start_pos.y + 300)
						{
							i_ = (mouse_pos.y - figures_start_pos.y) / 75;
							j_ = (mouse_pos.x - figures_start_pos.x) / 75;
							char color = (i_ < 2 ? white : black);
							char figure = figures_char[3 * (i_ % 2) + j_ % 3];
							user.set_figure(user.view_properties.start_pos_h, user.view_properties.start_pos_w, figure, color);
							user.view_properties.choosed_figure_to_move = false;
						}
						if (delete_button.Pressed(mouse_pos))
							user.delete_figure(user.view_properties.start_pos_h, user.view_properties.start_pos_w);
					}
					if (end_set_figures.Pressed(mouse_pos))
					{
						setting_figures = false;
						user.view_properties.choosed_figure_to_move = false;
					}
				}
				else if (setting_start_color)
				{
					if (white_color.Pressed(mouse_pos))
					{
						setting_start_color = false;
						user.properties.color = white;
					}
					if (black_color.Pressed(mouse_pos))
					{
						setting_start_color = false;
						user.properties.color = black;
					}
				}
				else if (setting_moves)
				{
					if (in_field(mouse_pos) && user.field[i_][j_].figure_color == user.properties.color)
					{
						figure_chosen.setPosition(sf::Vector2f((float)(100 * j_), (float)(100 * i_)));
						user.view_properties.start_pos_h = i_;
						user.view_properties.start_pos_w = j_;
						user.view_properties.choosed_figure_to_move = 1;
						user.view_properties.allowed = user.allowed_positions(i_, j_);
					}
					else if (user.field[i_][j_].figure_color != user.properties.color && user.view_properties.choosed_figure_to_move)
					{
						cout << user.field[i_][j_].figure_color << '\n';
						cout << user.properties.color << '\n';
						int h1 = user.view_properties.start_pos_h;
						int w1 = user.view_properties.start_pos_w;
						user.view_properties.final_pos_h = i_;
						user.view_properties.final_pow_w = j_;
						std::cout << h1 << w1 << i_ << j_ << '\n';
						if (find(user.view_properties.allowed.begin(),
								 user.view_properties.allowed.end(),
								 Vector2i(i_,j_) 
							)!= user.view_properties.allowed.end())
						{
							string s = "";
							s += '0' + h1;
							s += '0' + w1;
							s += '0' + i_;
							s += '0' + j_;
							cout << user.amount_of_moves << '\n';
							user.required_moves[entered_amount_of_moves] = s;
							entered_amount_of_moves++;
							setting_moves = entered_amount_of_moves < amount_of_moves;
							if (setting_moves)
								user.properties.color = opposite_color(user.properties.color);
							user.update_figure_pos(h1, w1, i_, j_);
						}
						user.view_properties.choosed_figure_to_move = 0;
						user.view_properties.allowed = std::vector<sf::Vector2i>();
					}
				}
				else if (save.Pressed(mouse_pos))
				{
					while (--entered_amount_of_moves >= 0)
						user.update_figure_pos(user.required_moves[entered_amount_of_moves][2] - '0',
							user.required_moves[entered_amount_of_moves][3] - '0',
							user.required_moves[entered_amount_of_moves][0] - '0',
							user.required_moves[entered_amount_of_moves][1] - '0');

					try
					{
						ofstream fout(path_custom[gamemode_] + name_ + txt);
						fout << user.properties.color << endl;
						if (gamemode_ > 0)
						{
							cout << user.required_moves[0] << '\n';
							entered_amount_of_moves = -1;
							while (++entered_amount_of_moves < amount_of_moves)
								fout << user.required_moves[entered_amount_of_moves] << '\n';
							fout.close();
						}
						user.WriteToFile(path_custom[gamemode_] + name_ + txt);
					}
					catch (std::ofstream::failure ex)
					{
						std::cerr << "Exception opening/writing/closing file: " << ex.what() << '\n';
						std::cerr << "Failed to write " << path_custom[gamemode_] + name_ + txt << '\n';
						return;
					}
					window.close();
				}

				while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
			}
		}
		window.clear();

		user.Draw(window);
		user.Board::DrawTaggedCells(window);

		window.draw(back_menu);
		window.draw(menu_sep);
		window.draw(title_bar_text[gamemode_]);
		window.draw(logo);

		if (setting_figures)
		{
			if (user.view_properties.choosed_figure_to_move)
			{
				for (int i = 0; i < 6; i++)
				{
					sf::Sprite a = figure[white][figures_char[i]];
					a.scale(0.75, 0.75);
					a.setPosition(figures_start_pos.x + (i % 3) * 75.0f, figures_start_pos.y + (i / 3) * 75.0f);
					window.draw(a);
					a = figure[black][figures_char[i]];
					a.scale(0.75, 0.75);
					a.setPosition(figures_start_pos.x + (i % 3) * 75.0f, figures_start_pos.y + (i / 3 + 2) * 75.0f);
					window.draw(a);
				}
				delete_button.Draw(window);
			}
			end_set_figures.Draw(window);
		}
		else if (setting_start_color)
		{
			window.draw(start_color_text);
			white_color.Draw(window);
			black_color.Draw(window);
		}
		else if (setting_moves)
		{
			window.draw(enter_turn);
		}
		else
		{
			save.Draw(window);
		}

		window.display();
	}
}
