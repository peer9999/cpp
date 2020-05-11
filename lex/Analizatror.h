#pragma once
#include <iostream>
using namespace std;
#include "String.h"
#include "Interpretator.h"
class Automate{
	istream& in;
	ostream& out;
	char ch;
	int (Automate::* state)();
	CString str;
	Interpretator Z;
public:
	static int Line;
	Automate(istream& i, ostream& o): in(i), out(o),Z(o){
		state=&Automate::qnull;
		str="";
	}
	int qnull(){
		switch(ch){
			case '+':
				state=&Automate::qnull;
				out<<0<<"\n";
				Z.AddLexem(0,Line);
				return 0;
			case '=':
				state=&Automate::qnull;
				out<<6<<"\n";
				Z.AddLexem(6,Line);
				return 0;
			case '\"':
				state=&Automate::qconst;
				str="";
				return 0;
			case '<':
				state=&Automate::qmenshe;
				return 0;
			case '>':
				state=&Automate::qbolshe;
				return 0;
			case 'x':
				throw "X ne ispolsuetsja otdelno";
			case '!':
				state=&Automate::qwarning;
				return 0;
			case '.':
				state=&Automate::qpoint;
				return 0;
			case -1:
				return -1;
			case '\n':
				Line++;
				state=&Automate::qnull;
				return 0;
			case '\t':
				state=&Automate::qnull;
				return 0;
			case ' ':
				state=&Automate::qnull;
				return 0;
			case '?':
				state=&Automate::qnull;
				out<<13<<"\n";
				Z.AddLexem(13,Line);
				return 0;
			case 'i':
				state=&Automate::qi;
				return 0;
			case 'j':
				state=&Automate::qj;
				return 0;
			case 'm':
				throw "M - nedopustimii symbol";
			case 'p':
				throw "P - nedopustimii symbol";
			case '-':
				state=&Automate::qminus;
				return 0;
			default :
				if(isdigit(ch))
					throw "Digit - nedopustimii symbol";
				else
					throw "Nedopustimii symbol";
		}
	}
	int qconst(){
		switch(ch){
			case '+':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case '=':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case '\"':
				state=&Automate::qnull;
				out<<5<<"("<<str<<")\n";
				Z.AddLexem(5,Line,str);
				return 0;
			case '<':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case '>':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case 'x':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case '!':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case '.':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case -1:
				throw "Neogidannii conez file";
			case '\n':
				Line++;
				state=&Automate::qconst;
				str+ch;
				return 0;
			case '\t':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case ' ':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case '?':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case 'i':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case 'j':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case 'm':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case 'p':
				state=&Automate::qconst;
				str+ch;
				return 0;
			case '-':
				state=&Automate::qconst;
				str+ch;
				return 0;
			default :
				state=&Automate::qconst;
				str+ch;
				return 0;
		}
	}
	int qmenshe(){
		switch(ch){
			case '+':
				state=&Automate::qnull;
				out<<8<<"\n"<<0<<"\n";
				Z.AddLexem(8,Line);
				Z.AddLexem(0,Line);
				return 0;
			case '=':
				state=&Automate::qnull;
				out<<9<<"\n";
				Z.AddLexem(9,Line);
				return 0;
			case '\"':
				state=&Automate::qconst;
				str="";
				out<<8<<"\n";
				Z.AddLexem(8,Line);
				return 0;
			case '<':
				state=&Automate::qmenshe;
				out<<8<<"\n";
				Z.AddLexem(8,Line);
				return 0;
			case '>':
				state=&Automate::qbolshe;
				out<<8<<"\n";
				Z.AddLexem(8,Line);
				return 0;
			case 'x':
				state=&Automate::qmenshex;
				return 0;
			case '!':
				state=&Automate::qwarning;
				out<<8<<"\n";
				Z.AddLexem(8,Line);
				return 0;
			case '.':
				state=&Automate::qpoint;
				out<<8<<"\n";
				Z.AddLexem(8,Line);
				return 0;
			case -1:
				out<<8<<"\n";
				Z.AddLexem(8,Line);
				return -1;
			case '\n':
				Line++;
				state=&Automate::qnull;
				out<<8<<"\n";
				Z.AddLexem(8,Line);
				return 0;
			case '\t':
				state=&Automate::qnull;
				out<<8<<"\n";
				Z.AddLexem(8,Line);
				return 0;
			case ' ':
				state=&Automate::qnull;
				out<<8<<"\n";
				Z.AddLexem(8,Line);
				return 0;
			case '?':
				state=&Automate::qnull;
				out<<8<<"\n";
				Z.AddLexem(8,Line);
				out<<13<<"\n";
				Z.AddLexem(13,Line);
				return 0;
			case 'i':
				state=&Automate::qi;
				out<<8<<"\n";
				Z.AddLexem(8,Line);
				return 0;
			case 'j':
				state=&Automate::qj;
				out<<8<<"\n";
				Z.AddLexem(8,Line);
				return 0;
			case 'm':
				throw "M - nedopustimii symbol";
			case 'p':
				throw "P - nedopustimii symbol";
			case '-':
				state=&Automate::qnull;
				out<<4<<"\n";
				Z.AddLexem(4,Line);
				return 0;
			default :
				if(isdigit(ch))
					throw "Digit - nedopustimii symbol";
				else
					throw "Nedopustimii symbol";
		}
	}
	int qbolshe(){
		switch(ch){
			case '+':
				state=&Automate::qnull;
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				out<<0<<"\n";
				Z.AddLexem(0,Line);
				return 0;
			case '=':
				state=&Automate::qnull;
				out<<11<<"\n";
				Z.AddLexem(11,Line);
				return 0;
			case '\"':
				state=&Automate::qconst;
				str="";
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				return 0;
			case '<':
				state=&Automate::qmenshe;
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				return 0;
			case '>':
				state=&Automate::qbolshe;
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				return 0;
			case 'x':
				state=&Automate::qbolshex;
				return 0;
			case '!':
				state=&Automate::qwarning;
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				return 0;
			case '.':
				state=&Automate::qpoint;
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				return 0;
			case -1:
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				return -1;
			case '\n':
				Line++;
				state=&Automate::qnull;
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				return 0;
			case '\t':
				state=&Automate::qnull;
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				return 0;
			case ' ':
				state=&Automate::qnull;
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				return 0;
			case '?':
				state=&Automate::qnull;
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				out<<13<<"\n";
				Z.AddLexem(13,Line);
				return 0;
			case 'i':
				state=&Automate::qi;
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				return 0;
			case 'j':
				state=&Automate::qj;
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				return 0;
			case 'm':
				throw "M - nedopustimii symbol";
			case 'p':
				throw "P - nedopustimii symbol";
			case '-':
				state=&Automate::qminus;
				out<<10<<"\n";
				Z.AddLexem(10,Line);
				return 0;
			default :
				if(isdigit(ch))
					throw "Digit - nedopustimii symbol";
				else
					throw "Nedopustimii symbol";
		}
	}

	int qwarning(){
		switch(ch){
			case '+':
				state=&Automate::qnull;
				out<<12<<"\n";
				Z.AddLexem(12,Line);
				out<<0<<"\n";
				Z.AddLexem(0,Line);
				return 0;
			case '=':
				state=&Automate::qnull;
				out<<7<<"\n";
				Z.AddLexem(7,Line);
				return 0;
			case '\"':
				state=&Automate::qconst;
				str="";
				out<<12<<"\n";
				Z.AddLexem(12,Line);
				return 0;
			case '<':
				state=&Automate::qmenshe;
				out<<12<<"\n";
				Z.AddLexem(12,Line);
				return 0;
			case '>':
				state=&Automate::qbolshe;
				out<<12<<"\n";
				Z.AddLexem(12,Line);
				return 0;
			case 'x':
				throw "X - nedopustimii symbol";
			case '!':
				state=&Automate::qwarning;
				out<<12<<"\n";
				Z.AddLexem(12,Line);
				return 0;
			case '.':
				state=&Automate::qnull;
				out<<1<<"\n";
				Z.AddLexem(1,Line);
				return 0;
			case -1:
				out<<12<<"\n";
				Z.AddLexem(12,Line);
				return -1;
			case '\n':
				Line++;
				state=&Automate::qnull;
				out<<12<<"\n";
				Z.AddLexem(12,Line);
				return 0;
			case '\t':
				state=&Automate::qnull;
				out<<12<<"\n";
				Z.AddLexem(12,Line);
				return 0;
			case ' ':
				state=&Automate::qnull;
				out<<12<<"\n";
				Z.AddLexem(12,Line);
				return 0;
			case '?':
				state=&Automate::qnull;
				out<<12<<"\n";
				Z.AddLexem(12,Line);
				out<<13<<"\n";
				Z.AddLexem(13,Line);
				return 0;
			case 'i':
				state=&Automate::qi;
				out<<12<<"\n";
				Z.AddLexem(12,Line);
				return 0;
			case 'j':
				state=&Automate::qj;
				out<<12<<"\n";
				Z.AddLexem(12,Line);
				return 0;
			case 'm':
				throw "M - nedopustimii symbol";
			case 'p':
				throw "P - nedopustimii symbol";
			case '-':
				state=&Automate::qminus;
				out<<12<<"\n";
				Z.AddLexem(12,Line);
				return 0;
			default :
				if(isdigit(ch))
					throw "Digit - nedopustimii symbol";
				else
					throw "Nedopustimii symbol";
		}
	}


	int qpoint(){
		switch(ch){
			case '+':
			case '=':
			case '\"':
			case '<':
			case '>':
			case 'x':
				throw "Ojidaetsja - !";
			case '!':
				state=&Automate::qnull;
				out<<2<<"\n";
				Z.AddLexem(2,Line);
				return 0;
			case '.':
			case -1:
			case '\n':
			case '\t':
			case ' ':
			case '?':
			case 'i':
			case 'j':
			case 'm':
			case 'p':
			case '-':
			default :
				throw "Ojidaetsja - !";
		}
	}
	int qminus(){
		switch(ch){
			case '+':
			case '=':
			case '\"':
			case '<':
				throw "Ojidaetsja - >";
			case '>':
				state=&Automate::qnull;
				out<<3<<"\n";
				Z.AddLexem(3,Line);
				return 0;
			case 'x':
			case '!':
			case '.':
			case -1:
			case '\n':
			case '\t':
			case ' ':
			case '?':
			case 'i':
			case 'j':
			case 'm':
			case 'p':
			case '-':
			default :
				throw "Ojidaetsja - >";
		}
	}
	int qi(){
		switch(ch){
			case '+':
			case '=':
			case '\"':
			case '<':
			case '>':
			case 'x':
			case '!':
			case '.':
			case -1:
			case '\n':
			case '\t':
			case ' ':
			case '?':
			case 'i':
				throw "Ojidaetsja - J";
			case 'j':
				state=&Automate::qij;
				return 0;
			case 'm':
			case 'p':
			case '-':
			default :
				throw "Ojidaetsja - J";
		}
	}
	int qj(){
		switch(ch){
			case '+':
			case '=':
			case '\"':
			case '<':
			case '>':
			case 'x':
			case '!':
			case '.':
			case -1:
			case '\n':
			case '\t':
			case ' ':
			case '?':
			case 'i':
			case 'j':
				throw "Ojidaetsja - M";
			case 'm':
				state=&Automate::qjm;
				return 0;
			case 'p':
			case '-':
			default :
				throw "Ojidaetsja - M";
		}
	}
	int qmenshex(){
		switch(ch){
			case '+':
			case '=':
			case '\"':
			case '<':
			case '>':
			case 'x':
			case '!':
			case '.':
			case -1:
			case '\n':
			case '\t':
			case ' ':
			case '?':
			case 'i':
			case 'j':
			case 'm':
			case 'p':
			case '-':
				throw "Ojidaetsja - Digit";
			default :
				if(isdigit(ch)){
					state=&Automate::qmenshexdigit;
					str="";
					str+ch;
					return 0;
				}
				else
					throw "Ojidaetsja - Digit";
		}
	}
	int qbolshex(){
		switch(ch){
			case '+':
			case '=':
			case '\"':
			case '<':
			case '>':
			case 'x':
			case '!':
			case '.':
			case -1:
			case '\n':
			case '\t':
			case ' ':
			case '?':
			case 'i':
			case 'j':
			case 'm':
			case 'p':
			case '-':
				throw "Ojidaetsja - Digit";
			default :
				if(isdigit(ch)){
					state=&Automate::qbolshexdigit;
					str="";
					str+ch;
					return 0;
				}
				else
					throw "Ojidaetsja - Digit";
		}
	}
	int qij(){
		switch(ch){
			case '+':
			case '=':
			case '\"':
			case '<':
			case '>':
			case 'x':
			case '!':
			case '.':
			case -1:
			case '\n':
			case '\t':
			case ' ':
			case '?':
			case 'i':
			case 'j':
			case 'm':
			case 'p':
			case '-':
				throw "Ojidaetsja - Digit";
			default :
				if(isdigit(ch)){
					state=&Automate::qijdigit;
					str="";
					str+ch;
					return 0;
				}
				else
					throw "Ojidaetsja - Digit";
		}
	}
	int qjm(){
		switch(ch){
			case '+':
			case '=':
			case '\"':
			case '<':
			case '>':
			case 'x':
			case '!':
			case '.':
			case -1:
			case '\n':
			case '\t':
			case ' ':
			case '?':
			case 'i':
			case 'j':
			case 'm':
				throw "Ojidaetsja - P";
			case 'p':
				state=&Automate::qjmp;
				return 0;
			case '-':
			default :
				throw "Ojidaetsja - P";
		}
	}
	int qjmp(){
		switch(ch){
			case '+':
			case '=':
			case '\"':
			case '<':
			case '>':
			case 'x':
			case '!':
			case '.':
			case -1:
			case '\n':
			case '\t':
			case ' ':
			case '?':
			case 'i':
			case 'j':
			case 'm':
			case 'p':
			case '-':
				throw "Ojidaetsja - Digit";
			default :
				if(isdigit(ch)){
					state=&Automate::qjmpdigit;
					str="";
					str+ch;
					return 0;
				}
				else
					throw "Ojidaetsja - P";
		}
	}
	int qmenshexdigit(){
		switch(ch){
			case '+':
				state=&Automate::qnull;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				out<<0<<"\n";
				Z.AddLexem(0,Line);
				return 0;
			case '=':
				state=&Automate::qnull;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				out<<6<<"\n";
				Z.AddLexem(6,Line);
				return 0;
			case '\"':
				state=&Automate::qconst;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				str="";
				return 0;
			case '<':
				state=&Automate::qmenshe;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				return 0;
			case '>':
				state=&Automate::qbolshe;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				return 0;
			case 'x':
				throw "X ne ispolsuetsja otdelno";
			case '!':
				state=&Automate::qwarning;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				return 0;
			case '.':
				state=&Automate::qpoint;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				return 0;
			case -1:
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				return -1;
			case '\n':
				Line++;
				state=&Automate::qnull;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				return 0;
			case '\t':
				state=&Automate::qnull;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				return 0;
			case ' ':
				state=&Automate::qnull;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				return 0;
			case '?':
				state=&Automate::qnull;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				out<<13<<"\n";
				Z.AddLexem(13,Line);
				return 0;
			case 'i':
				state=&Automate::qi;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				return 0;
			case 'j':
				state=&Automate::qj;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				return 0;
			case 'm':
				throw "M - nedopustimii symbol";
			case 'p':
				throw "P - nedopustimii symbol";
			case '-':
				state=&Automate::qminus;
				out<<17<<"("<<str<<")\n";
				Z.AddLexem(17,Line,str);
				return 0;
			default :
				if(isdigit(ch)){
					state=&Automate::qmenshexdigit;
					str+ch;
					return 0;
				}
				else
					throw "Nedopustimii symbol";
		}
	}
	int qbolshexdigit(){
		switch(ch){
			case '+':
				state=&Automate::qnull;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				out<<0<<"\n";
				Z.AddLexem(0,Line);
				return 0;
			case '=':
				state=&Automate::qnull;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				out<<6<<"\n";
				Z.AddLexem(6,Line);
				return 0;
			case '\"':
				state=&Automate::qconst;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				str="";
				return 0;
			case '<':
				state=&Automate::qmenshe;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				return 0;
			case '>':
				state=&Automate::qbolshe;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				return 0;
			case 'x':
				throw "X ne ispolsuetsja otdelno";
			case '!':
				state=&Automate::qwarning;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				return 0;
			case '.':
				state=&Automate::qpoint;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				return 0;
			case -1:
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				return -1;
			case '\n':
				Line++;
				state=&Automate::qnull;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				return 0;
			case '\t':
				state=&Automate::qnull;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				return 0;
			case ' ':
				state=&Automate::qnull;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				return 0;
			case '?':
				state=&Automate::qnull;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				out<<13<<"\n";
				Z.AddLexem(13,Line);
				return 0;
			case 'i':
				state=&Automate::qi;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				return 0;
			case 'j':
				state=&Automate::qj;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				return 0;
			case 'm':
				throw "M - nedopustimii symbol";
			case 'p':
				throw "P - nedopustimii symbol";
			case '-':
				state=&Automate::qminus;
				out<<16<<"("<<str<<")\n";
				Z.AddLexem(16,Line,str);
				return 0;
			default :
				if(isdigit(ch)){
					state=&Automate::qbolshexdigit;
					str+ch;
					return 0;
				}
				else
					throw "Nedopustimii symbol";
		}
	}
	int qijdigit(){
		switch(ch){
			case '+':
				state=&Automate::qnull;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				out<<0<<"\n";
				Z.AddLexem(0,Line);
				return 0;
			case '=':
				state=&Automate::qnull;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				out<<6<<"\n";
				Z.AddLexem(6,Line);
				return 0;
			case '\"':
				state=&Automate::qconst;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				str="";
				return 0;
			case '<':
				state=&Automate::qmenshe;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				return 0;
			case '>':
				state=&Automate::qbolshe;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				return 0;
			case 'x':
				throw "X ne ispolsuetsja otdelno";
			case '!':
				state=&Automate::qwarning;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				return 0;
			case '.':
				state=&Automate::qpoint;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				return 0;
			case -1:
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				return -1;
			case '\n':
				Line++;
				state=&Automate::qnull;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				return 0;
			case '\t':
				state=&Automate::qnull;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				return 0;
			case ' ':
				state=&Automate::qnull;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				return 0;
			case '?':
				state=&Automate::qnull;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				out<<13<<"\n";
				Z.AddLexem(13,Line);
				return 0;
			case 'i':
				state=&Automate::qi;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				return 0;
			case 'j':
				state=&Automate::qj;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				return 0;
			case 'm':
				throw "M - nedopustimii symbol";
			case 'p':
				throw "P - nedopustimii symbol";
			case '-':
				state=&Automate::qminus;
				out<<15<<"("<<str<<")\n";
				Z.AddLexem(15,Line,str);
				return 0;
			default :
				if(isdigit(ch)){
					state=&Automate::qijdigit;
					str+ch;
					return 0;
				}
				else
					throw "Nedopustimii symbol";
		}
	}
	int qjmpdigit(){
		switch(ch){
			case '+':
				state=&Automate::qnull;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				out<<0<<"\n";
				Z.AddLexem(0,Line);
				return 0;
			case '=':
				state=&Automate::qnull;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				out<<6<<"\n";
				Z.AddLexem(6,Line);
				return 0;
			case '\"':
				state=&Automate::qconst;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				str="";
				return 0;
			case '<':
				state=&Automate::qmenshe;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				return 0;
			case '>':
				state=&Automate::qbolshe;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				return 0;
			case 'x':
				throw "X ne ispolsuetsja otdelno";
			case '!':
				state=&Automate::qwarning;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				return 0;
			case '.':
				state=&Automate::qpoint;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				return 0;
			case -1:
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				return -1;
			case '\n':
				Line++;
				state=&Automate::qnull;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				return 0;
			case '\t':
				state=&Automate::qnull;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				return 0;
			case ' ':
				state=&Automate::qnull;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				return 0;
			case '?':
				state=&Automate::qnull;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				out<<13<<"\n";
				Z.AddLexem(13,Line);
				return 0;
			case 'i':
				state=&Automate::qi;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				return 0;
			case 'j':
				state=&Automate::qj;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				return 0;
			case 'm':
				throw "M - nedopustimii symbol";
			case 'p':
				throw "P - nedopustimii symbol";
			case '-':
				state=&Automate::qminus;
				out<<14<<"("<<str<<")\n";
				Z.AddLexem(14,Line,str);
				return 0;
			default :
				if(isdigit(ch)){
					state=&Automate::qjmpdigit;
					str+ch;
					return 0;
				}
				else
					throw "Nedopustimii symbol";
		}
	}
	void Analisis(){
		int make=0;
		do{
			ch=in.get();
			make=(this->*state)();				
		}while(make!=-1);
	}
	void RunInterpritator(){
		Z.RunInterpretator();
	}
};
