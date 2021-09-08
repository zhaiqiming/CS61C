#include "hashtable.h"

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
HashTable *createHashTable(int size, unsigned int (*hashFunction)(void *),
                           int (*equalFunction)(void *, void *)) {
  int i = 0;
  HashTable *newTable = malloc(sizeof(HashTable));
  if (NULL == newTable) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  newTable->size = size;
  newTable->buckets = malloc(sizeof(struct HashBucketEntry *) * size);
  if (NULL == newTable->buckets) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  for (i = 0; i < size; i++) {
    newTable->buckets[i] = NULL;
  }
  newTable->hashFunction = hashFunction;
  newTable->equalFunction = equalFunction;
  return newTable;
}

/* Task 1.2 */
void insertData(HashTable *table, void *key, void *data) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket location with table->hashFunction.
  int index = table->hashFunction(key) % table->size;
  // 2. Allocate a new hash bucket entry struct.
  struct HashBucketEntry* temp = (struct HashBucketEntry *)(malloc(sizeof(struct HashBucketEntry)));
  temp->key = key;
  temp->data = data;
  // 3. Append to the linked list or create it if it does not yet exist. 
  if (table->buckets[index] == NULL){
    table->buckets[index] = temp;
  }else{
    struct HashBucketEntry* head = table->buckets[index];
    while(head->next != NULL) head = head->next;
    head->next = temp;
  }
  // printf("################");
}

/* Task 1.3 */
void *findData(HashTable *table, void *key) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket with table->hashFunction.
  int index = table->hashFunction(key) % table->size;
  // 2. Walk the linked list and check for equality with table->equalFunction.
  struct HashBucketEntry* head = table->buckets[index];
  while(head != NULL){
    if(table->equalFunction(key, head->key)){
      return head->data;
    }
    head = head->next;
  }
  return NULL;
}

/* Task 2.1 */
unsigned int stringHash(void *s) {
  // -- TODO --
  // fprintf(stderr, "need to implement stringHash\n");
  /* To suppress compiler warning until you implement this function, */
  unsigned int ans = 0;
  unsigned int ch;
  while(ch = *(char*)(s++)){
    ans = ans * 131 + ch;
  }
  return ans;
}

/* Task 2.2 */
int stringEquals(void *s1, void *s2) {
  // -- TODO --
  // fprintf(stderr, "You need to implement stringEquals");
  /* To suppress compiler warning until you implement this function */
  while(*(char*)s1 != '\0' && *(char*)s2 != '\0'){
    if (*(char*)(s1++) != *(char*)(s2++)){
      return 0;
    }  
  }
  if(*(char*)s1 != '\0' || *(char*)s2 != '\0') return 0;
  else return 1;
}