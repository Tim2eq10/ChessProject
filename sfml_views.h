#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

const sf::Vector2f cell_size(100, 100);
const sf::Vector2i cell_si(100, 100);
const sf::IntRect std_int_rect(0, 0, 100, 100);

const std::string path_pack = "images\\classic\\";
const std::string path_ultimate = "images\\ultimate\\";

extern sf::Font main_font, title_font;

const char figures_char[6]{ king, queen, elephant, horse, rook, pawn };
extern std::map<int, sf::Text> title_bar_text;
extern std::map<int, std::wstring> description_text;
extern std::map<const char, sf::Texture> cell_color_t;
extern std::map<const char, sf::Sprite> cell_color;
extern std::map<const char, sf::Texture> black_figures_t;
extern std::map<const char, sf::Texture> white_figures_t;
extern std::map<const char, std::map<const char, sf::Texture>> figure_t;
extern std::map<const char, sf::Sprite> black_figures;
extern std::map<const char, sf::Sprite> white_figures;
extern std::map<const char, std::map<const char, sf::Sprite>> figure;

const sf::Vector2f trans_start_pos(870, 350);
const sf::Vector2i trans_menu_size(300, 75);
extern sf::RectangleShape trans_menu_back;
extern sf::Text trans_text;

extern sf::Texture logo_t;
extern sf::Sprite  logo;
extern sf::Image icon;
extern sf::Texture figure_chosen_t, allowed_t, check_warning_t, back_menu_t, menu_sep_t;
extern sf::Sprite  figure_chosen, allowed_s, check_warning, back_menu, menu_sep;


class Button
{
protected:
	std::string path;
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Button(const sf::String& path_, sf::Vector2f pos_, sf::Vector2f size_);
	virtual void Draw(sf::RenderWindow& window);
	virtual bool Pressed(sf::Vector2i mouse_pos);
	virtual void setPosition(sf::Vector2f pos_);
	virtual void setSize(sf::Vector2f size_);
};

class InfoButton :public Button
{
private:
	sf::Text text;
	int condition = 0;
public:
	InfoButton(std::wstring text_);
	void Draw(sf::RenderWindow& window) override;
	bool Pressed(sf::Vector2i mouse_pos) override;
};

class HintButton : public Button
{
private:
	int condition = 0;
	std::string hint_move;
	sf::Texture hint_t;
	sf::Sprite hint;
public:
	HintButton(std::string hint_move_);
	void Draw(sf::RenderWindow& window) override;
	bool Pressed(sf::Vector2i mouse_pos) override;;
	void update(std::string hint_move_);
};

class ChangeQuizButton : public Button
{
private:
	sf::Text text;
public:
	ChangeQuizButton(std::string mode_);
	void Draw(sf::RenderWindow& window) override;
};

class Mistakes : public Button
{
private:
	int amount;
	sf::Text text;
public:
	Mistakes();
	void update(int amount_of_mistakes);
	void Draw(sf::RenderWindow& window) override;
};

class MenuButton :public Button
{
private:
	sf::Text text;
public:
	MenuButton(std::wstring text_, sf::Vector2f pos, sf::Vector2f size = sf::Vector2f(600, 100));
	void Draw(sf::RenderWindow& window) override;
	void setString(const sf::String& text_);
};

class GameMenuButton : public Button
{
private:
	sf::Text text;
public:
	GameMenuButton(std::string path_, const sf::String& text_, sf::Vector2f pos_, sf::Vector2f size_);
	virtual void Draw(sf::RenderWindow& window) override;
};

bool in_field(sf::Vector2i pos);
void upload();