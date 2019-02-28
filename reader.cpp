#include "reader.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

typedef struct reader_{
    FILE* src;
    int end_trigger;
}reader_, *preader_;

void reader_destroy()
{
}

char* _reader_getword(reader* r)
{
    printf("Reader_getword start\n");
    reader_* r_ = (reader_*)((char*)r + sizeof(reader));

    char* w = (char*) calloc(30, sizeof(char));
    char c = fgetc(r_->src);
    printf("%c\n",c);
    int i;

    while(!isalpha(c)){          //skip non-letter charachters
        if(c == EOF ||(c == '\n' && r_->src == stdin)) {
            return NULL;
        }
        c = fgetc(r_->src);
    }

    for(i = 0; isalpha(c) ; i++) {
        w[i] = c;
        c = fgetc(r_->src);

    }
    if((c == EOF && i == 0) || (c == '\n' && r_->src == stdin && i == 0)) {
        free(w);

        return NULL;
    }

    if(c == EOF)
        r_->end_trigger = 1;
    w[i] = '\0';

    printf("word = %s \n", w);

    return w;
}

char* reader_getword(reader* r)
{
    reader_* r_ = (reader_*)((char*)r + sizeof(reader));

    if(r_->end_trigger != 1){
        char* w = _reader_getword(r);
        if(w == NULL) {
            r_->end_trigger = 1;
        }
        return w;
    }

    return NULL;
}

reader* reader_readstdin()
{
    reader* r = (reader*) malloc(sizeof(reader_) + sizeof(reader));
    reader_* r_ = (reader_*)((char*)r + sizeof(reader));

    r->getword = &reader_getword;
    r->destroy = &reader_destroy;

    r_->end_trigger = 0;
    r_->src = stdin;

    printf("ready to read stdin\n");

    return r;
}

reader* reader_openfile(char* file_name)
{
    printf("%s\n",file_name);

    reader* r = (reader*) malloc(sizeof(reader_) + sizeof(reader));
    reader_* r_ = (reader_*)((char*)r + sizeof(reader));

    FILE* file = fopen(file_name, "r");
    if(file == NULL) {
        perror(NULL);
        return NULL;
    }
    r->getword = &reader_getword;
    r->destroy = &reader_destroy;

    r_->src = file;
    r_->end_trigger = 0;

    return r;
}

void reader_closefile(reader* r)
{
    reader_* r_ = (reader_*)((char*)r + sizeof(reader));
    fclose(r_->src);
}
