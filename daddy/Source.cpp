#include <iostream>
#include <cstring>

using namespace std;
int main()
{
	int const max = 100;
	char* str_result = new char[max + 1];
	char x[max];
	char str2[max];
	char str3[max];
	cout << "Vvedite stroku : " << endl;
	cin.get(x, max);
	cout << "Vvedite slovo posle kotogo nado vstavit : " << endl;
	cin >> str2;
	cout << "Vvedite slovo kotogo nado vstavit : " << endl;
	cin >> str3;

	char* pch = strstr(x,str2);
	cout << pch << endl;

	char* p = strtok(x," ");	 	  //��������� ������ �� �������
	while (p != NULL) {
		strcat(str_result, p);            //���������� � str_result - p
		strcat(str_result, " "); 	  //���������� ������� � str_result
		if (strcmp(p, str2) == 0) {       //��������� ������ p �� ������� str2
			strcat(str_result, str3); //���������� � str_result ������ str3
			strcat(str_result, " ");  //���������� � str_result �������
		}
		p = strtok(NULL," "); 		 //���� ������ � ������
	}
	cout << str_result << endl;
	return 0;
}

void changeSymbol(char *str)
{
      char result[3][100]; 
	  int i = 0;
	  while (*str != '\0') //пока значение ячейки не равно символу конца строки
      {
            if (*str == ' ') *str = 'O';
            else strcat(result[i],*str);
 
            str++; //на каждой итерации цикла, указатель смещается на одну ячейку
      }
}