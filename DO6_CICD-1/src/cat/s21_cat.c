#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#include "CatFlags.h"

typedef struct {
  bool NumberNonBlank;     //-b
  bool markEndl;           // -e
  bool numberAll;          // -n
  bool squeeze;            // -s
  bool tab;                //-t
  bool printNonPrintable;  //-v
} Flags;

void CatFile(FILE *file, Flags flags, const char *table[static 256],
             int *lineno, char *r, int *FileCount);
void Cat(int argc, char *argv[], Flags flags, const char *table[static 256]);
void Cat(int argc, char *argv[], Flags flags, const char *table[static 256]);
Flags CatReadFlags(int argc, char *argv[]);
//функция считывания флагов
int main(int argc, char *argv[]) {
  Flags flags = CatReadFlags(argc, argv);
  const char *table[256];
  CatSetTable(table);
  if (flags.markEndl) {
    CatSetEndel(table);
  }
  if (flags.tab) {
    CatSetTab(table);
  }
  if (flags.printNonPrintable) {
    CarSetNonPrintable(table);
  }
  Cat(argc, argv, flags, table);
}
Flags CatReadFlags(int argc, char *argv[]) {
  struct option longOptions[] = {{"number-nonblank", 0, NULL, 'b'},
                                 {"number", 0, NULL, 'n'},
                                 {"squeeze-blank", 0, NULL, 's'},
                                 {NULL, 0, NULL, 0}};
  int currentFlag = getopt_long(argc, argv, "bevEnstT", longOptions, NULL);
  Flags flags = {false, false, false, false, false, false};
  for (; currentFlag != -1;
       currentFlag = getopt_long(argc, argv, "bevEnstT", longOptions, NULL)) {
    switch (currentFlag) {
      case 'b':
        flags.NumberNonBlank = true;
        break;
      case 'e':
        flags.markEndl = true;
        flags.printNonPrintable = true;
        break;
      case 'v':
        flags.printNonPrintable = true;
        break;
      case 'E':
        flags.markEndl = true;
        break;
      case 'n':
        flags.numberAll = true;
        break;
      case 's':
        flags.squeeze = true;
        break;
      case 't':
        flags.tab = true;
        flags.printNonPrintable = true;
        break;
      case 'T':
        flags.tab = true;
        break;
    }
  }
  return flags;
}

void CatFile(FILE *file, Flags flags, const char *table[static 256],
             int *lineno, char *r, int *FileCount) {
  int c = 0;  // хранить текушии символы
  int last;
  bool squeeze = false;  // для обработки других аргументов
  last = '\n';
  int StringCount = 0;
  // char buffer[256];
  if ((flags.markEndl && flags.tab && flags.printNonPrintable &&
       flags.squeeze) ||
      (flags.squeeze || flags.tab || flags.markEndl ||
       flags.printNonPrintable)) {
    while (fread(&c, 1, 1, file) > 0) {
      if (last == '\n') {
        if (flags.squeeze && c == '\n') {
          if (squeeze) continue;
          squeeze = true;
        } else {
          squeeze = false;
        }
      }
      if (!*table[c])
        printf("%c", '\0');
      else if (flags.squeeze && *FileCount > 1) {
        printf("\n");
        printf("%s", table[c]);
        *FileCount = 0;
      } else
        printf("%s", table[c]);
      last = c;
    }
  }
  char ch;
  if (flags.numberAll || flags.NumberNonBlank || flags.printNonPrintable) {
    while ((ch = fgetc(file)) != EOF) {
      StringCount++;
      if ((flags.NumberNonBlank)) {
        if ((ch != '\n' && *r == '\n')) {
          printf("%6i\t", ++*lineno);
          printf("%c", ch);
        } else {
          printf("%c", ch);
        }
      } else if (flags.numberAll) {
        if ((*r == '\n')) {
          printf("%6i\t", ++*lineno);
          printf("%c", ch);
        } else {
          printf("%c", ch);
        }
      }
      *r = ch;
    }
  } else {
    while ((ch = fgetc(file)) != EOF) {
      printf("%c", ch);
    }
  }
}

void Cat(int argc, char *argv[], Flags flags, const char *table[static 256]) {
  int lineno = 0;
  int FileCout = 0;
  char r = '\n';
  for (char **filename = &argv[1], **end = &argv[argc]; filename != end;
       ++filename) {
    if (**filename == '-') continue;
    FILE *file = fopen(*filename, "rb");
    if (errno) {
      fprintf(stderr, "%s", argv[0]);
      perror(*filename);
      continue;
    }
    FileCout++;
    CatFile(file, flags, table, &lineno, &r, &FileCout);
    fclose(file);
  }
}
