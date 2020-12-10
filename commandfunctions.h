#ifndef COMMAND_FUNC
#define COMMAND_FUNC

#include "glb_vars.h"
#include "commandmode.h"
#include "additionalfunc.h"



void implementSearch(){
	search_count=0;
	if(parsed_tokens.size()!=2){
        Errormessage("Not a valid command");
		return;
    }
	string searchable=parsed_tokens[1];
	searchInDir(searchable,present_working_dir);
	printf("\033[H\033[J");
	printf("%c[%d;%dH", 27, 1, 1);
	if(search_count>0) cout<<"True-File/Folder Exists\n";
	else cout<<"File/Folder Not Present\n";
	return;
}
void implementGoto(){
	if(parsed_tokens.size()!=2){
		Errormessage("Not a valid command");
		return;
	}
	prev_stack.push(present_working_dir);
	const char *homeDir;
	if ((homeDir = getenv("HOME")) == NULL) {
		homeDir = getpwuid(getuid())->pw_dir;
	}
	present_working_dir=parsed_tokens[1];
	content_listing();


}
void implementCreateFile(){

	if(parsed_tokens.size()<3){
        Errormessage("Not a valid command");
		return;
    }
	else{
		string destination=createAbsPath(parsed_tokens[parsed_tokens.size()-1]);
		for(int i=1;i<parsed_tokens.size()-1;i++)
		{
			string name = parsed_tokens[i];
			//string destination=createAbsPath(string(get_current_dir_name()));
			destination =destination + "/" + name;
			if(open(destination.c_str(),O_RDONLY | O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )==-1) {
				Errormessage(destination);
			}
		}
	} 
	

}
void implementCreateDir(){
	if(parsed_tokens.size()<2){
        Errormessage("Not a valid command");
		return;
    }
	else{
			
		for(int i=1;i<parsed_tokens.size()-1;i++)
		{
			string name = parsed_tokens[i];
			string destination=createAbsPath(parsed_tokens[parsed_tokens.size()-1]);
			destination =destination + "/" + name;
			if(mkdir(destination.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)==-1) Errormessage("Error makedir:");
		}
	} 

}

void implementRename(){
	if(parsed_tokens.size()!=3){
        Errormessage("Not a valid command");
		return;
    }
	    //cout<<"enteres rename";
		string givenname=parsed_tokens[1];
		string renamedAs=parsed_tokens[2];
		//char oldname[]=givenname.c_str();
		//char newname=
		rename(givenname.c_str(),renamedAs.c_str());
}
void implementCopy(){

    if(parsed_tokens.size()<3){
        Errormessage("Not a valid command");
		return;
    }
	else{
			
		for(int i=1;i<parsed_tokens.size()-1;i++)
		{
            
			string fullpath = createAbsPath(parsed_tokens[i]);
			string name = fileName(fullpath);
			string destination=createAbsPath(parsed_tokens[parsed_tokens.size()-1]);
			destination =destination + "/" + name;
			//cout<<"\ndespath in copy : "<<des<<endl;
			if(isDirectory(fullpath))
			{
				copyDir(fullpath,destination);
			}
			else
			{
				copyFile(fullpath,destination);
			}
		}
	}
}

void implementMove(){
	if(parsed_tokens.size()<3){
        Errormessage("Not a valid command");
		return;
    }
	else{
			
		for(int i=1;i<parsed_tokens.size()-1;i++)
		{
            
			string fullpath = createAbsPath(parsed_tokens[i]);
			string name = fileName(fullpath);
			string destination=createAbsPath(parsed_tokens[parsed_tokens.size()-1]);
			destination =destination + "/" + name;
			//cout<<"\ndespath in copy : "<<des<<endl;
			if(isDirectory(fullpath))
			{
				copyDir(fullpath,destination);
				deleteDirectory(fullpath);


			}
			else
			{
				copyFile(fullpath,destination);
				deleteFile(fullpath);
			}
		}
	}

}
void implementdeleteDirectory(){
	if(parsed_tokens.size()<2){
        Errormessage("Not a valid command");
		return;
    }
	else{
			
		for(int i=1;i<parsed_tokens.size();i++)
		{
            
			string fullpath = createAbsPath(parsed_tokens[i]);
			//string name = fileName(fullpath);
			//string destination=parsed_tokens[parsed_tokens.size()-1];
			//destination =destination + "/" + name;
			//cout<<"\ndespath in copy : "<<des<<endl;
				deleteDirectory(fullpath);
		}
	}

}
void implementdeleteFile(){
	if(parsed_tokens.size()<2){
        Errormessage("Not a valid command");
		return;
    }
	else{
			
		for(int i=1;i<parsed_tokens.size();i++)
		{
            
			string fullpath = createAbsPath(parsed_tokens[i]);
			//string name = fileName(fullpath);
			//string destination=parsed_tokens[parsed_tokens.size()-1];
			//destination =destination + "/" + name;
			//cout<<"\ndespath in copy : "<<des<<endl;
			deleteFile(fullpath);
		}
	}
	
}

#endif //COMMAND_FUNC
