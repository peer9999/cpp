#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <dir.h>
#include <stdio.h>
#include <process.h>
#include <dos.h>
#include <io.h>

struct checker
       {char identifier[255];
        int handle;
        char type[255];} checkup[255], buf, Rb;
FILE *f, *t; char c; int nst, ns, n, x; unsigned int count, p;
char lexem[16], s[16]; char a[]={':','!','<','>'}, Path[MAXPATH];
char b[]={'+','*',',','-','/',';','='}; FILE *f1, *h; char lexemsa[7];

void C (); void H (); void F (); void G (); void D ();  void _put (); void _type ();

void monitor ()
{getcwd(Path, MAXPATH);strcat(Path, "\\Programma.txt");
if ((f=fopen(Path, "rt"))==NULL)
{cprintf("Fuck! Some mistake occured...File: Programma.txt\n\r");getch ();return;}
if ((t=fopen("Temp.txt", "w"))==NULL)
{cprintf("Fuck! Some mistake occured...File\n\r");getch ();return ;}
while ((c=fgetc(f))!=EOF)
{if (isalpha(c)) fputc(tolower(c),t); else if (isdigit(c)) fputc(c,t);
 else if((c=='(')||(c==')')) {fputc('\n',t);fputc(c,t);fputc('\n',t);}
 else if (strchr(a,c)) {fputc('\n',t);fputc(c,t);c=fgetc(f);
    if (c=='=') {fputc(c,t);fputc('\n',t);} else {fputc('\n',t);fputc(c,t);}}
 else if (strchr(b,c)) {fputc('\n',t);fputc(c,t);fputc('\n\r',t);}
 else if (isspace(c)) fputc('\n',t);
 else {textcolor(12);cprintf("Error! Unexpected symbol..\n\r");getch ();
 return;}}fclose(t); fclose(f);}

int search (char P[MAXPATH])
{FILE *f;
 int string; string=0; getcwd(Path, MAXPATH);strcat(Path,P);
 if ((f=fopen(Path, "rt"))==NULL)
  {cprintf("Fuck! Some mistake occured...File\n\r");getch ();return 0;}
 while(!feof(f)) {fscanf(f,"%s",s); string++;
  if (!(strcmp(lexem,s))) return string;} fclose(f);}

void printak (int j , int nn)
{FILE *w;
 getcwd(Path, MAXPATH); strcat(Path, "\\Result.txt");
 if ((w=fopen(Path, "a+"))==NULL)
  {cprintf("Fuck! Some mistake occured with one of Files...Result.txt\n\r"); getch (); return ;}
    else {fprintf(w,"(%i,%i)\n",j,nn);fclose(w);}}

int Kaspersky ()
{int j, nc, nd;j=0;nc=0;nd=0;
 if (strlen(lexem)>16) return 0; else
  {while ((lexem[j]!='\0')&&(lexem[j]!='\n'))
    {if (isalpha(lexem[j])) nc++; if (isdigit(lexem[j])) nd++; j++;}
   if (nc<=10) if (nd<=6) return 1; else return 0;}}

void reset (char *P)
{getcwd(Path, MAXPATH); strcat(Path, P); int err =remove(Path);}

void respectla (char *P)
{FILE *ff1;
getcwd(Path, MAXPATH);strcat(Path,P);
if ((ff1=fopen(Path, "a+"))==NULL)
{cprintf("Fuck! Some mistake occured...File\n\r");getch ();return ;}
fprintf(ff1,"%s\n",lexem);fclose(ff1);}

int lexical ()
{int j,i; j=0;i=0;while (lexem[j]!='\0')
{if(isalnum(lexem[j])) {i++;j++;} else {i=0;break;}} return i;}

int mathcad ()
 {int j, i; j=0; i=0;
  while (lexem[j]!='\0') {if (isdigit(lexem[j])) {i++;j++;}
  else {i=0;break;}} return i;}

void scaner ()
{getcwd(Path, MAXPATH); strcat(Path, "\\Temp.txt");
if ((t=fopen(Path, "rt"))==NULL)
{cprintf("Fuck! Some mistake occured...File: Temp.txt\n\r");getch ();return;}
while (!feof(t)){fscanf(t,"%s\n",&lexem); if (Kaspersky ())
{if (x=lexical()) {if (nst=search("\\Reserved words.txt")) printak(1,nst) ;
else {if (nst=search("\\Identifier.txt")) printak(4,nst);
else {if ((x=mathcad())) {respectla("\\Constant.txt"); printak(3,ns++);}
else {respectla("\\Identifier.txt");printak(4,++n);}}}}
else if (nst=search("\\Marks.txt")) printak(2,nst);}else {textcolor(12);
cprintf("Stopped! So, You enter too many symbols in one lexem:))");getch ();
return;}} fclose(f);fclose(t);}

void respect (char k[255])
 {textcolor (12); cprintf("Stopped analyses -  %s \n\r",k);getch ();return;}

void _error (char *i)
 {textcolor (12); cprintf ("Error! %s \n\r",i); getch (); return;}

void _preview ()
 {FILE *f; int string; string=0;
 if ((f=fopen("Identifier.txt", "rt"))==NULL)
  {cprintf("Fuck! Some mistake occured...File\n\r");getch ();return;}
 while(!feof(f)) {fscanf(f,"%s",s); string++;}
 if(count!=string-1) {cprintf(" %i not equal %i ", count, string-1); _error(" Count not equal String! \n\r");} fclose(f);}

void _notice ()
 {unsigned int i=1;
  for (;;) {if(i>count) break;
    if(strcmp(checkup[i].identifier,lexemsa)) i++; else {checkup[i].handle=2;
     strcpy(buf.type,checkup[i].type); cprintf("Buf - %s \n\r", buf.type); break;}}}
     
void Arithmetic ()
 {if(strstr(lexemsa,"(4,")!=NULL) // Ідентифікатор
   { // cprintf("%s\n\r",lexemsa);
    _notice(); fscanf(f,"%s\n",lexemsa);
    if(!strcmp(lexemsa,"(2,1)")) // Якщо lexem це ':='
     {fscanf(f1,"%s\n",lexemsa);

    // Ідентифікатор := true|false;
      if((!strcmp(lexemsa,"(1,7)"))||(!strcmp(lexemsa,"(1,8)")))
       {if(!strcmp(buf.type,"(1,4)")) {fscanf(f1,"%s\n",lexemsa);
         if (strcmp(lexemsa,"(2,13)")) respect("it must be marks");
        while(!strcmp(lexemsa,"(2,13)")) {if(feof(f1)) break;
          C(); if(strcmp(lexemsa,"(2,13)")) respect("Error with ';' in true/false blok");}
        } else _error (" - Type incompatible\n\r");}

      // ( Певний арифметичний вираз );
     else {if(!strcmp(lexemsa,"(2,17)")) {fscanf(f1,"%s\n",lexemsa);
      F(); if(!strcmp(lexemsa,"(2,16)")) fscanf(f1,"%s\n",lexemsa);
        else respect("Expected ')' !");} else F();
      if (strcmp(lexemsa,"(2,13)")) respect("it must be marks");
      while(!strcmp(lexemsa,"(2,13)")) {if(feof(f1)||(!strcmp(lexemsa,"(1,5)"))) break;
       else {fscanf(f1,"%s\n",lexemsa);Arithmetic();}}}}
      else respect("Some error in arithmetic blok near ':=' ");}}

void _try ()
 {int i; for (i=count-p;i<count;i++) {strcpy(checkup[i].type,lexemsa);checkup[count].handle=1;}}

void _put ()
 {if ((h=fopen("Table.txt","a+"))==NULL)
   {textcolor(12); cprintf("Can't open File!"); getch (); return;}
  strcat(checkup[count].identifier,lexemsa); checkup[count].handle=0;
  strcat(checkup[count].type,"*");
   // cprintf("_put %s \n\r",checkup[count].identifier);
  fprintf(h,"%s",checkup[count].identifier); fprintf(h,"%s",checkup[count].handle); fclose(h);}

void _type ()
 {if ((h=fopen("Table.txt","a+"))==NULL)
   {textcolor(12);cprintf("Can't open File!");getch ();return;}
  strcpy(checkup[count].type,lexemsa); fprintf(h,"%s",checkup[count].type);
  if(p>0) if(!strcmp(checkup[count-1].type,"*")) _try (); fclose(h);}

void B ()
 {if (strstr(lexemsa,"(4,")!=NULL) {p=0; count++;  _put ();
   fscanf(f1,"%s\n",lexemsa);} else respect("On begin Must be identifier!");
  while (!strcmp(lexemsa,"(2,12)"))
   {fscanf(f1,"%s\n",lexemsa);
    if (strstr(lexemsa,"(4,")!=NULL) {p++; count++; _put (); fscanf(f1,"%s\n",lexemsa);}
      else respect("After ',' expect identifier only! ");}
  if (!strcmp(lexemsa,"(2,14)")) {fscanf(f1,"%s\n",lexemsa);}
     else respect(":");
  if(!strcmp(lexemsa,"(1,3)") || (!strcmp(lexemsa,"(1,2)")) || (!strcmp(lexemsa,"(1,4)")))
    { _type (); fscanf(f1,"%s\n",lexemsa);} else respect("Type must be defined");
  if (strcmp(lexemsa,"(2,13)")) respect("Must be ';' ");}

void A ()
 {cprintf("A(): %s\n\r",lexemsa);
  if (!strcmp(lexemsa,"(1,1)")) fscanf(f1,"%s\n",lexemsa); else respect ("A");B ();
  while (!strcmp(lexemsa,"(2,13)"))
   {fscanf(f1,"%s\n",lexemsa); if (!strcmp(lexemsa,"(1,12)")) break; B();}
   _preview();}

void _finito ()
 {textcolor (11);
  for (int i=1;i<=count;i++)
   if((checkup[i].handle==0)||(checkup[i].handle==1))
     {cprintf("Identifier %s not using!\n\r", checkup[i].identifier); getch();}
  for (int i1=1;i1<=count;i1++)
   for (int j1=count;j1>i1;j1--)
    if(!strcmp(checkup[i1].identifier,checkup[j1].identifier))
     {cprintf("%s already descript!",checkup[i1].identifier); getch(); return;}}

void Start ()
 {A(); C();}

void Table ()
 {int handle;
 handle=creatnew("Table.txt",0);
  if (handle==-1) cprintf("Table.txt is already exists!\n\r");
   else cprintf("Table.txt has successfully created!\n\r");}

void main (void)
{textcolor(333);nst=0; ns=0;n=0; count=0;
 getcwd(Path, MAXPATH);strcat(Path, "\\Identifier.txt");
 if ((f=fopen(Path, "w+"))==NULL)
  {cprintf("Fuck! Some mistake occured...File\n\r");getch ();return;}
 reset("\\Result.txt");reset("\\Constant.txt");
 monitor();scaner();//reset("\\Temp.txt");
 if ((f1=fopen("Result.txt", "rt"))==NULL)
   {cprintf("Fuck! Some mistake occured...File\n\r");getch ();return;}
 //execl(Path,"One",NULL); perror("Path");
 reset("\\Table.txt"); Table(); if (!feof(f1)) fscanf(f1,"%s\n",lexemsa);Start();
 _finito(); getch ();
}

void H () // Ідентифікатор або константа
 {if(strstr(lexemsa,"(3,")!=NULL) fscanf(f1,"%s\n",lexemsa);
   else if(strstr(lexemsa,"(4,")!=NULL)
    { _notice(); fscanf(f1,"%s\n", lexemsa);}
       else respect("It must be Identifier!");}

void G () // Після '*' або '\' або 'and'
 {if(!strcmp(lexemsa,"(2,17)")) {fscanf(f1,"%s\n",lexemsa);H();
   while ((!strcmp(lexemsa,"(2,8)"))||(!strcmp(lexemsa,"(2,11)"))||(!strcmp(lexemsa,"(1,11)")))
     {fscanf(f1,"%s\n",lexemsa); H();} if(!strcmp(lexemsa,"(2,16)")) fscanf(f1,"%s\n",lexemsa);
       else respect("Expected ')' !");} else {H();
        while ((!strcmp(lexemsa,"(2,8)"))||(!strcmp(lexemsa,"(2,11)"))||(!strcmp(lexemsa,"(1,11)")))
         {fscanf(f1,"%s\n",lexemsa); H();}}}

void F () // Після '+' або '-' або 'or'
 {if(!strcmp(lexemsa,"(2,17)")) {fscanf(f1,"%s\n",lexemsa); G(); strcpy(Rb.type, buf.type);
   cprintf(" %s %s \n\r", Rb.type, buf.type); if(!strcmp(Rb.type,"(1,4)")) _error("Can't be operator!\n\r");
   while ((!strcmp(lexemsa,"(2,5)"))||(!strcmp(lexemsa,"(2,15)"))||(!strcmp(lexemsa,"(1,9)")))
    {fscanf(f1,"%s\n",lexemsa); G(); if(!strcmp(Rb.type,"(1,4)")) _error("Can't be operator!\n\r");
     if(strcmp(Rb.type, buf.type)) _error("Different types in expressions!\n\r");}
   if(!strcmp(lexemsa,"(2,16)")) fscanf(f1,"%s\n",lexemsa); else respect("Expected ')' !");}
    else {G();strcpy(Rb.type, buf.type);cprintf(" %s %s \n\r", Rb.type, buf.type);
  while ((!strcmp(lexemsa,"(2,5)"))||(!strcmp(lexemsa,"(2,15)"))||(!strcmp(lexemsa,"(1,9)")))
   {fscanf(f1,"%s\n",lexemsa);G();if(strcmp(Rb.type, buf.type)) _error("Different types in expressions!\n\r");}}}

void D () // Після '>=' або '<=' або '!=' або '<' або '>' або '='
 {if(!strcmp(lexemsa,"(2,17)")) {fscanf(f1,"%s\n",lexemsa);F();strcpy(Rb.type, buf.type);
  cprintf(" %s %s \n\r", Rb.type, buf.type); if(!strcmp(Rb.type,"(1,4)")) _error("Can't be operator!\n\r");
  if(!strcmp(buf.type,"(1,4)")) _error("Can't be operator!\n\r");
  if(!strcmp(lexemsa,"(2,16)")) fscanf(f1,"%s\n",lexemsa); else respect("Expected ')' !");}
  else F(); strcpy(Rb.type, buf.type); cprintf(" %s %s \n\r", Rb.type, buf.type);
  if(!strcmp(Rb.type,"(1,4)")) _error("Can't be operator!\n\r");
  if ((!strcmp(lexemsa,"(2,2)"))||(!strcmp(lexemsa,"(2,3)"))||(!strcmp(lexemsa,"(2,4)"))||(!strcmp(lexem,"(2,6)"))||(!strcmp(lexemsa,"(2,7)"))||(!strcmp(lexemsa,"(2,10)")))
   {fscanf(f1,"%s\n",lexemsa);F();if(!strcmp(Rb.type,"(1,4)")) _error("Can't be operator!\n\r");
     if(strcmp(Rb.type, buf.type)) _error("Different types in expressions!\n\r");} else respect ("D");}

void C ()
 {fscanf(f1,"%s\n",lexemsa);
  if(strstr(lexemsa,"(4,")!=NULL)
   { // _notice();
    Arithmetic(); if(feof(f1)) {cprintf(" <=There is End Of File=> \n\r");return;}
       else {if(!strcmp(lexemsa,"(1,5)")) {fscanf(f1,"%s\n",lexemsa);
        if(!strcmp(lexemsa,"(2,17)")) fscanf(f1,"%s\n",lexemsa); else respect("It must be marks '('");
        D(); if(strcmp(lexemsa,"(2,16)")) respect("it must be marks ')'");
        fscanf(f1,"%s\n",lexemsa); if(!strcmp(lexemsa,"(1,6)")) C(); else respect("it must be Then");}
         else respect("Error with If!");}}
     else
      {if(!strcmp(lexemsa,"(1,5)")) // Якщо lexem це 'if'
      {fscanf(f1,"%s\n",lexemsa); D(); // Якщо lexem це 'then'
       if(!strcmp(lexemsa,"(1,6)")) C(); else respect("it must be then");} else respect("it must be If");}}
