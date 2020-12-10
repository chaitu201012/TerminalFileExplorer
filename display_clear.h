#ifndef DISPLAY
#define DISPLAY

//#include "normalMode.h"
#include "headerfiles.h"

#include "glb_vars.h"

//#include "commandmode.h"
#include "additionalfunc.h"

void clear_next_stack(){
    while(!next_stack.empty()){
        next_stack.pop();
    }
}
void clear_prev_stack(){
    while(!prev_stack.empty()){
        prev_stack.pop();
    }
}


void clear_screen(){
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
    xpos=1;
    ypos=1;
    goto(xpos,ypos);
}
void user_permission(struct stat& buf){
    printf((buf.st_mode & S_IRUSR) ? "r" : "-");
    printf((buf.st_mode & S_IWUSR) ? "w" : "-");
    printf((buf.st_mode & S_IXUSR) ? "x" : "-");
    printf((buf.st_mode & S_IRGRP) ? "r" : "-");
    printf((buf.st_mode & S_IWGRP) ? "w" : "-");
    printf((buf.st_mode & S_IXGRP) ? "x" : "-");
    printf((buf.st_mode & S_IROTH) ? "r" : "-");
    printf((buf.st_mode & S_IWOTH) ? "w" : "-");
    printf((buf.st_mode & S_IXOTH) ? "x" : "-");
    struct passwd *pwd_id = getpwuid(buf.st_uid);
	struct group *grp_id = getgrgid(buf.st_gid);
    printf("  %-10s",pwd_id->pw_name);
    printf("  %-10s",grp_id->gr_name);
}
void display(string path){
    //openable_detection(path);
    if(path.size()>4 && path.substr(path.size()-3,3)=="txt") open_contents.push_back(path);
    struct stat buf;
    stat(path.c_str(), &buf);
    int size = buf.st_size;
    char file_type;
    switch (buf.st_mode & S_IFMT) {
        case S_IFBLK: file_type='b'; break;
        case S_IFCHR: file_type='c'; break;
        case S_IFDIR: file_type='d';open_contents.push_back(path); break;
        case S_IFLNK: file_type='l'; break;
        case S_IFREG: file_type='-'; break;
        case S_IFSOCK: file_type='s';break;
        default: file_type='-';      break;
    }
    printf("%-1c",file_type);
    user_permission(buf);
    char* time;
    time=ctime(&buf.st_mtime);
    double newsize=(double)size/1024;
    printf("%-20s",path.c_str());
    printf("%-10fKb",newsize);
    printf("  %-20s",time);
    //printf("\n");

}

void window_list(){
    //write(STDOUT_FILENO,"\e[2J", 12); //clear screen before writing to Std file buffer
    clear_screen();
    xpos=1;
    ypos=1;
    goto(xpos,ypos);
    int row;
    //cout<<"line number=="<<line<<"\n";
    //cout<<"present_window=="<<present_window<<"\n";
    if (contents.size() <= line){
        //cout<<"line number"<<line<<"\n";
        row= contents.size() - 1;
    }
    else
        row = (line-2) + present_window;
    for (int i = present_window; i <= row; i++) {
        string str = contents[i];
        display(str);
    }

}


void moveUp(){
       if(xpos > 1) {
        xpos=xpos-1;
        goto(xpos,ypos);
    }
    else if (xpos == 1 && xpos + present_window > 1) {
        present_window--;
        window_list();
        goto(xpos,ypos);
    }

}

void moveDown(){
     if (xpos <= line) {
        xpos=xpos+1;
        goto(xpos,ypos);
    }
    else if (xpos > line && xpos + present_window < contents.size()) {
        present_window++;
        window_list();
        goto(xpos,ypos);
    }
}

void moveRight(){

    if(!next_stack.empty()){
        clear_screen();
        prev_stack.push(present_working_dir);
        present_working_dir=next_stack.top();
        next_stack.pop();

        content_listing();
    }
}
void moveLeft(){
    if(!prev_stack.empty()){
        clear_screen();
        next_stack.push(present_working_dir);
        present_working_dir=prev_stack.top();
        prev_stack.pop();
        content_listing();
    }
}
void goHome(){
    prev_stack.push(present_working_dir);
    present_working_dir=root_path;
    content_listing();
    clear_next_stack();
}

void enterDir(){

    //parent_stack.push(present_working_dir);
    //present_working_dir=get_current_dir_name();
    //prev_stack.push(present_working_dir );
    if(xpos==1){
        //handling '.' directory
        //present_working_dir=".";
        clear_screen();
        content_listing();
    }
    else if(xpos==2){
        //handling '..' directory which is parent
        //present_working_dir=get_current_dir_name();
        std::size_t found = present_working_dir.find_last_of("/\\");
       // root_path=present_working_dir;
        present_working_dir=present_working_dir.substr(0,found);
        prev_stack.push(present_working_dir);

        clear_screen();
        content_listing();
    }
    else {
        bool flag=false;
        bool flag_txt=false;
        string direct;
        string file;
        for(int i =0;i<open_contents.size();i++){
            if(contents[xpos-1]==open_contents[i]){
                flag=true;
                if(contents[xpos].size()>4 && (contents[xpos].substr(contents[xpos].size()-3,3)=="txt")) flag_txt=true;
                direct=contents[present_window+xpos-1];
                prev_stack.push(present_working_dir);
                present_working_dir+="/"+ direct;
                file=createAbsPath(contents[present_window+xpos-1]);
                //std::size_t found = present_working_dir.find_last_of("/\\");
                //next_stack.push(present_working_dir);
                //present_working_dir=present_working_dir.substr(0,found);
                break;
            }
        }
        clear_screen();
        /*
        if(flag_txt){
            prev_stack.pop();
            present_working_dir=prev_stack.top();
            int processId = fork();
            if (processId == 0) {
                close(2);
                execlp("/user/bin/xdg-open", "xdg-open", file.c_str(), NULL);
                exit(1);
            }
        }
        else if(flag && (flag_txt==false)){
            clear_next_stack();
            content_listing();
        }*/
        if(isDirectory(present_working_dir)){
            clear_next_stack();
            content_listing();
        }
        else {
            prev_stack.pop();
            present_working_dir=prev_stack.top();
            int processId = fork();
            if (processId == 0) {
                //close(2);
                execlp("/user/bin/xdg-open", "xdg-open", file.c_str(), NULL);
                exit(1);
            }
        }

        //else if(flag && (flag_txt==true)){
        //}
    }

}

void oneLevelUp(){
        //present_working_dir=get_current_dir_name();
        std::size_t found = present_working_dir.find_last_of("/\\");
        //next_stack.push(present_working_dir);
        present_working_dir=present_working_dir.substr(0,found);
        prev_stack.push(present_working_dir);
        clear_next_stack();
        clear_screen();
        content_listing();
}

#endif// Display
