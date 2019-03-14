#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#include "dict.h"

typedef struct hash_element
{
    char  *word;
    size_t word_s;//size of word
    size_t data;//number of times it occured
    struct hash_element *next;//element with the same hash key
} hash_element, *phash_element;

typedef struct hash_table
{
    hash_element **buckets;
    size_t n_buckets;
} hash_table, phash_table;




static hash_element *hash_element_new (char *key, size_t key_s)
{
    hash_element *elem = (hash_element*) calloc(1, sizeof(hash_element));
    elem->word =(char*) malloc(key_s);
    elem->data = 1;

    strcpy(elem->word, key);
    elem->word_s = key_s;
    return elem;
}

static int dl_new_hash (const char *s)
{
    int h = 5381;

    for (char c = *s; c != '\0'; c = *++s)
        h = h * 33 + c;
    return h;
}

static int hash_keys_cmp(char *key_a, size_t key_a_s,
                    char *key_b, size_t key_b_s)
{
    if (key_a_s != key_b_s)
        return 1;
    return 0;
}

void hash_insert_data(char *word, dict* d)
{
    hash_table* table = (hash_table*) ((char*) d + sizeof(dict));

    size_t index = dl_new_hash(word) % table->n_buckets;
    //if first elem
    if(table->buckets[index] == NULL) {
        hash_element *en = hash_element_new(word, strlen(word));
        table->buckets[index] = en;
    }
    else {
        hash_element *tmp = table->buckets[index];
        while (1) {
            // new and old elems matched
            if (!hash_keys_cmp(word, strlen(word),
                           tmp->word, tmp->word_s)) {
                tmp->data = tmp->data + 1;
                return;
            }
            if (!tmp->next) {
                tmp->next = hash_element_new(word, strlen(word));
                return;
            }
        }
    }
    return;
}

void hash_print(dict* d)
{
    hash_table* table = (hash_table*) ((char*) d + sizeof(dict));

    for (int i = 0; i < table->n_buckets; i++) {
        if (table->buckets[i]) {
            printf("[%d] ", i);
            printf("%s data: %d \n", table->buckets[i]->word, table->buckets[i]->data);
        } else
            printf("[%d] NULL\n", i);
    }
}

dict* hash_table_create (int n_buckets)
{
    dict *dtable = (dict*) malloc(sizeof(dict) + sizeof(hash_table));
    hash_table* table = (hash_table*) ((char*) dtable + sizeof(dict));

    table->n_buckets  = n_buckets;
    table->buckets    = (hash_element**) calloc(n_buckets, sizeof(hash_element*));

    dtable->addelem = hash_insert_data;
    dtable->showres = hash_print;

    return dtable;
}

void hash_table_destroy(dict* dtable)
{
    hash_table* table = (hash_table*) ((char*) dtable + sizeof(dict));

    free(table->buckets);
    free(dtable);
}
