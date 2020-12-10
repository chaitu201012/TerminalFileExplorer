#ifndef NORMAL_MODE
#define NORMAL_MODE

#include "headerfiles.h"

#include "glb_vars.h"

#include "display_clear.h"

#include "commandmode.h"

void disable_noncan_Mode() {
    xpos=1;
    ypos=1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
    goto(xpos,ypos);
}
void noncanonical_Mode(){
    
    unsigned int term= wind.ws_row;
    //cy = 1;
    printf("%c[%d;%dH", 27, term, 1);
    printf("-------Normal Mode---------");
    tcgetattr(STDIN_FILENO, &original);
    noncan_mode=original;
    noncan_mode.c_iflag &=~(IEXTEN | ISIG);
    noncan_mode.c_lflag &= ~(BRKINT);
    noncan_mode.c_lflag &=~ICANON;
    noncan_mode.c_lflag &=~ECHO;
    xpos=1;
    ypos=1;
    int x=tcsetattr(STDIN_FILENO, TCSAFLUSH, &noncan_mode);
    if (x!=0)
        fprintf(stderr, " Action cannot be performed \n");
    else{
        goto(xpos,ypos);
        
        while(1){
            char c,d,e;
            fflush(0);
            //cout<<"entering while loop\n";
            c=cin.get();

            //cout<<ch<<endl;
            if(c==27){
                d=cin.get();
                e=cin.get();
                if((e==65)){
                    moveUp();
                }
                else if((e==66)){
                    moveDown();
                }
                else if((e==67)){
                    moveRight();
                }
                else if((e==68)){
                    moveLeft();
                }
            }
            else if(c==72||c==104){
                goHome();
            }
            else if(c==127||c==8){
                oneLevelUp();
            }
            else if(c==10){
                //goto(line,col);
                enterDir();
            }
            else if(c==58){
                    //when ":" is pressed we need to switch to command mode 
                    commandMode();
            }
            else if (c== 'q') {
                    clear_screen();
                    disable_noncan_Mode();
            }

        }
    }


}
void content_listing(){

    DIR *dir;

    dir=opendir(present_working_dir.c_str());
    struct dirent *name;
    if(dir==NULL){
        Errormessage("Error opening the directory");
        disable_noncan_Mode();
        exit(1);
    }
    contents.clear();
    open_contents.clear();
    while((name=readdir(dir))!=NULL){
        contents.push_back(name->d_name);
    }
    closedir(dir);

    sort(contents.begin(),contents.end());

    //printf("\n");
    window_list();
    cout<<"\n";
    /*
    for(int i=0;i<open_contents.size();i++){
        cout<<open_contents[i]<<"\n";
    }*/
    xpos=line;
    ypos=1;

    noncanonical_Mode();
}

void normal_mode(){


    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wind);
    line=wind.ws_row;
    col=wind.ws_col;
    //goto(line,1);
   

    content_listing();
    disable_noncan_Mode();
}
#endif// NORMAL_MODE
