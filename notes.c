#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Note {
	int line;
	bool done;
	char* text;
};

void printHelp();
int getNotes();
int writeNote(char* note);
int deleteNote(int line);
int writeNotes();
void markDone(int line);
void clearNotes();
bool nullFile(FILE* fp);
char* noteToString(struct Note note);



struct Note* notes;

int main(int argc, char** argv) {
	//Loop to present the notes
  if (argc != 2 && argc != 3) {
    printf("Improper usage\n Run 'notes -help' for more information");
    return 1;
  }

  //Checking for flags
	char flag = '-';
  char* parameter = argv[1];
  if(parameter[0] == flag) {
    if(strncmp(parameter,"-help",5) == 0) {
        printHelp();
		   	return 0;
   } else if(strncmp(parameter,"-get",4) == 0) {
     return getNotes();
   } else if(strncmp(parameter,"-del",2) == 0) {
     if(argc != 3) {
       printf("Improper usage\n Run 'notes -help' for more information");
       return 1;
     }
     int line = atoi(argv[2]);
     return deleteNote(line);
   } else if(strncmp(parameter, "-clear", 6 ) == 0) {
		 clearNotes();
		 return 1;
	 } else {
   printf("Command not found");
   return 2;
	 }
  }
  int r = writeNote(parameter); 
  return r;
}

void printHelp() {
  printf("Notes is a command-line based note taking system\n");
  printf("use it for to-do lists and quick notes\n");
  printf("To view the help screen run: \"notes -help\"\n");
  printf("To view all notes run: \"notes -get\"\n");
  printf("To add a note run: \"notes \"[note]\"\n");
  printf("To delete a note run: \"notes -del [line number]\"\n");
}

int getNotes() {
  FILE *fp;
  fp = fopen("./notes.txt","r+");
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
  FILE* fp;
  fp = fopen("./notes.txt","r+");
  if (nullFile(fp)) return -1;
  notes[line-1] = (struct Note) { 0 };
  return writeNotes();

}


int writeNotes() {
  FILE* fp;
  fp = fopen("./note.txt", "w+");
  if (nullFile(fp)) return -1;
  int noteCount = sizeof(notes)/sizeof( struct Note);
  for (int i = 0; i < noteCount; i++) {
    if ( memcmp(notes[i], (struct Note) { 0 }, sizeof(struct Note))) continue; //== for structs is memcmp
    fprintf(fp, "%s", noteToString(notes[i]));
  }
  return 0;
}

char* noteToString(struct Note note) {
  char* s;
  char done = (note.done) ? 'D' : 'N';
  sprintf(s, "%s|%s|%s", note.line, done, note.text);
}
//Deprecated
// int deleteNote(int line) {
//   FILE *fp;
//   FILE *temp;
//   temp = fopen("./temp.txt","w+");
//   fp = fopen("./notes.txt","r+");
//   if (nullFile(temp)) return;
//   if (nullFile(fp)) return;
//   char ch;
//   char* newFile;
//   int lineCount = 1;
//   do {
//     //Read the character to the ch variable
//     ch = fgetc(fp);
//     if(!isalpha(ch) && strncmp(&ch,"\n",1) != 0) {
//        continue;
//     }
//     if (lineCount != line) {
//       fprintf(temp, "%c", ch);
//     }
//     if(ch == '\n') {
//       lineCount++;
//     }
//   } while (ch != EOF);
//   fclose(fp);

//   rename("temp.txt","notes.txt");

//   return 0;  
// }

bool nullFile(FILE* fp) {
  if (fp == NULL) {
    printf("Error opening file");
    return true;
  }
  return false;
}

void parseText() {
  FILE* fp;
  fp = fopen("notes.txt","r");
  if (nullFile(fp)) return;

  char ch;
  struct Note n;
  int delinCount = 0;
  do {
    ch = fgetc(fp);
    if (ch == '|') {
      delinCount++;
      continue;
    }
    if (delinCount%2 == 0) { //Second delineator before note
      char ch1;
      do {
        ch1 = fgetc(fp);
        strcat(n.text, ch1); //Add all characters until next delineator to note
      } while (ch1 != '|' && ch1 != EOF);
      ungetc('|', fp); //Iterate back from the delineator to maintain count
      int count = sizeof(notes) / sizeof(struct Note);
      n.line = ++count;
      notes[count+2] = n; //Add note to notes Account for 0 index and line count diferenece
      n = (struct Note) { 0 }; //reset note

    } else {
      if (ch == 'D') {
        n.done = true;
      }
      else {
        n.done = false;
      }
    }

  } while (ch != EOF);

}

int writeNote(char* note) {
  /*
  Text structure "|" delineator
  [Number] 
  [D]one/[N]ot done
  [Note]
  */
  FILE* fp;
  fp = fopen("notes.txt","a+");
  if (nullFile(fp)) return -1;
  fprintf(fp, "%s|%s|", 'N', note);
  fclose(fp);
  return 0;
}

void clearNotes() {
	FILE* fp;
	fp = fopen("notes.txt", "w");
	if (fp == NULL) {
		printf("Error opening file");
		return;
	}
	fprintf(fp, "");
	fclose(fp);
	return;
}
