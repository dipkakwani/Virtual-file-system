#include "filesys.h"
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<string>
#include<math.h>

using namespace std;
void filesys::set_file_system_name()
{       cout << "Enter file system name\n";
        char temp[80];
        cin >> temp;
        strcpy(file_system_name, temp);
        initialize();
}

filesys::filesys(char f_name[])
{
        if(f_name == NULL)
            set_file_system_name();
        else
        {
            cout << "Existing File System\n";
            strcpy(file_system_name, f_name);
            read_from_file();
        }
}
void filesys::initialize()
{
    fstream myfile(file_system_name, ios::out);
    int i;
    myfile.seekp(0, ios::beg);
    for(i = 0; i < MAX_FILES; i++)
    {
        strcpy(files[i].name, "\0");
        files[i].len = 0;
        files[i].startpos = 0;
    }
    myfile.close();
    write_to_file();
}

void filesys::list_files()
{
    for(int i = 0; i < MAX_FILES; i++)
    {
        if(!strcmp(files[i].get_file_name(), "\0"))
            break;
        cout << files[i].get_file_name() << endl;
    }
}

char* filesys::show_file_content(char* f_name)
{
    fstream myfile(file_system_name, ios::in);
    int i;
    char* file_contents = new char[MAX_FILE_LEN];
    cout << f_name << "\n";
    for(i = 0; i < MAX_FILES; i++)
    {
        if(!strcmp(files[i].get_file_name(), f_name))
        {
            myfile.seekg(files[i].get_startpos(), ios::beg);
            myfile.read(file_contents, files[i].get_file_length());
            *(file_contents + files[i].get_file_length()) = '\0';
            myfile.close();
            return file_contents;
        }
    }
    cout<<"File not found!";
    myfile.close();
    return NULL;
}
char* filesys::search_file(char* f_name)
{
    int i;
    for(i = 0; i < MAX_FILES; i++)
    {
        if(!strcmp(files[i].get_file_name(), f_name))
        {
            cout<<"File found\nFile name:";
            return files[i].get_file_name();
        }
    }

    cout<<"File not found!";
    return NULL;

}
void filesys :: search_keyword(char* f_name, char* keyword)
{
    fstream myfile(file_system_name, ios::in);
    for(int i = 0; i < MAX_FILES; i++)
    {
        if(!strcmp(f_name, files[i].get_file_name()))
        {
            char* file_content = new char[MAX_FILE_LEN];
            myfile.seekg(files[i].get_startpos());
            myfile.read(file_content, files[i].get_file_length());
            char* p = strstr(file_content, keyword);
            if(p == NULL)
            {
                cout<<"\nKeyword not Found!\n";
                myfile.close();
                return;
            }
            int pos = p - file_content + 1;      // The difference between the address of substring in the string and
                                                // the base address plus 1
            cout<<"\nKeyword Found!\nPosition of keyword:\t"<<pos;
            myfile.close();
            return;

        }
    }
    cout<<"\nFile not found!\n";
    myfile.close();
    return;
}

void filesys::delete_file(char* f_name)
{
    int i,j;
    char* file_content = new char[MAX_FILE_LEN];
    for(i = 0; i < MAX_FILES; i++)
    {
        if(!strcmp(files[i].get_file_name(), f_name))
        {
            int del_len;
            strcpy(files[i].name, "\0");
            del_len = files[i].get_file_length() ;
            files[i].len = 0;
            files[i].startpos = 0;
            write_to_file();        //Will skip the content of the file to be deleted
            for(j = i + 1; j < MAX_FILES ; j++)
            {
                strcpy(files[j - 1].name, files[j].get_file_name());
                files[j - 1].len = files[j].get_file_length();
                files[j - 1].startpos = files[j].get_startpos() - del_len;
            }
            write_to_file();
            cout << "\nFile deleted!\n";
            return;
        }
    }
    cout<<"File not found!";
}


void filesys::create_file(char* f_name, char* file_contents)
{
    int i;
    for(i = 0; i < MAX_FILES; i++){
        if(!strcmp(files[i].get_file_name(), "\0"))
            break;
    }
    if(i == MAX_FILES)
        cout<<"No space";
    else
    {
        fstream myfile(file_system_name, ios::out | ios::app);
        strcpy(files[i].name, f_name);
        files[i].len = strlen(file_contents);
        myfile.seekp(0, ios::end);
        files[i].startpos = myfile.tellp();
        myfile.write(file_contents,sizeof(char) * strlen(file_contents));
        myfile.close();
        write_to_file();
    }
}


void filesys::read_from_file()
{
    fstream myfile(file_system_name, ios::in);
    int i;
    myfile.seekg(0 , ios::beg);
    for(i = 0; i < MAX_FILES; i++)          //read already created files till null string is encountered or max limit
    {
        myfile.read((char*)&(files[i].name) , sizeof(files[i].name));
        if(!strcmp(files[i].name,"\0"))
            break;
        myfile.read((char*)&files[i].len , sizeof(long int));
        myfile.read((char*)&files[i].startpos , sizeof(int));
    }
    while(i < MAX_FILES)
    {
        strcpy(files[i].name,"\0");
        files[i].len = 0;
        files[i].startpos = 0;
        i++;
    }
    myfile.close();
}

void filesys::write_to_file()
{
    fstream myfile(file_system_name, ios::in);
    fstream newfile("temp.txt", ios::out);
    int i;
    char file_content[MAX_FILE_LEN];
    newfile.seekp(0 , ios::beg);
    for(i = 0; i < MAX_FILES; i++)
    {
        newfile.write((char*)&files[i].name , sizeof(files[i].name));
        newfile.write((char*)&files[i].len , sizeof(long int));
        newfile.write((char*)&files[i].startpos , sizeof(int));
    }
    for(i = 0; i < MAX_FILES; i++)
    {
        if(files[i].get_file_length())
        {
            myfile.seekg(files[i].get_startpos(), ios::beg);
            myfile.read((char*)&file_content, sizeof(char) * files[i].len);
            newfile.seekp(0 , ios::end);
            newfile.write((char*)&file_content, sizeof(char) * files[i].len);
        }
    }
    newfile.close();
    myfile.close();
    remove(file_system_name);
    rename("temp.txt", file_system_name);

}
