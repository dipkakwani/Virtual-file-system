#include "file.h"

char* file :: get_file_name()
{
    return name;
}
long int file :: get_file_length()
{
    return len;
}

int file :: get_startpos()
{
    return startpos;
}
