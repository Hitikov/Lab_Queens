#include <iostream>

using namespace std;

static short int desk[66][8] = { {0, 1, 2, 3, 4, 5, 6, 7} };
bool show_desk = false;

void desk_rec(int n);
void desk_print(int n, int curs);
void desk_place(int n);
void desk_print_all();

int main()
{
	system("chcp 1251");
	int n;

	cout << "Введите номер столбца в верхней строке, с которого хотите начать: ";
	cin >> desk[1][0];
	desk[1][0]--;

	cout << "Если хотите просматривать каждый отдельный шаг рекурсии, введите 1, введите любую другую цифру для вывода только финальной позиции: ";
	cin >> n;

	switch (n)
	{
	case 1:
		cout << "Вывод выполнен в псевдографическом стиле, где x - клетки под атакой, Q - ферзи." << endl;
		show_desk = true;
	}

	cout << endl;
	system("chcp 866");
	desk_rec(0);
	system("chcp 1251");

	cout << "Финальный вариант расставления" << endl << endl;

	system("chcp 866");
	desk_print_all();
	system("chcp 1251");

	system("pause");

	return 0;
}

void desk_rec(int n)
{	
	if (desk[1][7] == 0) 
	{		
		if (n == 0)
		{
			desk_place(0);
			if (show_desk)
			{
				desk_print(0, -1);
				system("chcp 1251");

				cout << endl;
				cout << "В столбце " << 1 << " строки " << desk[1][0] << " найдена свободная клетка." << endl;
				cout << "\tПереход на более глубокий уровень рекурсии. Вызов desk_rec(" << 1 << ")" << endl << endl;

				system("pause");
				system("chcp 866");
				cout << endl;
			}
			desk_rec(n + 1);
		}
		else 
		{
			for (int i = 0; i < 8; ++i) 
			{
				if (show_desk)
				{
					desk_print(n - 1, i);
					system("pause");
				}
				if (desk[n + (n - 1) * 8 + 2][i] == 0 && (desk[1][7] == 0))
				{
					desk[1][n] = i;
					desk_place(n);
					if (show_desk)
					{
						desk_print(n, -1);
						system("chcp 1251");
						cout << endl;
						cout << "В столбце " << i + 1 << " строки " << n + 1 << " найдена свободная клетка." << endl;
						cout << "\tПереход на более глубокий уровень рекурсии. Вызов desk_rec(" << n + 1 << ")" << endl << endl;
						system("pause");
						system("chcp 866");
						cout << endl;
					}
					desk_rec(n + 1);
					if ((desk[1][7] == 0) && (show_desk))
					{
						system("chcp 1251");
						cout << endl;
						cout << "Нет расстановок удовледтворяющих решению, возврат на более высокий уровень." << endl << endl;
						system("pause");
						system("chcp 866");
					}
				}
			}
		}
	}
}

void desk_print(int n, int curs)
{
	cout << "   A   B   C   D   E   F   G   H" << endl;

	cout << " \xDA";
	for (int i = 0; i < 7; ++i)
	{
		cout << "\xC4\xC4\xC4" << '\xC2';
	}
	cout << "\xC4\xC4\xC4\xBF" << endl;

	for (int i = 0; i < 7; ++i)
	{
		cout << 8 - i << "\xB3";
		for (int j = 0; j < 8; ++j)
		{
			//cout << ' ' << desk[i + n * 8 + 2][j] << ' ';
			switch (desk[i + n * 8 + 2][j])
			{
			case 0:
				if ((i == n + 1) && (j == curs)) cout << "[ ]";
				else cout << "   ";
				break;
			case 1:
				if ((i == n + 1) && (j == curs)) cout << "[\x78]";
				else cout << " \x78 ";
				break;
			case 8:
				if ((i == n + 1) && (j == curs)) cout << "[\x51]";
				else cout << " \x51 ";
				break;
			}
			cout << "\xB3";
		}
		cout << endl;

		cout << " \xC3";
		for (int j = 0; j < 7; ++j)
		{
			cout << "\xC4\xC4\xC4\xC5";
		}
		cout << "\xC4\xC4\xC4\xB4" << endl;

	}

	cout << 1 << "\xB3";
	for (int j = 0; j < 8; ++j)
	{
		//cout << ' ' << desk[7 + n * 8 + 2][j] << ' ';
		switch (desk[7 + n * 8 + 2][j])
		{
		case 0:
			if ((n == 6) && (j == curs)) cout << "[ ]";
			else cout << "   ";
			break;
		case 1:
			if ((n == 6) && (j == curs)) cout << "[\x78]";
			else cout << " \x78 ";
			break;
		case 8:
			if ((n == 6) && (j == curs)) cout << "[\x51]";
			else cout << " \x51 ";
			break;
		}
		cout << "\xB3";
	}
	cout << endl;

	cout << " \xC0";
	for (int j = 0; j < 7; ++j)
	{
		cout << "\xC4\xC4\xC4\xC1";
	}
	cout << "\xC4\xC4\xC4\xD9" << endl;
	cout << endl;
}

void desk_place(int n) 
{
	int x = desk[1][n];

	if (n != 0) 
	{
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				desk[i + n * 8 + 2][j] = desk[i + (n - 1) * 8 + 2][j];
			}
		}
	}

	for (int i = 0; i < 8; ++i)
	{
		desk[n + n * 8 + 2][i] = 1;
	}

	for (int i = 0; i < 8; ++i)
	{
		desk[i + n * 8 + 2][x] = 1;
	}

	for (int i = 0; i < 8; ++i)
	{
		if (((x + n - i) > 0) && ((x + n - i) < 8)) 
		{
			desk[(x + n - i) + n * 8 + 2][i] = 1;
		}
		
		if (((n - x + i) > 0) && ((n - x + i) < 8))
		{
			desk[(n - x + i) + n * 8 + 2][i] = 1;
		}
	}
	
	for (int i = 0; i <= n; ++i)
	{
		desk[i + n * 8 + 2][desk[1][i]] = 8;
	}
}

void desk_print_all()
{
	for (int n = 0; n < 8; ++n) {
		desk_print(n, - 1);
	}
}

//Old all
/* void desk_print_all()
{
	for (int n = 0; n < 8; ++n) {
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				cout << desk[i + n * 8 + 2][j];
			}
			cout << endl;
		}
		cout << endl;
	}
} */

//Old print
/*void desk_print(int n)
{
	cout << "   A   B   C   D   E   F   G   H" << endl;

	cout << " \xDA";
	for (int i = 0; i < 7; ++i)
	{
		cout << "\xC4\xC4\xC4" << '\xC2';
	}
	cout << "\xC4\xC4\xC4\xBF" << endl;

	for (int i = 0; i < 7; ++i)
	{
		cout << 8 - i << "\xB3";
		for (int j = 0; j < 8; ++j)
		{
			//cout << ' ' << desk[i + n * 8 + 2][j] << ' ';
			switch (desk[i + n * 8 + 2][j])
			{
			case 0:
				cout << "   ";
				break;
			case 1:
				cout << " \x78 ";
				break;
			case 8:
				cout << " \x51 ";
				break;
			}
			cout << "\xB3";
		}
		cout << endl;

		cout << " \xC3";
		for (int j = 0; j < 7; ++j)
		{
			cout << "\xC4\xC4\xC4\xC5";
		}
		cout << "\xC4\xC4\xC4\xB4" << endl;

	}

	cout << 1 << "\xB3";
	for (int j = 0; j < 8; ++j)
	{
		//cout << ' ' << desk[7 + n * 8 + 2][j] << ' ';
		switch (desk[7 + n * 8 + 2][j])
		{
		case 0:
			cout << "   ";
			break;
		case 1:
			cout << " \x78 ";
			break;
		case 8:
			cout << " \x51 ";
			break;
		}
		cout << "\xB3";
	}
	cout << endl;

	cout << " \xC0";
	for (int j = 0; j < 7; ++j)
	{
		cout << "\xC4\xC4\xC4\xC1";
	}
	cout << "\xC4\xC4\xC4\xD9" << endl;
	cout << endl;
}*/
