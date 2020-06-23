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
  notes = malloc(sizeof(struct Note));

  parseText();

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
  printf("%d\t%c\t%s", note.line, (char) done, note.text);
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
   
    char *note = malloc(sizeof(char) * 40); //40 Character note text limit
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
          while ((c = fgetc(fp)) != EOF && c != '|') {
            note[i++] = (char) c;
          }
          note[i] = '\0';
          n.text = note;
          ungetc('|', fp); // Replace the | in the 
          n.line = line++;
          printf("REALLOC SIZE: %d\n", (int) sizeof(n) * line);

          
        
        }
    }


    

    fclose(fp);



 
 
 
  // printf("File open");
  // char ch;
  // notes = (struct Note*) malloc(sizeof(struct Note));
  // struct Note n;
  // int delinCount = 0; //Number of |s
  // printf("Looping");
  // char* string;
  // string = (char* )malloc(10000);
  // int i = 0;
  // while(ch = fgetc(fp) != EOF) {
  //   string[i++] = (char) ch;
  // }
  // string[i] = '\0';
  // printf("%s", string);

//   do {
//     ch = fgetc(fp);
//     if (ch == EOF) {
//       break;
//     }
//     if (ch == '|') {
//       delinCount++;
// //      continue;
//     }
//     if (delinCount%2 == 1) { //Second delineator before note
//       char ch1;
//       do {
//         ch1 = fgetc(fp);
//         printf("%s", n.text);
//         printf("%d", (int) sizeof(n.text));
//         // n.text = appendChar(n.text, ch1);
//         // strcat(n.text, ch1); //Add all characters until next delineator to note text
//       } while (ch1 != '|' && ch1 != EOF);
//       ungetc('|', fp); //Iterate back from the delineator to maintain count
//       int count = sizeof(notes) / sizeof(struct Note);
//       n.line = ++count;
//       realloc(notes, sizeof(struct Note) * (sizeof(notes) / sizeof(notes) + 2));
//       notes[count+2] = n; //Add note to notes Account for 0 index and line count diferenece
//       n.text = "\0"; //reset note
//       noteToString(n);
//     } else { //First delineator
//       if (ch == 'D') {
//         n.done = true;
//       }
//       else {
//         n.done = false;
//       }
//     }

//   } while (ch != EOF);

}

char* appendChar(char* string, char c) {
  printf("%c", c);
  printf("%s", string);
  int i = sizeof(string);
  printf("%d", i);
  i++;
  string = (char*) realloc(string, sizeof(char) * i);
  string[i] = c;
  printf("%c", string[i]);
  return string;
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
