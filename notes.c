#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct Note {
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
int parseText();
bool nullFile(FILE* fp);
char* appendChar(char* string, char c);
void noteToString(struct Note note);



struct Note* notes;


int main(void) {
  return getNotes();
}


// int main(int argc, char** argv) {
// 	//Loop to present the notes
//   if (argc != 2 && argc != 3) {
//     printf("Improper usage\n Run 'notes -help' for more information");
//     return 1;
//   }

//   //Checking for flags
// 	char flag = '-';
//   char* parameter = argv[1];
//   if(parameter[0] == flag) {
//     if(strncmp(parameter,"-help",5) == 0) {
//         printHelp();
// 		   	return 0;
//    } else if(strncmp(parameter,"-get",4) == 0) {
//      return getNotes();
//    } else if(strncmp(parameter,"-del",2) == 0) {
//      if(argc != 3) {
//        printf("Improper usage\n Run 'notes -help' for more information");
//        return 1;
//      }
//      int line = atoi(argv[2]);
//      return deleteNote(line);
//    } else if(strncmp(parameter, "-clear", 6 ) == 0) {
// 		 clearNotes();
// 		 return 1;
// 	 } else {
//    printf("Command not found");
//    return 2;
// 	 }
//   }
//   int r = writeNote(parameter);
//   return r;
// }

void printHelp() {
  printf("Notes is a command-line based note taking system\n");
  printf("use it for to-do lists and quick notes\n");
  printf("To view the help screen run: \"notes -help\"\n");
  printf("To view all notes run: \"notes -get\"\n");
  printf("To add a note run: \"notes \"[note]\"\n");
  printf("To delete a note run: \"notes -del [line number]\"\n");
}


int getNotes()
{
  int lines = parseText();
  for (int i = 1; i < lines; i++) {
    // noteToString(notes[i]);
  }

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
     noteToString(notes[i]);
  }
  return 0;
}

void noteToString(struct Note note) {
  char done = (note.done) ? 'D' : 'N';
  printf("%d\t%c\t%s\n", note.line, (char) done, note.text);
}

bool nullFile(FILE* fp) {
  if (fp == NULL) {
    printf("Error opening file");
    return true;
  }
  return false;
}
/*
* Converts the text in notes to an array of notes
* In text notes are :
* Done | Note
*/
int parseText() {
  FILE *fp;
  fp = fopen("./notes.txt","r+");
  if (fp == NULL) {
    printf("Error reading file");
    return 3;
  }
  
    
    struct Note n;
   
    char* note = (char *) malloc(sizeof(char) * 40); //40 Character note text limit
    int c;
    int delinCount = 0;
    int line = 1;



    while ((c = fgetc(fp)) != EOF) {
      if (c == 'N' || c == 'D') {
        n.done = (c == 'D' ? true: false);
      } else if (c == '|') {
          delinCount++;
      }
        if (delinCount % 2 == 1) { //Delineator between completion and note
          int i = 0;
          free(note);
          note = (char*) malloc(sizeof(char) * 40);
          while ((c = fgetc(fp)) != EOF && c != '|') {
            note[i++] = (char) c;
          }
          n.text = note;
          ungetc('|', fp); // Replace the | in the 
          n.line = line++;

          noteToString(n);
          
          n = (struct Note) {0};
        }
    }
    fclose(fp);
    return line;

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
  fprintf(fp, "%s|%s|", "N", note); //[N]ot done | Text
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
