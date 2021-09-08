/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philphix.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in 
 * the grading process.
 */
#ifndef _PHILPHIX_UNITTEST
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Specify a dictionary\n");
    return 1;
  }
  /*
   * Allocate a hash table to store the dictionary.
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(0x61C, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();

  /*
   * The MAIN function in C should always return 0 as a way of telling
   * whatever program invoked this that everything went OK.
   */
  return 0;
}
#endif /* _PHILPHIX_UNITTEST */

/* Task 3 */
void readDictionary(char *dictName) {
  // -- TODO --
  const int length = 10000;
  FILE *fp = fopen(dictName, "r");
  while(1){
    char* key = (char*) malloc(sizeof(char) * length);
    char* value = (char*) malloc(sizeof(char) * length);
    if(fscanf(fp, "%s%s", key, value) == EOF){
      break;
    }
    if(strlen(key) && strlen(value)) {
      // printf("%s %s\n", key, value);
      insertData(dictionary, key, value);
    }
  }

}

/* Task 4 */
void processInput() {
  // -- TODO --
  // fprintf(stderr, "You need to implement processInput\n");
  const int length = 100000;
  char* word = (char*) malloc(sizeof(char) * length);
  char ch;
  int pos = 0;
  while((ch = getchar()) != EOF){
      if(isalpha(ch) || isdigit(ch)){
        *(word + pos++) = ch;
        // printf("%c",ch);
        continue;
      }
      *(word + pos) = '\0';
      pos = 0;
      // printf("first! : %s\n", word);
      char* res;
      //The exact word
      res = (char*)findData(dictionary, word);
      if(res != NULL) {
        printf("%s%c", res, ch);
        memset(word, 0 ,sizeof(word));
        continue;
      }

      int i = 0; 

      //The word with every alphabetical character except the first character converted to lowercase
      i = 1;
      for( ;i < strlen(word); i++){
        *(word + i) = tolower(*(word + i));
      }
      res = (char*)findData(dictionary, word);
      if(res != NULL) {
        printf("%s%c", res, ch);
        memset(word, 0 ,sizeof(word));
        continue;
      }

      //Every alphabetical character of the word converted to lowercase
      *(word + i) = tolower(*(word + i));
      res = (char*)findData(dictionary, word);
      if(res != NULL) {
        printf("%s%c", res, ch);
        memset(word, 0 ,sizeof(word));
        continue;
      }   

      printf("%s%c", word, ch);
      memset(word, 0 ,sizeof(word));
  }
}
