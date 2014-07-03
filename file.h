#ifndef fi
#define fi


class file{
public:
    char name[64];
    long int len;
    int startpos;

    char* get_file_name();
    long int get_file_length();
    int get_startpos();
};

#endif // fi
