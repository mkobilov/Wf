#include <stdio.h>

#include "reader.h"
#include "dict.h"

int main(int argc, char* argv[])
{
    char* s;
    dict* d = hash_table_create(50);
    if(argc == 1) {
        reader* r = reader_readstdin();
        for(; s != NULL;) {
            s = NULL;
            s = r->getword(r);
            if(s != NULL)
                d->addelem(s, d);
        }
    }

    else {
        reader* r;
        int k;
        for(k = 1; k < argc; k++) {
            r = reader_openfile(argv[k]);
            while(s != NULL) {
                s = r->getword(r);
                if(s != NULL)
                    d->addelem(s, d);
            }
        }
    }

    d->showres(d);
    return 0;
}
