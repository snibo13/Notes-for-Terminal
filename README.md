# Notes-for-Terminal
`Notes for Terminal` is a simple notes and to-do app built right into your terminal.
Command prompt/powershell functionality is a work in progress.
A Simple Notes App for Terminal or Command Prompt.

### For the time being, notes is only accesible within the directory it is installed. I am working on a solution but if you have a multi-tab terminal, having notes open in one and code in another is recommended.

## Instalation

Requirements: Clang or other C compiler, git

```sh
git clone https://github.com/snibo13/Notes-for-Terminal.git
cd Notes-for-Terminal
clang notes.c -o notes
#For Linux
chmod a+x notes
```


## Usage

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
      
