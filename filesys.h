#define MAX_FILES 16
#define MAX_FILE_LEN 1000
#ifndef fs
#define fs
#include "file.h"
#include<fstream>
using namespace std;
class filesys
{
public:
    file files[MAX_FILES];

    void initialize();
    void read_from_file();
    void write_to_file();
    void set_file_system_name();
    filesys(char f_name[]);
    char file_system_name[20];
    void list_files();
    char* show_file_content(char* f_name);
    char* search_file(char* f_name);
    void search_keyword(char* f_name, char* keyword);
    void delete_file(char* f_name);
    void create_file(char* f_name, char* file_contents);
};

#endif // fs
