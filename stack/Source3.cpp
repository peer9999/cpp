#include <iostream>
#include <string>
using namespace std;

struct comp {
	string data;
	comp* prev;
};

void s_push(comp**, string);
void s_del(comp**);
void s_print(comp*);
string s_top(comp*);

int main() {
	setlocale(0, "");
//	string s1 = "<html><head><title>������ ��� - ��������</title></head><body><h1>���������</h1><p>������ �����.</p><p>������ �����.</p></body></html>";
	string s1;
	string tag;
	string s_beg = "<";
	string s_end = ">";
	string slesh = "/";
	comp* top = NULL;

	size_t found_beg;
	size_t found_end;
	size_t found_slesh;

	do {
		cout << "������� Html ��� ��� �������� ��������� �����(��� ������ ������� q): " << endl;
		getline(cin, s1);
		while (s1 != "q" && s1 != "") {
			found_beg   = s1.find(s_beg);
			found_end   = s1.find(s_end);
			tag         = s1.substr(found_beg + 1, found_end - found_beg - 1);
			found_slesh = tag.find(slesh);
			if (found_slesh == 0) {
				tag = tag.substr(found_slesh + 1);
				if (s_top(top) == tag) {
					cout << "���������: " << s_top(top) << "--" << tag << endl;
				}
				else {
					cout << "�����������: " << s_top(top) << "--" << tag << endl;
				}
				s_del(&top);
			}
			else {
				s_push(&top, tag);
			}
			s1 = s1.substr(found_end + 1);
//			cout << s1 << endl;
		}
	} while (s1 != "q");

//	s_print(top);
//	cout << endl << s_top(top)<<endl;
	return 0;
}

void s_push(comp** top, string d) {
	comp* p;
	p = new comp();
	p->data = d;
	p->prev = NULL;
	if (top == NULL) {
		*top = p;
	}
	else {
		p->prev = *top;
		*top = p;
	}
}

void s_del(comp** top) {
	comp* p = *top;
	*top = p->prev;
}

void s_print(comp* top) {
	comp* p = top;
	while (p != NULL) {
		cout << p->data << " ";
		p = p->prev;
	}
}

string s_top(comp* top) {
	return top->data;
}
