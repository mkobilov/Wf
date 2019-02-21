#ifndef READER_H
#define READER_H

#include <stdio.h>

typedef struct reader reader, *preader;

struct reader
{
    char* (*getword)(reader* file_name);
    void (*destroy)();
};

reader* reader_readstdin();
reader* reader_openfile(char* file_name);



#endif // READER_H
