# Notes-for-Terminal
A Simple Notes App for Terminal or Command Prompt.


To install:

Requirements: Clang or other C compiler

1. In the directory you place notes in initialize a blank notes.txt file or use the notes.txt file in the repository
 [touch notes.txt]
 
2. Compile notes.c
 [clang notes.c -o notes]

3. On linux run: [chmod a+x notes] to allow notes to be run as an executable

4. Finished

Usage:

  To add a note run:
   [./notes {note}]
   
   For all other commands:
  ./notes [command]
  
  Commands:
   -help:
      Provides help and usage instructions
   -del {index}
      Removes a note
      Example: ./notes -del 1
      
