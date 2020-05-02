#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <iostream.h>

class Data
 {
  FILE  *ptr;
  char  inputfile[30];
  char  compfile[30];
  char  inflafile[30];
  char  chars[256];
  char  tree[3000];
  int   number[256];
  int   bits[256][15];
  int   length[256];
  int   noofchars;
  int   origsize;
  int   compsize;
  float probs[256];
  public :
    Data();
    void readFileName(int);
    void getProbs();
    void sortProbs();
    void genCodes();
    void storeData();
    void formProbs();
    void createTree();
    void inflate();
    void handleError(char *);
    void swap(int &, int &);
    void swap(float &, float &);
    void swap(char &, char &);
 };

Data::Data()
 {
  int i, j;
  noofchars = origsize = 0;
  for (i = 0; i < 256; i++)
   {
    chars[i] = '\0';
    length[i] = number[i] = probs[i] = 0;
    for (j = 0; j < 15; j++)
     bits[i][j] = 0;
   }
  for (i = 0; i < 3000; i++)
   tree[i] = 1;
 }

void Data::readFileName(int ch)
 {
  if (ch == 1)
   {
    cout << "Enter name of file to be compressed : ";
    cin >> inputfile;
    cout << "Enter name of compressed file : ";
    cin >> compfile;
   }
   else
    {
     cout << "Enter name of file to be inflated : ";
     cin >> compfile;
     cout << "Enter name of inflated file : ";
     cin >> inflafile;
    }
 }

void Data::getProbs()
 {
  int charcount = 0;
  char temp;
  ptr = fopen(inputfile, "rb");
  if (ptr == NULL) handleError(inputfile);
  cout << "\nCompressing...";
  while (!feof(ptr))             // reading input file and counting
   {                             // occurences of each character.
    temp = getc(ptr);
    chars[temp] = temp;
    number[temp]++;
    charcount++;
    origsize++;
   }
  fclose(ptr);
  for (int i = 0; i < 256; i++)     // calculating frequency of
   {                                // each character.
    if (chars[i] == NULL) continue;
    chars[noofchars] = chars[i];
    number[noofchars] = number[i];
    probs[noofchars] = float(number[i]) / charcount;
    noofchars++;
   }
 }

void Data::sortProbs()   // sorts characters in descending
 {                       // order of probability.
  int i, j;
  for (i = 0; i < (noofchars - 1); i++)
   for (j = 0; j < (noofchars - 1); j++)
     if (probs[j] < probs[j + 1])
       {
	swap(chars[j], chars[j + 1]);
	swap(probs[j], probs[j + 1]);
	swap(number[j], number[j + 1]);
       }
 }

void Data::genCodes()        // generates the bit code for
 {                           // each character in the file.
  float sum, temp = 0.5;
  int i, j, k, groups = 1, index1[256], index2[256];
  for (i = 0; i < 256; i++)
   index1[i] = index2[i] = 0;
  index1[1] = index2[1] = noofchars;
  while (groups != noofchars)
   {
    k = 1;
    for (j = 0; j < groups; j++)
     {
      if ((index1[j + 1] - index1[j]) == 1)
       {
	index2[k] = index1[j + 1];
	k++;
	continue;
       }
      i = index1[j];
      sum = 0;
      while ((sum < temp) && (i < index1[j + 1]))
       {
	sum += probs[i];
	i++;
       }
      index2[k] = i;            // marking position of newly
      if (i >= index1[j + 1])   // created group.
       {                        // if no split point was found,
	k++;                    // we skip this group.
	continue;
       }
      for (i = index1[j]; i < index2[k]; i++)  // append bit '0'
       {                                       // to codes in upper
	bits[i][length[i]] = 0;                // half of group.
	length[i]++;
       }
      for (i = index2[k]; i < index1[j + 1]; i++)  // append bit '1'
       {                                           // to codes in
	bits[i][length[i]] = 1;                    // lower half of
	length[i]++;                               // group.
       }
      k++;
      index2[k] = index1[j + 1];  // store position of next group.
      k++;
     }
    temp /= 2;
    for (i = 0; i < k; i++)       // refresh main index array.
     index1[i] = index2[i];
    groups = k - 1;               // calculate no. of groups.
   }
  for (i = 0; i < (noofchars - 1); i++)
   for (j = 0; j < (noofchars - 1); j++)
    if (length[j] > length[j + 1])
     {
      swap(length[j], length[j + 1]);
      for (k = 0; k < length[j + 1]; k++)
       swap(bits[j][k], bits[j + 1][k]);
     }
 }

void Data::storeData()        // stores data in compressed file
 {                            // in the form of bit codes.
  int i, j, k = 0, l = 0;
  int m = 0, sum = 0, tmp[1000];
  char buf[32767], temp;
  for (i = 0; i < 32767; i++)
   buf[i] = NULL;
  ptr = fopen(inputfile, "rb");
  if (ptr == NULL) handleError(inputfile);
  while (!feof(ptr))
   {
    temp = getc(ptr);
    i = 0;
    while ((temp != chars[i]) && (i < noofchars)) i++;
    if (i == noofchars) break;
    for (j = 0; j < length[i]; j++)
     {
      buf[l] <<= 1;
      k++;
      if (bits[i][j]) buf[l]++;
      if (k == 8)
       {
	k = 0;
	if (buf[l] == 0)
	 {
	  m++;
	  tmp[m] = l + 1 - sum;
	  sum = l + 1;
	 }
	l++;
       }
     }
   }
  fclose(ptr);
  if (k < 8)
   buf[l] <<= (8 - k);
  if (buf[l] == 0)
   {
    m++;
    tmp[m] = l + 1 - sum;
   }
  tmp[0] = m;

// Write compressed data into file.

  ptr = fopen(compfile, "wb");
  fwrite(&noofchars, 2, 1, ptr);
  compsize  = 2;
  for (i = 0; i < noofchars; i++)
    putc(chars[i], ptr);
  compsize += noofchars;
  for (i = 0; i < noofchars; i++)
    fwrite(&number[i], 2, 1, ptr);
  compsize += (2 * noofchars);
  fwrite(&l, 2, 1, ptr);
  fwrite(&k, 2, 1, ptr);
  compsize += 4;
  for (i = 0; i <= m; i++)
    fwrite(&tmp[i], 2, 1, ptr);
  compsize += (2 * (m + 1));
  for (i = 0; i <= l; i++)
   if (buf[i] != 0)
     {
      putc(buf[i], ptr);
      compsize++;
     }
  fclose(ptr);
  cout << "Done\n\n";
  cout << "Compression : " << (100 - (int)(100 * (float)compsize / origsize)) << "%\n";
 }

void Data::formProbs()
 {
  int i;
  for (i = 0; i < noofchars; i++)
    origsize += number[i];
  for (i = 0; i < noofchars; i++)
    {
     probs[i] = float(number[i]) / origsize;
    }
 }

void Data::createTree()   // creates a tree of characters
 {                        // on basis of bit codes for
  int i, j, k;            // efficient inflation of file.
  for (i = 0; i < noofchars; i++)
   {
    k = 1;
    for (j = 0; j < (length[i] - 1); j++)
     {
      if (bits[i][j] == 0) k *= 2;
       else k = (2 * k) + 1;
     }
    if (bits[i][j] == 1)
     {
      tree[2 * k + 1] = chars[i];
      tree[4 * k + 2] = 0;
      tree[4 * k + 3] = 0;
     }
     else
      {
       tree[2 * k] = chars[i];
       tree[4 * k] = 0;
       tree[4 * k + 1] = 0;
      }
   }
 }

void Data::inflate()               // inflates the file.
 {
  char buf[32767], bitcode, temp;
  int i, j, k, l, n = 0, r = 1;
  int m = 1, sum = 0, tmp[1000], seg;
  ptr = fopen(compfile, "rb");
  if (ptr == NULL) handleError(compfile);
  cout << "\nInflating...\n";
  fread(&noofchars, 2, 1, ptr);
  for (i = 0; i < noofchars; i++)
    {
     chars[i] = getc(ptr);
    }
  for (i = 0; i < noofchars; i++)
    {
     fread(&number[i], 2, 1, ptr);
    }
  formProbs();
  sortProbs();
  genCodes();
  createTree();
  fread(&l, 2, 1, ptr);
  fread(&k, 2, 1, ptr);
  fread(&tmp[0], 2, 1, ptr);
  for (i = 1; i <= tmp[0]; i++)
    fread(&tmp[i], 2, 1, ptr);
  i = 0;
  while (l != -1)
   {
    l--;
    n++;
    if (((sum + tmp[m]) == n) && (m <= tmp[0]))
     {
      bitcode = 0;
      sum += tmp[m];
      m++;
     }
     else
      bitcode = getc(ptr);
    j = 0;
    while (j < 8)
     {
      temp = bitcode;
      temp &= 128;
      if (temp == 0)
       {
	if (tree[2 * r] == 0)
	 {
	  buf[i] = tree[r];
	  i++;
	  r = 2;
	 }
	 else r *= 2;
       }
       else
	{
	 if (tree[2 * r + 1] == 0)
	  {
	   buf[i] = tree[r];
	   i++;
	   r = 3;
	  }
	  else r = (2 * r) + 1;
	}
      j++;
      if ((j == k + 1) && (l == -1)) break;
      bitcode <<= 1;
     }
   }
  fclose(ptr);
  buf[i] = '\0';
  ptr = fopen(inflafile, "wb");
  fwrite(buf, strlen(buf), 1, ptr);
  fclose(ptr);
 }

void Data::handleError(char a[30])
 {
  cout << '\n' << "File " << a << " not found! Aborting program.";
  exit(1);
 }

void Data::swap(int &a, int &b)
 {
  int temp;
  temp = a;
  a = b;
  b = temp;
 }

void Data::swap(float &a, float &b)
 {
  float temp;
  temp = a;
  a = b;
  b = temp;
 }

void Data::swap(char &a, char &b)
 {
  char temp;
  temp = a;
  a = b;
  b = temp;
 }

main(int argc, char* argv[])
 {
  Data D;
  clrscr();
  cout << "VinZip v1.0\n";
  cout << "===========\n\n";
  if (!strcmpi(argv[1], "c"))
    {
     D.readFileName(1);
     D.getProbs();
     D.sortProbs();
     D.genCodes();
     D.storeData();
    }
   else if (!strcmpi(argv[1], "i"))
     {
      D.readFileName(0);
      D.inflate();
     }
    else
      {
       cout << "Usage : vinzip c|i\n";
       cout << "        'c' is used for compression\n";
       cout << "        'i' is used for inflation\n";
      }
  return 0;
 }
