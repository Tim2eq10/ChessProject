#include "Board.h"
#include "sfml_views.h"

// ================================================================ //
//						BOARD ASSIST METHODS						//
// ================================================================ //
char Board::opposite_color(char color)
{
	return (color == white ? black : white);
}
void Board::set_figure(int h, int w, char figure, char figure_color)
{
	field[h][w].occ = true;
	field[h][w].figure = figure;
	field[h][w].figure_color = figure_color;
}
void Board::delete_figure(int h, int w)
{
	field[h][w].occ = false;
	field[h][w].figure = empty_;
	field[h][w].figure_color = empty_;
}
void Board::update_figure_pos(COORDS_ARGS)
{
	set_figure(h2, w2, field[h1][w1].figure, field[h1][w1].figure_color);
	delete_figure(h1, w1);
}
void Board::WriteToFile(std::string path)
{
	using namespace std;
	try
	{
		fstream fout(path, ios::app);
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (field[i][j].occ) {
					cout << i << j << field[i][j].figure_color << field[i][j].figure << endl;
					fout << i << j << field[i][j].figure_color << field[i][j].figure << endl;
				}

		fout.close();
	}
	catch (std::ofstream::failure ex)
	{
		std::cerr << "Exception opening/writing/closing file " << ex.what() << '\n';
		std::cerr << "Failed to write " << path << '\n';
		return;
	}
}
std::vector<sf::Vector2i> Board::allowed_positions(int h1, int w1)
{
	std::vector<sf::Vector2i> v;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (CanMoveFigure(h1, w1, i, j, properties.color))
				if (!IsCheckAfterMove(h1, w1, i, j))
					v.push_back(sf::Vector2i(i, j));
	return v;
}
// ================================================================ //
//							"BOARD" METODS							//
// ================================================================ //
Board::Board() {};
void Board::Create()
{
	set_figure(0, 0, rook, black);
	set_figure(0, 1, horse, black);
	set_figure(0, 2, elephant, black);
	set_figure(0, 3, queen, black);
	set_figure(0, 4, king, black);
	set_figure(0, 5, elephant, black);
	set_figure(0, 6, horse, black);
	set_figure(0, 7, rook, black);
	for (int i = 0; i < 8; i++) set_figure(1, i, pawn, black);

	set_figure(7, 0, rook, white);
	set_figure(7, 1, horse, white);
	set_figure(7, 2, elephant, white);
	set_figure(7, 3, queen, white);
	set_figure(7, 4, king, white);
	set_figure(7, 5, elephant, white);
	set_figure(7, 6, horse, white);
	set_figure(7, 7, rook, white);
	for (int i = 0; i < 8; i++) set_figure(6, i, pawn, white);
};
void Board::Draw(sf::RenderWindow& window)
{
	using namespace sf;
	Text index(L"", main_font, 25);
	index.setFillColor(Color(150, 100, 180));
	index.setStyle(Text::Bold);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (i % 2 + j % 2 - 1 == 0)
			{
				cell_color[black].setPosition((float)j * 100, (float)i * 100);
				window.draw(cell_color[black]);
			}
			else
			{
				cell_color[white].setPosition((float)j * 100, (float)i * 100);
				window.draw(cell_color[white]);
			}

			
			if (field[i][j].occ)
			{
				figure[field[i][j].figure_color][field[i][j].figure].setPosition((float)j * 100, (float)i * 100);
				window.draw(figure[field[i][j].figure_color][field[i][j].figure]);
			}
			if (j == 0)
			{
				index.setPosition(Vector2f(100.0f * j, 100.0f * i + 70));
				index.setString(std::to_string(8 - i));
				window.draw(index);
			}
			if (i == 7)
			{
				index.setPosition(Vector2f(100.0f * j + 80, 100.0f * (i + 1) - 30));
				index.setString((char)('A' + j));
				window.draw(index);
			}
		}
}
// ================================================================ //
//						MOVE:FIGURES METODS							//
// ================================================================ //
bool Board::CanMove(COORDS_ARGS)
{
	if (!CanMoveFigure(COORDS_PARAMS, properties.color))
	{
		std::cout << "‘игура не может так сходить!\n";
		return false;
	}
	else if (IsCheckAfterMove(COORDS_PARAMS))
	{
		std::cout << "Ќельз€ ходить, на вас Ўј’!!!\n";
		return false;
	}
	else
		return true;
}
bool Board::CanMoveFigure(COORDS_ARGS, char color)
{
	if (h1 < 0 || h1 > 7 || w1 < 0 || w1 > 7 || h2 < 0 || h2 > 7 || w2 < 0 || w2 > 7) 
		return false; // все позиции внутри пол€
	if (!field[h1][w1].occ || field[h1][w1].figure_color != color) 
		return false; // есть фигура на начальной позиции, притом своего цвета
	if (field[h2][w2].occ && field[h2][w2].figure_color == color) 
		return false; // на конечной позиции нет фигуры своего цвета

	switch (field[h1][w1].figure)
	{
	case pawn:
		return CanMovePawn(COORDS_PARAMS, color);
	case horse:
		return CanMoveHorse(COORDS_PARAMS);
	case elephant:
		return CanMoveElephant(COORDS_PARAMS);
	case rook:
		return CanMoveRook(COORDS_PARAMS);
	case queen:
		return CanMoveQueen(COORDS_PARAMS);
	case king:
		return CanMoveKing(COORDS_PARAMS, color);
	default:
		std::cout << "ѕроизошла очень больша€ проблема\n";
		return false;
	}
}
bool Board::CanMovePawn(COORDS_ARGS,char color)
{
	int color_mult = (color == white ? 1 : -1);
	int move_distance = abs(h2 - h1) + abs(w2 - w1);

	if (color_mult * h2 >= color_mult * h1)
		return false;// нельз€ пешками ходить назад/вбок
	if (move_distance == 1 && !field[h2][w2].occ)
		return true; // разрешЄн ход на клетку вперЄд
	if (move_distance == 2 && abs(w2 - w1) == 1 && field[h2][w2].figure_color == opposite_color(color))
		return true; // кушать по диагонали можно
	if (move_distance == 2 && abs(w2 - w1) == 0 && h1 == (7 - color_mult) % 7 && !field[h2 - color_mult][w2].occ && !field[h2][w2].occ)
		return true; // вперЄд на 2 клетки с начальной позиции
	if (move_distance == 2 && abs(w2 - w1) == 1 && h2 == properties.en_passent_h && w2 == properties.en_passent_w)
		return true; //вз€тие на проходе
	
	return false;
}
bool Board::CanMoveHorse(COORDS_ARGS)
{
	return (abs(w1 - w2) + abs(h1 - h2) == 3 && abs(w1 - w2) % 3 != 0);
}
bool Board::CanMoveElephant(COORDS_ARGS)
{
	if (abs(w1 - w2) != abs(h1 - h2)) return false; // ход по диагонали
	int move_w_orient = (w2 - w1) / abs(w1 - w2);
	int move_h_orient = (h2 - h1) / abs(h1 - h2);
	while (w1 != w2 - move_w_orient) // провер€ем клетки до последней 
	{
		h1 += move_h_orient; // сразу делаем сдвиг так как не нужно провер€ть 
		w1 += move_w_orient; // начальную позицию
		if (field[h1][w1].occ) return false;
	}
	return true;
}
bool Board::CanMoveRook(COORDS_ARGS)
{
	int move_w = abs(w1 - w2);
	int move_h = abs(h1 - h2);

	if (abs(w1 - w2) != 0 && abs(h1 - h2) != 0)
		return false;

	int move_w_orient;
	int move_h_orient;
	if (move_w == 0)
	{
		move_h_orient = (h2 - h1) / move_h;
		move_w_orient = 0;
	}
	else
	{
		move_w_orient = (w2 - w1) / move_w;
		move_h_orient = 0;
	}
	
	while (w1 != w2 - move_w_orient || h1 != h2 - move_h_orient)
	{
		h1 += move_h_orient;
		w1 += move_w_orient;
		if (field[h1][w1].occ)
			return false;
	}
	return true;
}
bool Board::CanMoveQueen(COORDS_ARGS)
{
	return (CanMoveElephant(h1,w1,h2,w2) || CanMoveRook(h1,w1,h2,w2));
}
bool Board::CanMoveKing(COORDS_ARGS, char color)
{ 
	//рокировка
	bool all_pos_not_occ_left = !(field[h2][1].occ || field[h2][2].occ || field[h2][3].occ);
	bool all_pos_not_occ_right = !(field[h2][6].occ || field[h2][5].occ);
	// рокировка белого корол€ 
	if (field[h1][w1].figure_color == white && h2 == 7 && properties.white_king_motionless) 
		// длинна€
		if ((w2 == 2 && properties.left_white_rook_motionless && all_pos_not_occ_left ||   
		// коротка€ 
		(w2 == 6 && properties.right_white_rook_motionless && all_pos_not_occ_right))) 
			return true;
	// рокировка чЄрного корол€ 
	if (field[h1][w1].figure_color == black && h2 == 0 && properties.black_king_motionless) 
		// длинна€
		if ((w2 == 2 && properties.left_black_rook_motionless && all_pos_not_occ_left) || 
		// коротка€ 
		(w2 == 6 && properties.right_black_rook_motionless && all_pos_not_occ_right)) 
			return true;

	return (abs(w1 - w2) + abs(h1 - h2) <= 2 && abs(w1 - w2) != 2 && abs(h1 - h2) != 2); 
}
void Board::Castling(COORDS_ARGS)
{
	// ладь€/король сдвинулись, надо бы это запомнить
	if ((h1 == 0 && w1 == 0) || (h2 == 0 && w2 == 0)) properties.left_black_rook_motionless = false;
	if ((h1 == 0 && w1 == 7) || (h2 == 0 && w2 == 7)) properties.right_black_rook_motionless = false;
	if ((h1 == 7 && w1 == 0) || (h2 == 7 && w2 == 0)) properties.left_white_rook_motionless = false;
	if ((h1 == 7 && w1 == 7) || (h2 == 7 && w2 == 7)) properties.right_white_rook_motionless = false;
	if (h1 == 0 && w1 == 4) properties.black_king_motionless = false;
	if (h1 == 7 && w1 == 4) properties.white_king_motionless = false;

	if (field[h1][w1].figure == king && ((h1 == 0 && h2 == 0) || (h1 == 7 && h2==7)))
		//если рокироку надо делать, то двигаем ладью (король уже сдвинулс€)
	{
		int orient = (w2 - w1) / abs(w2 - w1);
		update_figure_pos(h1, (orient == 1 ? 7 : 0), h2, w2 - orient);
	}
}
// ================================================================ //
//					CHECK AND CHECKMATE METODS						//
// ================================================================ //
bool Board::IsCheck() // есть ли Ўах на корол€ такого то цвета в данном положении пол€
{
	int h_const = -1, w_const = -1;
	//ищем нашего корол€
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (field[i][j].figure == king && field[i][j].figure_color == properties.color)
			{
				h_const = i;
				w_const = j;
			}

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (field[i][j].figure_color == opposite_color(properties.color))
				if (CanMoveFigure(i, j, h_const, w_const, opposite_color(properties.color)))
					return true;
	return false;
}
bool Board::IsCheckAfterMove(COORDS_ARGS)
{
	char figure_fin = field[h2][w2].figure;
	char figure_color_fin = field[h2][w2].figure_color;
	update_figure_pos(h1, w1, h2, w2);
	bool f = IsCheck();
	update_figure_pos(h2, w2, h1, w1);
	set_figure(h2, w2, figure_fin, figure_color_fin);
	if (figure_fin == empty_) field[h2][w2].occ = false;
	return f;
}
bool Board::IsCheckmate()
{
	if (!IsCheck()) return false; //если нет шаха, то мата €вно тоже нет
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) //перебираем все клетки доски
			if (field[i][j].figure_color == properties.color) // дл€ каждой нашей фигуры проверим
				for (int w = 0; w < 8; w++) 
					for (int h = 0; h < 8; h++)
						if (CanMoveFigure(i, j, h, w, properties.color)) //может ли она сделать такой ход
							if (!IsCheckAfterMove(i, j, h, w)) // что шаха не будет
								return false;
	return true;
}
bool Board::IsStalemate()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (field[i][j].figure_color == properties.color)
				for (int w = 0; w < 8; w++)
					for (int h = 0; h < 8; h++)
						if (CanMoveFigure(i, j, h, w, properties.color))
							if (!IsCheckAfterMove(i, j, h, w))
								return false;
	return true;
}
bool Board::IsEndgame()
{
	if (IsCheckmate())
	{
		std::cout << opposite_color(properties.color) << " wins\n";
		return true;
	}
	if (IsStalemate())
	{
		std::cout << "Draw'chka\n";
		return true;
	}
	return false;
}
// ================================================================ //
//							VIEWS METHODS							//
// ================================================================ //
void Board::Move(sf::Vector2i mouse_pos)
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

			if (CanMove(h1, w1, i_, j_))
			{
				Castling(h1, w1, i_, j_);

				update_figure_pos(h1, w1, i_, j_);

				EnPassent(h1, w1, i_, j_);

				view_properties.transforming_pawn = 
					(i_ == (properties.color == white ? 0 : 7) && field[i_][j_].figure == pawn);

				if (!view_properties.transforming_pawn)
					properties.color = opposite_color(properties.color);

				view_properties.check_warning_not_hidden = 0;
			}
			view_properties.choosed_figure_to_move = 0;
			view_properties.allowed = std::vector<sf::Vector2i>();
		}
	}
}
void Board::TransformPawn(sf::Vector2i mouse_pos)
{
	if (!view_properties.transforming_pawn)
		return;

	if (mouse_pos.x < trans_start_pos.x || mouse_pos.x > trans_start_pos.x + trans_menu_size.x
		|| mouse_pos.y < trans_start_pos.y || mouse_pos.y > trans_start_pos.y + trans_menu_size.y)
		return;

	int i_ = (mouse_pos.x - (int)trans_start_pos.x) / 75;
	set_figure(view_properties.final_pos_h, view_properties.final_pow_w,
		figures_char[i_ + 1], properties.color);
	view_properties.transforming_pawn = 0;
	properties.color = opposite_color(properties.color);
}
void Board::EnPassent(COORDS_ARGS)
{
	if (field[h2][w2].figure != pawn)
		return;

	if (h2 == properties.en_passent_h && w2 == properties.en_passent_w)
		delete_figure(h2 + (properties.color == white ? 1 : -1), w2);

	properties.en_passent_h = -1;
	properties.en_passent_w = -1;
	if (abs(h1 - h2) == 2)
	{
		properties.en_passent_h = h2 + (properties.color == white ? 1 : -1);
		properties.en_passent_w = w2;
	}
}

void Board::DrawTaggedCells(sf::RenderWindow& window)
{
	//показывать или не показывать шах на короле
	if (!view_properties.check_warning_not_hidden && IsCheck())
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (field[i][j].figure == king && field[i][j].figure_color == properties.color)
				{
					view_properties.h_king = i;
					view_properties.w_king = j;
					view_properties.check_warning_not_hidden = 1;
				}


	if (view_properties.choosed_figure_to_move == 1)
		window.draw(figure_chosen);
	for (sf::Vector2i v : view_properties.allowed) {
		allowed_s.setPosition(sf::Vector2f((float)(100 * v.y), (float)(100 * v.x)));
		window.draw(allowed_s);
	}
	if (view_properties.check_warning_not_hidden) {
		check_warning.setPosition(sf::Vector2f((float)(100 * view_properties.w_king), (float)(100 * view_properties.h_king)));
		window.draw(check_warning);
	}
}
void Board::DrawMenu(sf::RenderWindow& window, int description_mode)
{
	window.draw(back_menu);
	window.draw(menu_sep);
	window.draw(title_bar_text[description_mode]);

	//кто сейчас ходит или кто уже победил
	sf::Text move_color(L"", main_font, 40);
	move_color.setStyle(sf::Text::Bold);
	move_color.setFillColor(sf::Color::Black);
	if (IsCheckmate())
		move_color.setString(properties.color == white ? L"ѕобеда чЄрных" : L"ѕобеда белых");
	else if (IsStalemate())
	{
		move_color.setString(L"Ќичь€");
		move_color.setFillColor(sf::Color::Magenta);
	}
	else
		move_color.setString(properties.color == white ? L"’од белых" : L"’од чЄрных");

	sf::FloatRect size = move_color.getLocalBounds();
	move_color.setOrigin(size.left + size.width * 0.5f, size.top + size.height * 0.5f);
	move_color.setPosition((1200.0 + 830.0) / 2, 480);
	window.draw(move_color);
	//------------------------
	window.draw(logo);
}
void Board::DrawTransformPawnMenu(sf::RenderWindow& window)
{
	if (view_properties.transforming_pawn)
	{
		window.draw(trans_menu_back);
		window.draw(trans_text);
		for (int i = 1; i <= 4; i++)
		{
			sf::Sprite a = figure[properties.color][figures_char[i]];
			a.scale(0.75, 0.75);
			a.setPosition(trans_start_pos.x + (i - 1) * 75, trans_start_pos.y);
			window.draw(a);
		}
	}
}



void Board::__StartGame()
{
	using namespace sf;

	sf::RenderWindow window(sf::VideoMode(8 * (ui)cell_size.x + 400, 8 * (ui)cell_size.y), "Chess created by Timur && Vladimir");
	window.setIcon(768, 768, icon.getPixelsPtr());

	InfoButton info_button(description_text[0]);

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

				Board::Move(mouse_pos);

				TransformPawn(mouse_pos);

				info_button.Pressed(mouse_pos);

				while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
			}
		}
		window.clear();

		Draw(window);
		DrawMenu(window, 0);
		DrawTaggedCells(window);
		DrawTransformPawnMenu(window);
		info_button.Draw(window);

		window.display();
	}
}
void Board::StartGame()
{
	Board Desk;
	Desk.Create();
	Desk.__StartGame();
}
