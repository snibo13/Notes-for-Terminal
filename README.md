# Notes-for-Terminal
`Notes for Terminal` is a simple notes and to-do app built right into your terminal.
Command prompt/powershell functionality is a work in progress.
A Simple Notes App for Terminal or Command Prompt.


## Instalation

Requirements: Clang or other C compiler, git

```sh
git clone https://github.com/snibo13/Notes-for-Terminal.git
cd Notes-for-Terminal
clang notes.c -o notes
#For Linux
chmod a+x notes
```
Optional
Add Note-for-Terminal directory to System PATH
Additional Information: https://www.architectryan.com/2018/03/17/add-to-the-path-on-windows-10/


## Usage:

  Adding notes:
  ```sh
   ./notes {note}
   #Example
   ./notes "Hello, World"
   ```
   
   For all other commands:
  ```sh 
  ./notes [command]
  ```
  
  Commands:
   -help:
      Provides help and usage instructions
   -get:
     Lists out all notes
     ```sh
     ./notes -get
     ```
   -del {index}:
      Removes a note
      Example: ```./notes -del 1```
      
