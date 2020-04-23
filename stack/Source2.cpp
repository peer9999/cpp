#include <iostream>
#include <string>
using namespace std;

struct comp {
	string data;
	comp* next;
};

void s_push(comp**, string);
void s_del(comp**, string);
void s_print(comp*);
string s_top(comp*);

int main() {
	setlocale(0, "");
	//	string s1 = "<html><head><title>Пример веб - страницы</title></head><body><h1>Заголовок</h1><p>Первый абзац.</p><p>Второй абзац.</p></body></html>";
	string s1 = "<html><head><title>Пример веб - страницы</title></head><body><h1>Заголовок</h3><p>Первый абзац.</p><p>Второй абзац.</p></body></html>";
	string tag;
	string s_beg = "<";
	string s_end = ">";
	string slesh = "/";
	comp* top = NULL;

	size_t found_beg;
	size_t found_end;
	size_t found_slesh;

	do {
		found_beg = s1.find(s_beg);
		found_end = s1.find(s_end);

		tag = s1.substr(found_beg + 1, found_end - found_beg - 1);

		found_slesh = tag.find(slesh);
		if (found_slesh == 0) {
			tag = tag.substr(found_slesh + 1);
			if (s_top(top) == tag) {
				cout << "Right: " << s_top(top) << "--" << tag << endl;
				s_del(&top, tag);
			}
			else {
				cout << "Mistake: " << s_top(top) << "--" << tag << endl;
				s_del(&top, s_top(top));
			}
		}
		else {
			s_push(&top, tag);
		}

		s1 = s1.substr(found_end + 1);
		
	} while (s1 != "");
	system("pause");
	return 0;
}

void s_push(comp** top, string d) {
	comp* p;
	p = new comp();
	p->data = d;
	if (top == NULL) {
		*top = p;
	}
	else {
		p->next = *top;
		*top = p;
	}
}

void s_del(comp** top, string x) {
	comp* p = *top;
	comp* prev = NULL;
	if (p->data == x) {
		if (p == *top) {
			*top = p->next;
			free(p);
			p->data = "";
			p->next = NULL;
		}
		else {
			prev->next = p->next;
			free(p);
			p->data = "";
			p->next = NULL;
		}
	}
	else {
		prev = p;
		p = p->next;
	}

}

void s_print(comp* top) {
	comp* p = top;
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
}

string s_top(comp* top) {
	return top->data;
}
