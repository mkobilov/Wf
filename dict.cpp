#include "dict.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct word
{
    char* str;
    int freq;
    struct word* next;
} word, *pword;

typedef struct dict_
{
    word* fst;
    word* lst;
}dict_, *pdict_;



word* word_create(char* s)
{
    word* w = (word*) calloc(1, sizeof(word));

    w->str = s;
    w->freq = 1;
    w->next = NULL;

    printf("word->str = %s\n",w->str);
    return w;
}

int dict_checkword(word* w, dict* d)
{
    dict_* d_ = (dict_*) ((char*) d + sizeof(dict));
    word* cur;
    for(cur = d_->fst; cur != NULL; cur = cur->next) {
        if(!strcmp(cur->str, w->str)) {
            cur->freq += 1;
            return 1;
        }
    }
    return 0;
}

void dict_addelem(char* s, dict* d)
{
    dict_* d_ = (dict_*) ((char*) d + sizeof(dict));
    word* w = word_create(s);
    if(dict_checkword(w, d) == 1){
        return;
    }
    if(d_->fst != NULL){
        d_->lst->next = w;
        d_->lst = d_->lst->next;
    }
    else {
        d_->fst = w;
        d_->lst = w;
    }
}

void dict_showres(dict* d)
{
    printf("res:\n");
    dict_* d_ = (dict_*) ((char*) d + sizeof(dict));
    word* cur;
    for(cur = d_->fst; cur != NULL; cur = cur->next) {
        printf("%s , %d\n", cur->str, cur->freq);
    }
}

dict* dict_create()
{
    dict* d = (dict*) malloc(sizeof(dict_) + sizeof(dict));
    dict_* d_ = (dict_*) ((char*) d + sizeof(dict));

    d->addelem = &dict_addelem;
    d->showres = &dict_showres;

    d_->fst = NULL;
    d_->lst = NULL;
    return d;
}

void dict_destroy(dict* d)
{
    dict_* d_ = (dict_*) ((char*) d + sizeof(dict));
    word* tmp;
    word* cur = d_->fst;
    while(cur != NULL) {
        tmp = cur;
        cur = cur->next;

        free(tmp);
        free(d);
    }
}
