#ifndef  ADDITIONAL
#define  ADDITIONAL



#include "glb_vars.h"

void searchInDir(string searchable,string curDir){
    DIR *dir;
    struct dirent *entry;
    if(dir=opendir(curDir.c_str())){
        while((entry=readdir(dir))!=NULL){
            if(string(entry->d_name)=="." ||string(entry->d_name)==".." ) continue;
            else{
                string dname=string(entry->d_name);
                //string finalname= curDir+"/"+dname;
                if(dname==searchable) search_count++;
            }

        }
        closedir(dir);

    }
    else {
        Errormessage("Unable to open directory");
        return;
    }


}
string createAbsPath(string substr)
{
	string absolute="";
	if(substr[0] =='/')
	{
		absolute = root_path + substr;
	}
    else if(substr[0]=='.')
	{
		absolute = string(get_current_dir_name()) + substr.substr(1,substr.length());	
	}
	else if(substr[0]=='~')
	{
		absolute = root_path + substr.substr(1,substr.length());
	}
	else
	{
		absolute = string(get_current_dir_name())+ "/" + substr;
	}

	return absolute;
}
void deleteFile(string fullpath){
    remove(fullpath.c_str());

}

void deleteDirectory(string fullpath){
    DIR *dir;
    struct dirent *name;
    if(dir=opendir(fullpath.c_str())){
        while(name=readdir(dir)){
            if(string(name->d_name)=="." ||string(name->d_name)=="..") continue;
            string  newpath=fullpath+"/"+string(name->d_name);
           // string finalDestination=destination+"/"+string(name->d_name);
            struct stat buf;
            if(stat(newpath.c_str(),&buf)!=-1){

                if(S_ISDIR(buf.st_mode)){
                    deleteDirectory(newpath);
                }
                else{
                    deleteFile(newpath);
                }
            }
            else
            {
                perror("Error"); 
            }

        }
        closedir(dir);
        if(rmdir(fullpath.c_str())==-1){
             Errormessage("Error removing directory");
             return;
        }

    }
    else{
        Errormessage("Error openeing directory");
    }
}

void copyFile(string fullpath,string destination){
    int infile, outfile;
    char mem_block[1024];
    int size;
    infile=open(fullpath.c_str(),O_RDONLY);
    outfile=open(destination.c_str(),O_CREAT|O_WRONLY,0777);

    while((size=read(infile, mem_block, 1024)) > 0){
        write(outfile, mem_block, size);
    }

    struct stat sb;
    stat(fullpath.c_str(), &sb);
    chown(destination.c_str(), sb.st_uid, sb.st_gid);
    chmod(destination.c_str(), sb.st_mode);

    close(infile);
    close(outfile);

}
void copyDir(string fullpath,string destination){

    DIR *dir;
    struct dirent *name;
    if(mkdir(destination.c_str(),0777)==-1){
        //clrscr();
        clear_screen();
        cerr << "Error :  " << strerror(errno) << endl;
        
    }
    if(dir=opendir(fullpath.c_str())){
        while(name=readdir(dir)){
            if(string(name->d_name)=="." ||string(name->d_name)=="..") continue;
            string  newpath=fullpath+"/"+string(name->d_name);
            string finalDestination=destination+"/"+string(name->d_name);
            struct stat buf;
            if(stat(newpath.c_str(),&buf)!=-1){

                if(S_ISDIR(buf.st_mode)){
                    copyDir(newpath,finalDestination);
                }
                else{
                    copyFile(newpath,finalDestination);
                }
            }

        }
        closedir(dir);
    }

}



bool isDirectory(string path){
	struct stat sb;
	if (stat(path.c_str(),&sb) == -1) {
        perror("Error ");
    }
    else
    {
    	if((S_ISDIR(sb.st_mode)))
	    {
	    	return true;
	    }
	    else
	    {
	    	return false;
	    }
    }

    return -1;
}

string fileName(string fullpath)
{
	string filename;
	size_t found;
	found = fullpath.find_last_of("/\\");
	filename = fullpath.substr(found+1,fullpath.length());
	return filename;
}

void Errormessage(string msg){
    clear_screen();
    cout<<msg<<"  :"<<endl;
}

#endif // ! 