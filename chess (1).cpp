#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

class Figure;
using namespace std;
const char cellw = '*';
const char cellb = ' ';
const char fb = 'Ч';
const char fw = 'Б';
const char pawn = 'П';
const char horse = 'К';
const char king = 'Ц';
const char queen = 'Ф';
const char elephant = 'С';
const char rook = 'Л';
const char empty_ = '0';
struct cell
{
	bool occ;//occupancy-заполненность(0-пустая, 1- заполненная)
	char cell_c;//cell color - цвет ячейки (w-white, b-black)
	char figure_c;// figure color ((w-white, b-black, 0-пусто)
	char figure;
};
struct permission
{
	int allowfor;
	
};
cell field_base [8][8];

void create_fieldbase()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (i % 2 + j % 2 - 1 == 0)
				field_base[i][j].cell_c = 'b';
			else
				field_base[i][j].cell_c = 'w';
		}
	field_base[3][3].occ = true;
	field_base[3][3].figure_c = 'b';
	field_base[3][3].figure = 'r';

	field_base[6][4].occ = true;
	field_base[6][4].figure_c = 'w';
	field_base[6][4].figure = 'p';


}
void alteration()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (field_base[i][j].occ == false)
			{
				field_base[i][j].figure_c = empty_;
				field_base[i][j].figure = empty_;
			}
}

void move()
{
	char x1,x2;
	int y1,y2;
	bool flag = true;
	do
	{ 
		cin >> x1 >> y1 >> x2 >> y2;
		int x = 0;
		if (x1 < 'A' || x1>'H' || y1 < 1 || y1>8 || x2 < 'A' || x2 > 'H' || y2 < 1 || y2 > 8)
		{
			cout << "Данная позиция отсутствует" << '\n';
			flag = false;
		}
		else
		{
				switch (x1)
				{
					case 'A':
						x = 0;
						break;
					case 'B':
						x = 1;
						break;
					case 'C':
						x = 2;
						break;
					case 'D':
						x = 3;
						break;
					case 'E':
						x = 4;
						break;
					case 'F':
						x = 5;
						break;
					case 'G':
						x = 6;
						break;
					case 'H':
						x = 7;
						break;
				}
			if (field_base[8 - y1][x].occ == false)
			{
				cout << "На выбранной позиции отсутствует фигура" << '\n';
				flag = false;
			}
			else if (field_base[8 - y1][x].occ == true)
			{

				int xt = 0;
				switch (x2)
				{
					case 'A':
						xt = 0;
						break;
					case 'B':
						xt = 1;
						break;
					case 'C':
						xt = 2;
						break;
					case 'D':
						xt = 3;
						break;
					case 'E':
						xt = 4;
						break;
					case 'F':
						xt = 5;
						break;
					case 'G':
						xt = 6;
						break;
					case 'H':
						xt = 7;
						break;
				}
				if (field_base[8 - y2][xt].occ == true)
				{
					cout << "Там стоит фигура, пока хз какого цвета, поэтому бан" << '\n';
					flag = false;
				}
				else if (field_base[8 - y2][xt].occ == false)
				{
					field_base[8 - y2][xt].occ = true;
					field_base[8 - y2][xt].figure_c = field_base[8 - y1][x].figure_c;
					field_base[8 - y2][xt].figure = field_base[8 - y1][x].figure;
					field_base[8 - y1][x].occ = false;
					flag = true;
				}
			}
		}
	} while (flag == false);
}

//void print_startfield()
//{
//	string field[24];
//	for (int i = 0; i < 24; i++)
//	{
//		for (int j = 0; j < 32; j++)
//			if (field_base[i / 3][j / 4].cell_c == 'w')
//				field[i].insert(j, 1, cellw);
//			else
//				field[i].insert(j, 1, cellb);
//	}
//
//	
//}

void print_field()
{
	
	string field[24];
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 32; j++)
			if (field_base[i / 3][j / 4].cell_c == 'w')
				field[i].insert(j, 1, cellw);
			else
				field[i].insert(j, 1, cellb);
	}

	
	
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (field_base[i][j].occ == true)
			{
				if (field_base[i][j].figure_c == 'b')
					field[i * 3 + 1][j * 4 + 1] = fb;
				else if (field_base[i][j].figure_c == 'w')
					field[i * 3 + 1][j * 4 + 1] = fw;
				switch (field_base[i][j].figure)
				{
				case 'p':
					field[i * 3 + 1][j * 4 + 2] = pawn;
					break;
				case 'h':
					field[i * 3 + 1][j * 4 + 2] = horse;
					break;
				case 'k':
					field[i * 3 + 1][j * 4 + 2] = king;
					break;
				case 'q':
					field[i * 3 + 1][j * 4 + 2] = queen;
					break;
				case 'e':
					field[i * 3 + 1][j * 4 + 2] = elephant;
					break;
				case 'r':
					field[i * 3 + 1][j * 4 + 2] = rook;
					break;

				}
			}


			if (field_base[i][j].occ == false)
				if (field_base[i][j].cell_c == 'b')
					field[i * 3][j * 4] = cellb;
				else if (field_base[i][j].cell_c == 'w')
					field[i * 3][j * 4] = cellw;
			
				
		}

	for (int i = 0; i < 24; i++)
	{
		if (i % 3 != 1)
			cout << field[i] << '\n';
		else
			cout << field[i] << ' ' << 8 - i / 3 << '\n';
	}
	for (int j = 0; j < 32; j++)
		cout << (j % 4 == 1 ? (char)('A' + j / 4) : ' ');
	cout << '\n';
}

int main()
{
	system("cls");
	setlocale(2, "Rus");
	create_fieldbase();
	print_field();
	move();
	alteration();
	print_field();
}
//char field[24][33];
//vector<Figure> figures;
//
//const char w = '*';
//const char b = ' ';
//const char black = 'Ч';
//const char white = 'Б';
//const char pawn = 'П';
//const char horse = 'К';
//const char king = 'Ц';
//const char queen = 'Ф';
//const char elephant = 'С';
//const char rook = 'Л';
//
//class Figure
//{
//protected:
//
//	int x;
//	int y;
//	//white - 1 
//	//black - 0
//	int color;
//
//	Figure(int x, int y, int color)
//	{
//		this->x = x;
//		this->y = y;
//		this->color = color;
//	}
//
//public:
//
//	void Print()
//	{
//		cout << x << ' ' << y << ' ' << (color == 1 ? "white" : "black") << '\n';
//	}
//
//};
//class Pawn : Figure
//{
//public:
//
//	Pawn(int x, int y, int color) : Figure(x, y, color) {};
//
//	static void __init__()
//	{
//		//black - 5
//		for (int i = 0; i < 32; i++)
//			if (i % 4 == 1)
//			{
//				field[19][i] = white;
//				field[4][i] = black;
//
//				field[19][i + 1] = pawn;
//				field[4][i + 1] = pawn;
//
//				figures.push_back(Pawn(19, i, 1));
//				figures.push_back(Pawn(4, i, 0));
//			}
//
//	}
//
//	static bool check(Pawn init, int x, int y)
//	{
//		if (field[19] [init.x % 4] == pawn)
//			if(field[19][init.x % 4] == pawn)
//	}
//};
//class Horse : Figure
//{
//public:
//
//	Horse(int x, int y, int color) : Figure(x, y, color) {};
//
//	static void __init__()
//	{
//		for (int i = 0; i < 32; i++)
//			if (i == 5 || i == 25)
//			{
//				field[1][i] = black;
//				field[1][i + 1] = horse;
//				field[22][i] = white;
//				field[22][i + 1] = horse;
//
//				figures.push_back(Horse(1, i, 0));
//				figures.push_back(Horse(22, i, 1));
//			}
//	}
//
//};
//class King :Figure
//{
//public:
//
//	King(int x, int y, int color) : Figure(x, y, color) {};
//
//	static void __init__()
//	{
//		for (int i = 0; i < 32; i++)
//			if (i == 13)
//			{
//				field[1][i] = black;
//				field[1][i + 1] = king;
//				field[22][i] = white;
//				field[22][i + 1] = king;
//
//				figures.push_back(King(1, i, 0));
//				figures.push_back(King(22, i, 1));
//			}
//	}
//};
//class Queen :Figure
//{
//public:
//
//	Queen(int x, int y, int color) : Figure(x, y, color) {};
//
//	static void __init__()
//	{
//		for (int i = 0; i < 32; i++)
//			if (i == 17)
//			{
//				field[1][i] = black;
//				field[1][i + 1] = queen;
//				field[22][i] = white;
//				field[22][i + 1] = queen;
//
//				figures.push_back(Queen(1, i, 0));
//				figures.push_back(Queen(22, i, 1));
//			}
//	}
//};
//class Elephant :Figure
//{
//public:
//
//	Elephant(int x, int y, int color) : Figure(x, y, color) {};
//
//	static void __init__()
//	{
//		for (int i = 0; i < 32; i++)
//			if (i == 9 || i == 21)
//			{
//				field[1][i] = black;
//				field[1][i + 1] = elephant;
//				field[22][i] = white;
//				field[22][i + 1] = elephant;
//
//				figures.push_back(Elephant(1, i, 0));
//				figures.push_back(Elephant(22, i, 1));
//			}
//	}
//};
//class Rook :Figure
//{
//public:
//
//	Rook(int x, int y, int color) : Figure(x, y, color) {};
//
//	static void __init__()
//	{
//		for (int i = 0; i < 32; i++)
//			if (i == 1 || i == 29)
//			{
//				field[1][i] = black;
//				field[1][i + 1] = rook;
//				field[22][i] = white;
//				field[22][i + 1] = rook;
//
//				figures.push_back(Rook(1, i, 0));
//				figures.push_back(Rook(22, i, 1));
//			}
//	}
//};
//
//void create_field()
//{
//	for (int i = 0; i < 24; i++)
//		for (int j = 0; j < 32; j++)
//			if (i / 3 % 2 + j / 4 % 2 - 1)
//				field[i][j] = w;
//			else
//				field[i][j] = b;
//	Pawn::__init__();
//	Horse::__init__();
//	King::__init__();
//	Queen::__init__();
//	Elephant::__init__();
//	Rook::__init__();
//}
//void print_field()
//{
//	for (int i = 0; i < 24; i++) {
//		for (int j = 0; j < 32; j++)
//			cout << field[i][j];
//		if (i % 3 == 1)
//			cout << ' ' << (24 - i) / 3 + 1;
//		cout << '\n';
//	}
//	for (int j = 0; j < 32; j++)
//		cout << (j % 4 == 1 ? (char)('A' + j / 4) : ' ');
//	cout << '\n';
//}
//
//
//
//int main()
//{
//	setlocale(2, "Rus");
//	create_field();
//}