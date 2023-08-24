#ifndef CERVER_HASHMAP_H
#define CERVER_HASHMAP_H

#define HASH_MAP_SIZE 100

struct HashMapNode {
    char *key;
    char *value;
    struct HashMapNode* next;
};

typedef struct HashMapNode HashMapNode;

struct HashMap {
    HashMapNode* table[HASH_MAP_SIZE];
};

typedef struct HashMap HashMap;

HashMap* HashMap_init();

void HashMap_add(HashMap* map, char *key, char *value);

char *HashMap_get(HashMap* map, char *key);

void HashMap_remove(HashMap* map, char *key);

void HashMap_destroy(HashMap* map);


#endif /* CERVER_HASHMAP_H */
