#include "sfml_views.h"

sf::Font main_font, title_font;

std::map<int, sf::Text> title_bar_text = {
	{0, sf::Text(L"Игра для двоих", title_font)},
	{1, sf::Text(L"Мат в 1 ход", title_font)},
	{2, sf::Text(L"Мат в 2 хода", title_font)},
	{3, sf::Text(L"Мат в 3 хода", title_font)}
};
std::map<int, std::wstring> description_text = {
	{0, std::wstring(
		L"Игроки ходят по очереди.\n"
		L"Белые всегда ходят первыми.\n"
		L"Белые выбирают фигуру, которой будут\n"
		L"ходить, и ставят ее на другую клетку,\n"
		L"исходя из правил передвижения\n"
		L"этой фигуры.\n"
		L"Поставьте королю противника\n"
		L"шах, от которого он не сможет\n"
		L"найти защиту или отступить на\n"
		L"другие поля шахматной доски.\n"
		L"Неотразимый шах королю в\n"
		L"шахматах называется мат.\n"
	)},
	{1, std::wstring(
		L"Поставьте королю противника\n"
		L"шах, от которого он не сможет\n"
		L"найти защиту или отступить на\n"
		L"другие поля шахматной доски.\n"
		L"Неотразимый шах королю в\n"
		L"шахматах называется мат.\n"
		L"У вас есть один ход для победы."
	)},
	{2, std::wstring(
		L"Поставьте королю противника\n"
		L"шах, от которого он не сможет\n"
		L"найти защиту или отступить на\n"
		L"другие поля шахматной доски.\n"
		L"Неотразимый шах королю в\n"
		L"шахматах называется мат.\n"
		L"У вас есть два хода для победы."
	)},
	{3, std::wstring(
		L"Поставьте королю противника\n"
		L"шах, от которого он не сможет\n"
		L"найти защиту или отступить на\n"
		L"другие поля шахматной доски.\n"
		L"Неотразимый шах королю в\n"
		L"шахматах называется мат.\n"
		L"У вас есть три хода для победы."
	)},
};

std::map<const char, sf::Texture> cell_color_t = {
	{black, sf::Texture()},
	{white, sf::Texture()}
};
std::map<const char, sf::Sprite> cell_color = {
	{black, sf::Sprite()},
	{white, sf::Sprite()}
};
std::map<const char, sf::Texture> black_figures_t = {
	{king, sf::Texture()},
	{queen, sf::Texture()},
	{elephant, sf::Texture()},
	{horse, sf::Texture()},
	{rook, sf::Texture()},
	{pawn, sf::Texture()}
};
std::map<const char, sf::Texture> white_figures_t = black_figures_t;
std::map<const char, std::map<const char, sf::Texture>> figure_t = {
	{black, black_figures_t},
	{white, white_figures_t}
};
std::map<const char, sf::Sprite> black_figures = {
	{king, sf::Sprite()},
	{queen, sf::Sprite()},
	{elephant, sf::Sprite()},
	{horse, sf::Sprite()},
	{rook, sf::Sprite()},
	{pawn, sf::Sprite()}
};
std::map<const char, sf::Sprite> white_figures = black_figures;
std::map<const char, std::map<const char, sf::Sprite>> figure = {
	{black, black_figures},
	{white, white_figures}
};

sf::Image icon;
sf::Texture logo_t;
sf::Sprite  logo;
sf::Texture figure_chosen_t, allowed_t, check_warning_t, back_menu_t, menu_sep_t;
sf::Sprite  figure_chosen, allowed_s, check_warning, back_menu, menu_sep;

sf::RectangleShape trans_menu_back;
sf::Text trans_text(L"Выберите фигуру", main_font);

bool in_field(sf::Vector2i pos)
{
	return (pos.x <= 800 && pos.x >= 0) && (pos.y <= 800 && pos.y >= 0);
}
void upload()
{
	//загрузка всего
	using namespace sf;
	//шрифты & тексты
	main_font.loadFromFile(path_ultimate + "main_font.ttf");
	title_font.loadFromFile(path_ultimate + "title_font.otf");
	for (int i = 0; i < 4; i++) {
		title_bar_text[i].setFillColor(Color::Black);
		title_bar_text[i].setCharacterSize(30);
		FloatRect size = title_bar_text[i].getLocalBounds();
		title_bar_text[i].setOrigin(size.left + size.width * 0.5f, size.top + size.height * 0.5f);
		title_bar_text[i].setPosition((1200.0 + 830.0) / 2, 30);
	}
	trans_text.setPosition(Vector2f((float)trans_start_pos.x, (float)trans_start_pos.y - 35));
	trans_text.setFillColor(Color::Black);
	trans_text.setCharacterSize(20);
	//текстуры и спрайты ячеек
	cell_color_t[black].loadFromFile(path_pack + "bc.jpg", std_int_rect);
	cell_color[black].setTexture(cell_color_t[black]);
	cell_color_t[white].loadFromFile(path_pack + "wc.jpg", std_int_rect);
	cell_color[white].setTexture(cell_color_t[white]);
	//текстуры и спрайты фигур
	for (int i = 0; i < 6; i++)
	{
		figure_t[white][figures_char[i]].loadFromFile(path_pack + "m_all_const.png", IntRect(Vector2i(100 * i, 0), cell_si));
		figure_t[black][figures_char[i]].loadFromFile(path_pack + "m_all_const.png", IntRect(Vector2i(100 * i, 100), cell_si));
		figure[white][figures_char[i]].setTexture(figure_t[white][figures_char[i]]);
		figure[black][figures_char[i]].setTexture(figure_t[black][figures_char[i]]);
	}
	//текстуры и спрайты подсказок
	figure_chosen_t.loadFromFile(path_ultimate + "figure_chosen.png", std_int_rect);
	figure_chosen.setTexture(figure_chosen_t);
	allowed_t.loadFromFile(path_ultimate + "allowed.png", std_int_rect);
	allowed_s.setTexture(allowed_t);
	check_warning_t.loadFromFile(path_ultimate + "check_warning.png", std_int_rect);
	check_warning.setTexture(check_warning_t);
	//текстуры и спрайты бокового меню
	back_menu_t.loadFromFile(path_ultimate + "back_menu.jpg", IntRect(0, 0, 400, 800));
	back_menu.setTexture(back_menu_t);
	back_menu.setPosition(800, 0);
	menu_sep_t.loadFromFile(path_ultimate + "menu_sep.jpg", IntRect(0, 0, 30, 800));
	menu_sep.setTexture(menu_sep_t);
	menu_sep.setPosition(800, 0);
	trans_menu_back.setSize(Vector2f((float)trans_menu_size.x, (float)trans_menu_size.y + 50));
	trans_menu_back.setFillColor(Color::Cyan);
	trans_menu_back.setOutlineColor(Color::Black);
	trans_menu_back.setOutlineThickness(5);
	trans_menu_back.setPosition(Vector2f(trans_start_pos.x, trans_start_pos.y - 35));
	logo_t.loadFromFile(path_ultimate + "logo.jpg");
	logo.setTexture(logo_t);
	logo.setPosition(830, 522);
	//
	icon.loadFromFile(path_ultimate + "vt.png");
}


Button::Button(const sf::String& path_, sf::Vector2f pos_, sf::Vector2f size_)
{
	path = path_;
	pos = pos_;
	size = size_;
	texture.loadFromFile(path, sf::IntRect(0, 0, (int)size.x, (int)size.y));
	sprite.setTexture(texture);
}
void Button::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(pos);
	window.draw(sprite);
}
bool Button::Pressed(sf::Vector2i mouse_pos)
{
	return (mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + size.x &&
		mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + size.y);
}
void Button::setPosition(sf::Vector2f pos_)
{
	pos.x = pos_.x;
	pos.y = pos_.y;
}
void Button::setSize(sf::Vector2f size_)
{
	size.x = size_.x;
	size.y = size_.y;
}

InfoButton::InfoButton(std::wstring text_) :Button(path_ultimate + "info.png",
	sf::Vector2f(850, 100),
	sf::Vector2f(50, 50))
{
	text.setFont(main_font);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(15);
	text.setString(text_);
	text.setPosition(sf::Vector2f(sf::Vector2f(pos.x + size.x * (float)0.7, pos.y + size.y * (float)0.7)));
}
void InfoButton::Draw(sf::RenderWindow& window)
{
	Button::Draw(window);
	if (condition)
	{
		sf::FloatRect size = text.getGlobalBounds();
		sf::RectangleShape back(sf::Vector2f(size.width + 15, size.height + 15));
		back.setFillColor(sf::Color::White);
		back.setPosition(sf::Vector2f(size.left - 5, size.top - 5));
		window.draw(back);
		window.draw(text);
	}
}
bool InfoButton::Pressed(sf::Vector2i mouse_pos)
{
	if (Button::Pressed(mouse_pos))
		condition = 1 - condition;
	return Button::Pressed(mouse_pos);
}

HintButton::HintButton(std::string hint_move_) :Button(path_ultimate + "hint.png",
	sf::Vector2f(900, 100),
	sf::Vector2f(50, 50))
{
	hint_move = hint_move_;
	hint_t.loadFromFile(path_ultimate + "hint_show.png", std_int_rect);
	hint.setTexture(hint_t);
}
void HintButton::Draw(sf::RenderWindow& window)
{
	Button::Draw(window);
	if (condition)
	{
		int w1 = hint_move[0] - '0';
		int h1 = hint_move[1] - '0';
		int w2 = hint_move[2] - '0';
		int h2 = hint_move[3] - '0';
		
		hint.setPosition((float)100 * h1, (float)100 * w1);
		window.draw(hint);
		hint.setPosition((float)100 * h2, (float)100 * w2);
		window.draw(hint);
	}
}
bool HintButton::Pressed(sf::Vector2i mouse_pos)
{
	if (Button::Pressed(mouse_pos))
		condition = 1 - condition;
	return Button::Pressed(mouse_pos);
}
void HintButton::update(std::string hint_move_)
{
	if (hint_move != hint_move_)
	{
		hint_move = hint_move_;
		condition = 0;
	}
}

ChangeQuizButton::ChangeQuizButton(std::string mode_) :Button(path_ultimate + "dark_plank.jpg",
	(mode_ == "prev" ? sf::Vector2f(850, 170) : sf::Vector2f(1025, 170)),
	sf::Vector2f(150, 50))
{
	text.setFont(main_font);
	if (mode_ == "prev")
		text.setString(L"Предыдущее\n    задание");
	else if(mode_ == "next")
		text.setString(L"Следующее\n   задание");
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::White);

	sf::FloatRect txt_size = text.getGlobalBounds();
	text.setOrigin(txt_size.left + txt_size.width * 0.5f, txt_size.top + txt_size.height * 0.5f);
	text.setPosition(pos.x + size.x * 0.5f, pos.y + size.y * 0.5f);
}
void ChangeQuizButton::Draw(sf::RenderWindow& window)
{
	Button::Draw(window);
	window.draw(text);
}

Mistakes::Mistakes() :Button(path_ultimate + "mistakes.png",
	sf::Vector2f(950, 100),
	sf::Vector2f(50, 50))
{
	amount = 0;

	text.setFont(main_font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);

	text.setString(std::to_string(amount));
	sf::FloatRect txt_size = text.getGlobalBounds();
	text.setOrigin(txt_size.left + txt_size.width * 0.5f, txt_size.top + txt_size.height * 0.5f);
	text.setPosition(pos.x + size.x * 0.5f, pos.y + size.y * 0.5f);
}
void Mistakes::update(int amount_of_mistakes)
{
	if (amount == 99)
		return;
	if (amount == amount_of_mistakes)
		return;
	amount = amount_of_mistakes;
	text.setString(std::to_string(amount));

	if (amount == 10)
	{
		sf::FloatRect txt_size = text.getLocalBounds();
		text.setOrigin(txt_size.left + txt_size.width * 0.5f, txt_size.top + txt_size.height * 0.5f);
		text.setPosition(pos.x + size.x * 0.5f, pos.y + size.y * 0.5f);
	}

}
void Mistakes::Draw(sf::RenderWindow& window)
{
	Button::Draw(window);
	window.draw(text);
}

MenuButton::MenuButton(std::wstring text_, sf::Vector2f pos, sf::Vector2f size) :
	Button(path_ultimate + "main_menu_back.jpg", pos, size)
{
	setString(text_);
}
void MenuButton::Draw(sf::RenderWindow& window)
{
	Button::Draw(window);
	window.draw(text);
}
void MenuButton::setString(const sf::String& text_)
{
	text.setFont(main_font);
	text.setString(text_);
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Black);
	sf::FloatRect size = text.getLocalBounds();
	text.setOrigin(size.left + size.width * 0.5f, size.top + size.height * 0.5f);
	text.setPosition(pos.x + this->size.x * 0.5f, pos.y + this->size.y * 0.5f);
}

GameMenuButton::GameMenuButton(std::string path_, const sf::String& text_, sf::Vector2f pos_, sf::Vector2f size_):
	Button(path_, pos_, size_)
{
	text.setFont(main_font);
	text.setString(text_);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::White);
	sf::FloatRect size = text.getLocalBounds();
	text.setOrigin(size.left + size.width * 0.5f, size.top + size.height * 0.5f);
	text.setPosition(pos.x + size_.x * 0.5f, pos.y + size_.y * 0.5f);
}
void GameMenuButton::Draw(sf::RenderWindow& window)
{
	Button::Draw(window);
	window.draw(text);
}
