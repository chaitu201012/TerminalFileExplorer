#ifndef HEADERFILES
#define HEADERFILES

#include <bits/stdc++.h>
//#include<conio.h>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <iomanip>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define  goto(xpos,ypos) printf("%c[%d;%dH",27,(xpos), (ypos))
using namespace std;

/* we will define all the functions to implement our functionality.*/

void normal_mode();
void content_listing();
bool isDirectory(string path);
void commandMode();
void implementCopy();
bool isDirectory(string path);
string fileName(string fullpath);
void clear_screen();
void Errormessage(string msg);
string createAbsPath(string substr);
void copyDir(string fullpath,string destination);
void copyFile(string fullpath,string destination);
void clear_screen();
string createAbsPath(string substr);


#endif //HEADERFILES
