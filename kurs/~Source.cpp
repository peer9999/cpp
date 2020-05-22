#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

union MISC {
	int number;
	char note[25];
};

enum TYPE {
	TYPE_INT = 1,
	TYPE_CHAR
};

enum {
	INPUT = 1,
	SORT,
	DELETE,
	ANALYSE,
	WRITE,
	READ,
	EDIT,
	EXIT = 0,
	SORTSIZE = 1,
	SORTCOST,

};

enum RESOLUTION {
	HIGHDEFENITION = 1,
	FULLHD,
	ULTRAHD4K,
	ULTRAHD8K
};

struct Mark_tv {
	char country[30];
	char title[30];
	unsigned int size : 6;
	float cost;
	enum RESOLUTION resolution;
	union MISC misc;
	enum TYPE tag;
};

void func();
int  menu();
void InputStruct  (Mark_tv*, int&);
void OutputStruct (Mark_tv*, int&);
void DeleteStruct (Mark_tv*, int&);
void SortStruct	  (Mark_tv*, int&);
void Sortsize	  (Mark_tv*, int&);
void Sortcost	  (Mark_tv*, int&);
void Analyse	  (Mark_tv*, int&);
void Write		  (Mark_tv*, int&);
void Read		  (Mark_tv*, int&);
void Edit		  (Mark_tv*);

int main()
{
	setlocale(0, "");
	Mark_tv* p = new Mark_tv();
	int f, len = 0;
//	Read(p, len);
	do {
		func();
		OutputStruct(p, len);
		f = menu();
		if (f == 0) break;


		switch (f) {
		case INPUT:
			InputStruct(p, len);
			break;
		case SORT:
			SortStruct(p, len);
			break;
		case DELETE:
			DeleteStruct(p, len);
			break;
		case ANALYSE:
			Analyse(p, len);
			break;
		case WRITE:
			Write(p, len);
			break;
		case READ:
			Read(p, len);
			break;
		case EDIT:
			Edit(p);
			break;
		case EXIT:
			return 0;
		}
	} while (1);
	return 0;
}

void func() {
	system("cls");
	cout << "Меню" << endl;
	cout << "1.Ввод    " << "2.Сортировка    " << "3.Удаление    " << "4.Анализ    " << "5.Запись   " << "6.Чтение    " << "7.Редактирование    " << "0.Выход" << endl << endl;
}

int menu()
{
	int k;
	cout << endl << endl << "Введите номер операции, которую необходимо выполнить : ";
	cin >> k;
	cin.get();
	return k;
}

void InputStruct(Mark_tv* p, int& len)
{
	int i, k, l = len, z, y;
	char misc[16];
	cout << "Количество телевизоров : ";
	cin >> k;
	cin.get();

	for (i = l; i < k + l; i++, len++) {
		cout << i + 1 << "." << setw(2) << "Название : ";
		cin.getline(p[i].title, 30);

		cout << setw(2) << "Страна производитель : ";
		cin.getline(p[i].country, 30);

		cout << setw(2) << "Цена : ";
		cin >> y;
		p[i].cost = y;
		cin.get();

		cout << setw(2) << "Размер по диагонали : ";
		cin >> z;
		p[i].size = z;
		cin.get();

		int input;
		cout << "Разрешение экрана (1 - HD, 2 - FullHD, 3 - 4k UHD, 4 - 8k UHD): ";
		cin >> input;
		cin.get();

		switch (input) {
		case HIGHDEFENITION:
			p[i].resolution = HIGHDEFENITION;
			break;
		case FULLHD:
			p[i].resolution = FULLHD;
			break;
		case ULTRAHD4K:
			p[i].resolution = ULTRAHD4K;
			break;
		case ULTRAHD8K:
			p[i].resolution = ULTRAHD8K;
			break;
		}

		cout << "Дополнительная информация : ";
		cin.get(misc, 16);
		cin.get();
		if (isdigit(misc[0])) {
			p[i].misc.number = atoi(misc);
			p[i].tag = TYPE_INT;
		}
		else {
			strcpy_s(p[i].misc.note, misc);
			p[i].tag = TYPE_CHAR;
		}
	}
}

void Edit(Mark_tv* p) {
	int i;
	char temp[30];
	char misc[16];

	cout << "Введите поле для изменения: ";
	cin >> i;
	cin.get();

	cout << i << "." << setw(2) << "Название : ";
	cin.getline(temp, 30);
	if (temp[0] != '\0') {
		strcpy(p[i - 1].title, temp);
	}

	cout << setw(2) << "Страна производитель : ";
	cin.getline(temp, 30);
	if (temp[0] != '\0') {
		strcpy(p[i - 1].country, temp);
	}

	cout << setw(2) << "Цена : ";
	cin.getline(temp, 30);
	if (temp[0] != '\0') {
		p[i - 1].cost = atoi(temp);
	}

	cout << setw(2) << "Размер по диагонали : ";
	cin.getline(temp, 30);
	if (temp[0] != '\0') {
		p[i - 1].size = atoi(temp);
	}

	//int input;
	//cout << "Разрешение экрана (1 - HD, 2 - FullHD, 3 - 4k UHD, 4 - 8k UHD): ";
	//cin.getline(temp, 30);

	/*if (temp[0] != '\0') {
		cin >> input;
		switch (input) {
		case HIGHDEFENITION:
			p[i - 1].resolution = HIGHDEFENITION;
			break;
		case FULLHD:
			p[i - 1].resolution = FULLHD;
			break;
		case ULTRAHD4K:
			p[i - 1].resolution = ULTRAHD4K;
			break;
		case ULTRAHD8K:
			p[i - 1].resolution = ULTRAHD8K;
			break;
		}
	}
	*/
	cout << "Дополнительная информация : ";
	cin.get(misc, 16);
	cin.get();
	if (misc[0] != '\0') {
		if (isdigit(misc[0])) {
			p[i - 1].misc.number = atoi(misc);
			p[i - 1].tag = TYPE_INT;
		}
		else {
			strcpy_s(p[i - 1].misc.note, misc);
			p[i - 1].tag = TYPE_CHAR;
		}
	}
}

void OutputStruct(Mark_tv* p, int& len)
{
	char resolution[4][25] = { "High Definition(HD)",
		"FullHD",
		"4K(ultra hd)",
		"8k(ultra hd)" };
	int i;
	if (len == 0) {
		cout << endl << endl << "Данные отсутствуют! Используйте операцию \"Ввод\"";
		return;
	}

	cout << setfill('-') << setw(125) << "-" << endl;
	cout << setfill(' ')
		<< "|      |"
		<< setw(20) << "Название" << " |"
		<< setw(10) << "Страна производитель" << " |"
		<< setw(9) << "Цена" << " |"
		<< setw(13) << "Размер по диагонали" << " |"
		<< setw(20) << "Разрешение" << " |"
		<< setw(17) << "Доп.информация" << " |" << endl;
	cout << setfill('-') << setw(125) << "-" << endl;
	for (i = 0; i < len; i++) {
		cout << setfill(' ')
			<< "|" << setw(4) << i + 1 << "." << " |"
			<< setw(20) << p[i].title << " |"
			<< setw(20) << p[i].country << " |"
			<< setw(9) << p[i].cost << " |"
			<< setw(19) << p[i].size << " |"
			<< setw(20) << resolution[p[i].resolution - 1] << " |";
		if (p[i].tag == TYPE_INT) {
			cout << setw(17) << p[i].misc.number << " |" << endl;
		}
		else {
			cout << setw(17) << p[i].misc.note << " |" << endl;
		}
	}
	cout << setfill('-') << setw(125) << "-" << endl;
}

void DeleteStruct(Mark_tv* p, int& len) {
	int z;
	cout << "Введите номер поля для удаления : ";
	cin >> z;
	cin.get();
	for (int i = z - 1; i < len; i++) {
		p[i] = p[i + 1];
	}
	len--;
}

void SortStruct(Mark_tv* p, int& len) {
	int x;
	cout << "1.По цене" << endl;
	cout << "2.По размеру" << endl;
	cin >> x;

	switch (x) {
	case SORTSIZE:
		Sortsize(p, len);
		break;
	case SORTCOST:
		Sortcost(p, len);
		break;
	}
}
void Sortsize(Mark_tv* p, int& len) {
	Mark_tv temp;
	for (int i = 0; i < len; i++) {
		for (int j = len - 1; j > i; j--) {
			if (p[j - 1].size > p[j].size) {
				temp = p[j - 1];
				p[j - 1] = p[j];
				p[j] = temp;
			}
		}
	}
}

void Sortcost(Mark_tv* p, int& len) {
	Mark_tv temp;
	for (int i = 0; i < len; i++) {
		for (int j = len - 1; j > i; j--) {
			if (p[j - 1].cost > p[j].cost) {
				temp = p[j - 1];
				p[j - 1] = p[j];
				p[j] = temp;
			}
		}
	}
}

void Analyse(Mark_tv* p, int& len) {
	int max, i, j = 0;
	max = p[0].size;
	for (i = 1; i < len; i++) {
		if (max < p[i].size) {
			j = i;
			max = p[i].size;
		}
	}

	cout << endl << "Лучший телевизор "
		<< p[j].title << ", " << " стоимость  "
		<< p[j].cost << ", "
		<< p[j].size << " - " << " размер по диагонали " << endl << endl;
	system("pause");
}

void Write(Mark_tv* p, int& len)
{
	ofstream file;
	const char* OUT_FILE = "Out.txt";

	if (len == 0) {
		return;
	}

	file.open(OUT_FILE);
	for (int i = 0; i < len; i++) {
		file << p[i].title << ";" << p[i].country << ";" << p[i].cost << ";" << p[i].size << ";" << p[i].resolution << ";";
		if (p[i].tag == TYPE_INT) {
			file << p[i].misc.number << ";";
		}
		else {
			file << p[i].misc.note << ";";
		}
		file << endl;
	}
	file.close();
}

void Read(Mark_tv* p, int& len)
{
	char line[256];
	char delimiter[] = ";";
	char* token;
	int l;
	ifstream file;
	const char* OUT_FILE = "Out.txt";

	file.open(OUT_FILE);
	if (file.is_open()) {
		while (file.getline(line, 256)) {
			token = strtok(line, delimiter);
			l = 0;
			while (token != NULL) {
				switch (l) {
				case 0:
					strcpy_s(p[len].title, token);
					break;
				case 1:
					strcpy_s(p[len].country, token);
					break;
				case 2:
					p[len].cost = atoi(token);
					break;
				case 3:
					p[len].size = atoi(token);
					break;
				case 4:
					switch (atoi(token)) {
					case HIGHDEFENITION:
						p[len].resolution = HIGHDEFENITION;
						break;
					case FULLHD:
						p[len].resolution = FULLHD;
						break;
					case ULTRAHD4K:
						p[len].resolution = ULTRAHD4K;
						break;
					case ULTRAHD8K:
						p[len].resolution = ULTRAHD8K;
						break;
					}
					break;
				case 5:
					if (isdigit(token[0])) {
						p[len].misc.number = atoi(token);
						p[len].tag = TYPE_INT;
					}
					else {
						strcpy_s(p[len].misc.note, token);
						p[len].tag = TYPE_CHAR;
					}
					break;
				}
				l++;
				token = strtok(NULL, delimiter);
			}
			len++;
		}
	}
	file.close();
}
