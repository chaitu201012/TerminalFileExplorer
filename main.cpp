#include "headerfiles.h"
#include "glb_vars.h"
#include "normalMode.h"
#include "commandmode.h"
#include "commandfunctions.h"

stack<string> prev_stack;
stack<string> next_stack;
stack<string> parent_stack;
vector<string> contents;
vector<string> open_contents;
string root_path;
struct winsize wind;
struct termios noncan_mode,original;
unsigned int line,col;
unsigned int xpos=1,ypos=1;
int present_window=0;
string present_working_dir;
vector<string> parsed_tokens;
unsigned int search_count=0;
int main(){

    root_path=string(get_current_dir_name());
    present_working_dir=root_path;
    //prev_stack.push(root_path);
    normal_mode();
    //commandMode();

    return 0;
}
