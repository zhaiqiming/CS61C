/*
 * This is so the C preprocessor does not try to include multiple copies
 * of the header file if someone uses multiple #include directives.
 */
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

/*
 * Everyone uses NULL, or 0, as the null pointer,
 * but C never defines it so you have to define it yourself.  :(
 */
#ifndef NULL
#define NULL ((void *)0)
#endif

/*
 * This header file defines an interface to a generic chained hash table. 
 * It stores void * data and uses two functions, int (*) (void *)
 * and int (*) (void *, void *), to compute the hash and check
 * for equality.
 */
typedef struct HashBucketEntry {
  void *key;
  void *data;
  struct HashBucketEntry *next;
} HashBucketEntry;

/* Task 1.1 */
typedef struct HashTable {
  // -- TODO --
  // HINT: Take a look at createHashTable.
} HashTable;

/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
extern HashTable *createHashTable(int size,
                                  unsigned int (*hashFunction)(void *),
                                  int (*equalFunction)(void *, void *));

extern void insertData(HashTable *table, void *key, void *data);

extern void *findData(HashTable *table, void *key);

extern unsigned int stringHash(void *s);

extern int stringEquals(void *s1, void *s2);

#endif
