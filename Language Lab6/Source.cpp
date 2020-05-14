#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#define HASHTAB_MUL 31
#define HASHTAB_SIZE 128

using namespace std;

struct listnode {
	char* key;
	int value;
	listnode* next;
};

union MISC {
	int inumber;
	char xnumber[6];
	float fnumber;
	char identificator[32];
};

enum TYPE {
	TYPE_INT = 1,
	TYPE_CHAR,
	TYPE_FLOAT,
	TYPE_XDIGIT,
	TYPE_COMM
};

struct lex {
	char lexema;
	char type;
	union MISC misc;
	enum TYPE tag;

};

unsigned int hashtab_hash(char*);					   
void hashtab_init(listnode**);					   
void hashtab_add(listnode**, char*, int);
int hashtab_lookup(listnode**, char*);   

int main() {
	listnode* hashtab[HASHTAB_SIZE];
	int i = 0;
	char buff[100];
	char* misc;
	int const max = 20;
	lex info[max] = {};

	ifstream file("text.txt");
	file.getline(buff, 100);
	file.close();
	cout << buff << endl;
	hashtab_init(hashtab);
	char s[] = "func_max";
	char* p = strtok(buff, " (),;");
	cout << "Lexems" << "    " << "Lexems type" << endl;
	while (p != NULL) {
		//cout << p << endl;
		misc = p;
		//cout << misc << endl;
		if (isalpha(misc[0])) {
			strcpy(info[i].misc.identificator, misc);
			info[i].tag = TYPE_CHAR;
		}
		else if (misc[0] == '0' && (misc[1] == 'x' || misc[1] == 'X')) {
			strcpy(info[i].misc.xnumber, misc);
			info[i].tag = TYPE_XDIGIT;
		}
		else {
			if (atof(misc) - abs(atoi(misc)) > 0) {
				info[i].misc.fnumber = atof(misc);
				info[i].tag = TYPE_FLOAT;
			}
			else {
				info[i].misc.inumber = atoi(misc);
				info[i].tag = TYPE_INT;
			}
		}
		if (misc[0] == '/' && misc[1] == '/') {
			strcpy(info[i].misc.identificator, misc);
			info[i].tag = TYPE_COMM;
		}

		if (info[i].tag == TYPE_CHAR) {
			cout << setw(15) << left << info[i].misc.identificator << setw(15) << left << "\t" << "Identificator";
		}
		else if (info[i].tag == TYPE_XDIGIT) {
			cout << setw(15) << left << info[i].misc.xnumber << setw(15) << left << "\t" << "Hex number";
		}
		else if (info[i].tag == TYPE_FLOAT) {
			cout << setw(15) << left << info[i].misc.fnumber << setw(15) << left << "\t" << "Float number";
		}
		else if (info[i].tag == TYPE_INT) {
			cout << setw(15) << left << info[i].misc.inumber << setw(15) << left << "\t" << "Int number";
		}
		else {
			cout << setw(15) << left << info[i].misc.identificator << setw(15) << left << "\t" << "Comment";
		}

		cout << endl;
		cout << info[i].tag << " " << endl;
		if (info[i].tag == 2) {
			hashtab_add(hashtab, misc, i);
		}
		i++;
		p = strtok(NULL, " (),;");
	}
	int count = hashtab_lookup(hashtab,s);
	cout << "Count: " << count << endl;
	return 0;
}

unsigned int hashtab_hash(char* key) {

	unsigned int h = 0;
	char* p;
	for (p = key; *p != '\0'; p++) {
		h = h * HASHTAB_MUL + (unsigned int)*p;
	}
	if (key == "function") {
		std::cout << h % HASHTAB_SIZE << std::endl;
	}
	return h % HASHTAB_SIZE;
}

void hashtab_init(listnode** hashtab) {
	int i;
	for (i = 0; i < HASHTAB_SIZE; i++) {
		hashtab[i] = NULL;
	}
}

void hashtab_add(listnode** hashtab, char* key, int value) {
	listnode* node;
	int index = hashtab_hash(key);
	node = new listnode;
	if (node != NULL) {
		node->key = key;
		node->value = value;
		node->next = hashtab[index];
		hashtab[index] = node;
	}
}

int hashtab_lookup(listnode** hashtab, char* key) {
	int index;
	int i = 0;
	listnode* node;
	index = hashtab_hash(key);
	for (node = hashtab[index]; node != NULL; node = node->next) {
		if (strcmp(node->key, key) == 0) {
			cout << "Node: " << node->key << " " << node->value << endl;
		}
		i++;
	}
	return i;
}

