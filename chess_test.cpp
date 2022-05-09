#include "Custom.h"
#include "sfml_views.h"

int main()
{
    using namespace std;
    using namespace sf;
    setlocale(2, "Rus");

    upload();

    //кнопки основного меню
    MenuButton main_game(L"Игра для двоих", sf::Vector2f(0, 0));
    MenuButton check_one_move(L"Мат в 1 ход", sf::Vector2f(0, 100));
    MenuButton check_two_moves(L"Мат в 2 хода", sf::Vector2f(0, 200));
    MenuButton check_three_moves(L"Мат в 3 хода", sf::Vector2f(0, 300));
    MenuButton constructor(L"Конструктор", sf::Vector2f(0, 400));
    MenuButton exit_(L"Выход", sf::Vector2f(0, 500));

    //кнопки меню и переменные для реализации диалога при выборе конструктора
    bool constructor_was_pressed = false;
    MenuButton constructor_header(L"Выберите режим конструктора", sf::Vector2f(0, 0));
    MenuButton constructor_play(L"Играть в созданную задачу", sf::Vector2f(0, 100));
    MenuButton constructor_add(L"Создать задачу", sf::Vector2f(0, 200));
    MenuButton constructor_edit(L"Изменить задачу", sf::Vector2f(0, 300));
    MenuButton constructor_main_game(L"Игра для двоих", sf::Vector2f(0, 100));
    MenuButton constructor_check_one_move(L"Мат в 1 ход", sf::Vector2f(0, 200));
    MenuButton constructor_check_two_moves(L"Мат в 2 хода", sf::Vector2f(0, 300));
    MenuButton constructor_check_three_moves(L"Мат в 3 хода", sf::Vector2f(0, 400));
    MenuButton constructor_entered(L"Закончить ввод", sf::Vector2f(0, 400));
    MenuButton empty_button(L"", sf::Vector2f(0, 400));
    std::string task_name = "";
    MenuButton task_name_out(L"", sf::Vector2f(0, 200));
    int constructor_workmode = -1;
    int constructor_gamemode = -1;


    RenderWindow window(sf::VideoMode(600, 600), "Chess created by Timur && Vladimir");
    window.setIcon(768, 768, icon.getPixelsPtr());

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                Vector2i mouse_pos = Mouse::getPosition(window);
                
                if (!constructor_was_pressed)
                {
                    if (main_game.Pressed(mouse_pos))
                        Board::StartGame();
                    if (check_one_move.Pressed(mouse_pos))
                        QuizCheck::StartGame(1);
                    if (check_two_moves.Pressed(mouse_pos))
                        QuizCheck::StartGame(2);
                    if (check_three_moves.Pressed(mouse_pos))
                        QuizCheck::StartGame(3);
                    if (constructor.Pressed(mouse_pos))
                    {
                        constructor_was_pressed = true;
                        exit_.setString(L"Назад");
                    }
                    if (exit_.Pressed(mouse_pos))
                        window.close();
                }
                else
                {
                    if (constructor_workmode == -1)
                    {
                        if (constructor_play.Pressed(mouse_pos))
                            constructor_workmode = 0;
                        if (constructor_add.Pressed(mouse_pos))
                            constructor_workmode = 1;
                        if (constructor_edit.Pressed(mouse_pos))
                            constructor_workmode = 2;
                        if (exit_.Pressed(mouse_pos))
                        {
                            exit_.setString(L"Выход");
                            constructor_was_pressed = false;
                        }
                    }
                    else
                    {
                        if (constructor_gamemode == -1)
                        {
                            if (constructor_main_game.Pressed(mouse_pos))
                            {
                                constructor_gamemode = 0;
                                constructor_header.setString(L"Введите название задачи");
                            }   
                            if (constructor_check_one_move.Pressed(mouse_pos))
                            {
                                constructor_gamemode = 1;
                                constructor_header.setString(L"Введите название задачи");
                            }
                            if (constructor_check_two_moves.Pressed(mouse_pos))
                            {
                                constructor_gamemode = 2;
                                constructor_header.setString(L"Введите название задачи");
                            }
                            if (constructor_check_three_moves.Pressed(mouse_pos))
                            {
                                constructor_gamemode = 3;
                                constructor_header.setString(L"Введите название задачи");
                            }
                                
                            if (exit_.Pressed(mouse_pos))
                            {
                                constructor_header.setString(L"Введите название задачи");
                                constructor_workmode = -1;
                            }
                        }
                        else
                        {
                            if (constructor_entered.Pressed(mouse_pos))
                            {
                                switch (constructor_workmode)
                                {
                                case 0:
                                    Custom::Play(constructor_gamemode, task_name); break;
                                case 1:
                                    Custom::Add(constructor_gamemode, task_name); break;
                                case 2:
                                    Custom::Edit(constructor_gamemode, task_name); break;
                                default:
                                    break;
                                }
                            }

                            if (exit_.Pressed(mouse_pos))
                            {
                                constructor_gamemode = -1;
                                task_name = "";
                                task_name_out.setString(task_name);
                                constructor_header.setString(L"Выберите режим конструктора");
                            }

                        }
                    }

                }
                
                while (Mouse::isButtonPressed(Mouse::Left));
            }

            if (constructor_workmode != -1 && event.type == sf::Event::TextEntered)
            {
                task_name += event.text.unicode;
                task_name_out.setString(task_name);
            }
        }
        
        window.clear();
        
        if (!constructor_was_pressed)
        {
            main_game.Draw(window);
            check_one_move.Draw(window);
            check_two_moves.Draw(window);
            check_three_moves.Draw(window);
            constructor.Draw(window);
        }
        else
        {
            if (constructor_workmode == -1)
            {
                constructor_header.Draw(window);
                constructor_play.Draw(window);
                constructor_add.Draw(window);
                constructor_edit.Draw(window);
                empty_button.setPosition(sf::Vector2f(0, 400));
                empty_button.Draw(window);
            }
            else
            {
                if (constructor_gamemode == -1)
                {
                    constructor_header.Draw(window);
                    constructor_main_game.Draw(window);
                    constructor_check_one_move.Draw(window);
                    constructor_check_two_moves.Draw(window);
                    constructor_check_three_moves.Draw(window);
                }
                else
                {
                    constructor_header.Draw(window);
                    task_name_out.Draw(window);
                    constructor_entered.Draw(window);
                    empty_button.setPosition(sf::Vector2f(0, 100));
                    empty_button.Draw(window);
                    empty_button.setPosition(sf::Vector2f(0, 300));
                    empty_button.Draw(window);
                }
            }
        }
        exit_.Draw(window);

        window.display();
    }


    return 0;
}
