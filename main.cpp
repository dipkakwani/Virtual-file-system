#include <iostream>
#include<fstream>
#include "filesys.h"
#include<string.h>
//Coder - Diptanshu Kakwani
using namespace std;

int main(int argc, char* argv[])    //Enter command line arguments to open a previously created file system
                                    // or leave blank to create a new one.
{
    char name[80], content[200], name1[80], keyword[60], *c = NULL;
    cout<< "-----------------------------------------------------------------------------\n";
    cout<< "************************ Virtual File System *********************************\n";
    cout<< "-----------------------------------------------------------------------------\n";
    int choice;
    filesys f1(argv[1]);

    while(1)
    {
        cout << "\nEnter your choice:\n";
        cout << "1. List files in the file system\n";
        cout << "2. Show file content\n";
        cout << "3. Search a file\n";
        cout << "4. Search for a keyword in a file\n";
        cout << "5. Create new file\n";
        cout << "6. Delete a file\n";
        cin >> choice;
        switch(choice)
        {
            case 1:
                f1.list_files();
                break;
            case 2:
                cout << "Enter file name\n";
                cin >> name;
                c = f1.show_file_content(name);
                if(c != NULL)
                    cout << c;
                break;
            case 3:
                cout << "Enter file name\n";
                cin >> name;
                c = f1.search_file(name);
                if(c != NULL)
                    cout << c;
                break;
            case 4:
                cout << "Enter the file name\n";
                cin >> name;
                cout << "Enter the keyword to be searched\n";
                cin >> keyword;
                f1.search_keyword(name, keyword);
                break;
            case 5:
                cout << "Enter the name of new file\n";
                cin >> name;
                cout << "Enter the content of the file\n";
                cin.clear();
                fflush(stdin);
                cin.getline(content, sizeof(content));
                f1.create_file(name, content);
                break;
            case 6:
                cout << "Enter the name of the file to be deleted\n";
                cin >> name;
                f1.delete_file(name);
                break;
            default:
                cout << "Enter a valid option!\n";
        }
        cout << "\nEnter 0 to exit; 1 to continue\n";
        cin >> choice;
        if(!choice)
            break;
    }
    return 0;
}
