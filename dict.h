#ifndef DICT_H
#define DICT_H



typedef struct dict
{
    void (*showres)(dict* d);
    void (*addelem)(char* s, dict* d);
}dict, *pdict;

dict* dict_create();


dict* hash_table_create (int n_buckets);

#endif
