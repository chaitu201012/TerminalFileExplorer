#include <iostream>
#include <termios.h>
#define STDIN_FILENO 0
using namespace std;
int main()
{
// Black magic to prevent Linux from buffering keystrokes.
    while(1){
        struct termios t;
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag &= ~(ICANON|ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &t);

    // Once the buffering is turned off, the rest is simple.
        //cout << "Enter a character: ";
        char c,d,e;
        cin >> c;
        cin >> d;
        cin >> e;
        cout << "\nYour character was ";
    // Using 3 char type, Cause up down right left consist with 3 character
        if ((c==27)&&(d=91)) {
            if (e==65) { cout << "UP";}
            if (e==66) { cout << "DOWN";}
            if (e==67) { cout << "RIGHT";}
            if (e==68) { cout << "LEFT";}
        }
        if(e=='q'){
            t.c_lflag &=ICANON;
            t.c_lflag &= ECHO;
            tcsetattr(STDIN_FILENO, TCSANOW, &t);
            exit(1);
        }

    }
    return 0;
}
