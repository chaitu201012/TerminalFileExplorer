#ifndef GLOBALVARS
#define GLOBALVARS
#include "headerfiles.h"


//All the global variables will be declared in this header file and
//file guards should be used before including in the cpp files.

extern stack<string> prev_stack;
extern stack<string> next_stack;
extern stack<string> parent_stack;
extern string root_path;
extern string present_working_dir;
extern vector<string> contents; // stores the contents of opendir for sorted printing
extern vector<string> open_contents;// to store openable files like txt and directories 
extern struct winsize wind;
extern struct termios noncan_mode,original;
extern unsigned int line,col;
extern unsigned int xpos,ypos;
extern int present_window;
extern vector<string> parsed_tokens;
extern unsigned int search_count;

#endif //GLOBALVARS
