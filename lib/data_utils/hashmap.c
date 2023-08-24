#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

unsigned int hash(const char *key) {
    if(key == NULL)
    {
        fprintf(stderr, "Key cannot be NULL (HashMap.hash function)\n");
        exit(1);
    }

    size_t keyLength = strlen(key);
    unsigned int generatedHash = 0;
    size_t iterator = 0;

    for (; iterator < keyLength; iterator++) {
        generatedHash += key[iterator];
    }

    return generatedHash % HASH_MAP_SIZE;
}

HashMap* HashMap_init() {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        map->table[i] = NULL;
    }
    return map;
}

void HashMap_add(HashMap* map, char *key, char *value) {
    if(key == NULL)
    {
        fprintf(stderr, "Key cannot be NULL\n");
        return;
    }
    if(value == NULL)
    {
        fprintf(stderr, "Key cannot be NULL\n");
        return;
    }

    int index = hash(key);
    HashMapNode* newNode = (HashMapNode*)malloc(sizeof(HashMapNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = map->table[index];
    map->table[index] = newNode;
}

char *HashMap_get(HashMap* map, char *key) {
    if(key == NULL)
    {
        fprintf(stderr, "Key cannot be NULL\n");
        return NULL;
    }

    int index = hash(key);
    HashMapNode* current = map->table[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void HashMap_remove(HashMap* map, char *key) {
    int index = hash(key);
    HashMapNode* current = map->table[index];
    HashMapNode* prev = NULL;
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                map->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void HashMap_destroy(HashMap* map) {
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        HashMapNode* current = map->table[i];
        while (current != NULL) {
            HashMapNode* temp = current;
            current = current->next;
            free(temp);
            temp = NULL;
        }
    }
    free(map);
}

