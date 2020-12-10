#ifndef COMMAND_MODE
#define COMMAND_MODE

#include "normalMode.h"
#include "commandfunctions.h"
#include "additionalfunc.h"
#include "display_clear.h"


void clearSpace(){
	unsigned int term= wind.ws_row-2;
    //cy = 1;
    printf("%c[%d;%dH", 27, term, 1);
    printf("$Commandl Mode>>copy   move  delete_dir  delete_file  rename create_file  create_dir  goto  search");
    xpos=wind.ws_row+1;
    ypos=1;
    goto(xpos,ypos);
	printf("%c[2K", 27);
	//cout<<"command$>> ";
	cout<<":  ";
}

/*
void createTokens(string command){
	//cout<<command<<"command\n";

    parsed_tokens.clear();
    int i=0;
    while(i<command.length()){
        string substr="";
		while(command[i]!=' ' && i<command.length()){
            substr+=command[i++];
        }
		//cout<<substr;
        parsed_tokens.push_back(substr);
    }
	//cout<<parsed_tokens[0];
}*/
void executeCommands(string command){
    //createTokens(command);
	parsed_tokens.clear();
    int i=0;
    while(i<command.length()){
        string substr="";
		while(command[i]!=' ' && i<command.length()){
            substr+=command[i];
			i++;
        }
		i=i+1;
		//cout<<substr<<" ";
        parsed_tokens.push_back(substr);
    }
	string command_name;
	command_name=parsed_tokens[0];
	if(command_name == "copy")
	{
		//cout<<"copy starts";
		implementCopy();
	}
	else if(command_name == "move")
	{
		implementMove();
	}
	else if(command_name == "rename")
	{
		implementRename();
	}
	else if(command_name == "search")
	{
		implementSearch();
	}
	else if(command_name == "create_file")
	{
		implementCreateFile();

	}
	else if(command_name == "goto")
	{
		implementGoto();

	}
	else if(command_name == "create_dir")
	{
		implementCreateDir();
	}
	else if(command_name == "delete_file")
	{
		implementdeleteFile();
	}
	else if(command_name == "delete_dir")
	{
		implementdeleteDirectory();
		
	}
	else{ 
		Errormessage("Enter valid command");
		clearSpace();
	}
	//clear_screen();


}

void commandMode(){
    //clear_screen();
    clear_next_stack();
    clear_prev_stack();
    //tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
	clearSpace(); 

	
	
	char c;
	do{
		clearSpace();
		string command="";
		while((c=cin.get())!=10 && c!=27){
			if(c==127){
				clearSpace();
				if(command.length()<=1){
					command="";
				}
				else{
					command = command.substr(0,command.length()-1);
				}
				cout<<command;
			}
			else{
				command+=c;
				cout<<c;
			}
		}
		if(c==10) executeCommands(command);
	}while(c!=27);
	
	if(c==27) normal_mode();
}




#endif //ending command mode 