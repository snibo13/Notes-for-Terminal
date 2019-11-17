#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


void printHelp();
int getNotes();
int writeNote(char* note);
int deleteNote(int line);

int main(int argc, char** argv) {
  if (argc != 2 && argc != 3) {
    printf("Improper usage\n Run 'notes -help' for more information");
    return 1;
  }

  char flag = '-';
  char* parameter = argv[1];
  if(parameter[0] == flag) {
    if(strncmp(parameter,"-help",5) == 0) {
        printHelp();
	return 0;
   }
   if(strncmp(parameter,"-get",4) == 0) {
     return getNotes();
   }
   if(strncmp(parameter,"-del",2) == 0) {
     if(argc != 3) {
       printf("Improper usage\n Run 'notes -help' for more information");
       return 1;
     }
     int line = atoi(argv[2]);
     return deleteNote(line);
   }
   printf("Command not found");
   return 2;
  }
  int r = writeNote(parameter); 
  return r;
}

void printHelp() {
  printf("Notes is a command-line based note taking system\n");
  printf("use it for to-do lists and quick notes\n");
  printf("To view the help screen run: \"notes -help\"\n");
  printf("To view all notes run: \"notes -get\"\n");
  printf("To add a note run: \"notes \"[note]\"\n ");
  printf("To delete a note run: \"notes -del [line number]\"\n");
}

int getNotes() {
  FILE *fp;
  fp = fopen("notes.txt","r+");
  if (fp == NULL) {
    printf("Error reading file");
    return 3;
  }
  char ch;
  int lineCount = 1;
  printf("%d:",lineCount);
  do {
    //Read the character to the ch variable
    ch = fgetc(fp);
    putchar(ch);
    if(ch == '\n') {
      lineCount++;
      printf("%d:",lineCount);
    }
  } while (ch != EOF);
  fclose(fp);
  return 0;  
}

int deleteNote(int line) {
  FILE *fp;
  FILE *temp;
  temp = fopen("temp.txt","w+");
  fp = fopen("notes.txt","r+");
  if (fp == NULL) {
    printf("Error reading file");
    return 3;
  }
  char ch;
  char* newFile;
  int lineCount = 1;
  do {
    //Read the character to the ch variable
    ch = fgetc(fp);
    if(!isalpha(ch) && strncmp(&ch,"\n",1) != 0) {
       continue;
    }
    if (lineCount != line) {
      fprintf(temp, "%c", ch);
    }
    if(ch == '\n') {
      lineCount++;
    }
  } while (ch != EOF);
  fclose(fp);

  rename("temp.txt","notes.txt");

  return 0;  
}

int writeNote(char* note) {
  FILE* fp;
  fp = fopen("notes.txt","a+");
  if(fp == NULL) {
    printf("Error opening file");
    return 4;
  }
  fprintf(fp, "%s\n", note);
  fclose(fp);
  return 0;
}
