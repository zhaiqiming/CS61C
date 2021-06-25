#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#include "../src/hashtable.h"
#include "../src/philphix.h"

/* For free() */
#include <stdlib.h>

/* For printf() */
#include <stdio.h>

/** 
 * This file uses the CUnit framework to unit test the various functions of Philphix. We recommend you make use
 * of these tests to assist with writing and debugging your functions. You are also encouraged to add your own tests (see main()).
 * 
 * Note that passing all the unit tests for a function does NOT guarantee that that function is fully correct. These tests are largely
 * sanity tests and basic cases, but may not cover all edge cases or possible scenarios. Again, you are encouraged to write your own tests
 * for these cases.
 */

/* Runs prior to any test in the Hashtable Suite */
int init_hashtb() {
    dictionary = createHashTable(0x61c, &stringHash, &stringEquals);
    if (dictionary == NULL) {
        return -1;
    }
    return 0;
}

/* Runs after all tests in the Hashtable Suite 
* This is NOT the proper way to free a HashTable, but for small scale unit tests
* it doesn't particuarly matter. */
int clean_hashtb() {
    free(dictionary);
    dictionary = NULL;
    return 0;
}

// Insert a K-V pair, should be able to retrieve the value
void test_InsertGet() {
    char *tkey = "in";
    char *tval = "out";
    insertData(dictionary, (void*)tkey, (void*)tval);
    CU_ASSERT((void*)tval == findData(dictionary, (void*)tkey));

    char *tkey1 = "inner";
    char *tval1 = "outer";
    insertData(dictionary, (void*)tkey1, (void*)tval1);
    CU_ASSERT((void*)tval1 == findData(dictionary, (void*)tkey1));
    CU_ASSERT(NULL == findData(dictionary, (void*)tval));
}

// Non-existent key should return NULL
void test_badGet() {
    char *tval = "out"; // exists as a value but not a key
    char *DNE = "doesnotexist";
    CU_ASSERT(NULL == findData(dictionary, (void*)tval));
    CU_ASSERT(NULL == findData(dictionary, (void*)DNE));
}

void test_stringEq() {
    char *s1 = "thisclassisCS61C";
    char *s1c = "thisclassisCS61C";
    char *s2 = "thisClassisCS61C";
    char *s3 = "thisclassisCS61B";
    char *s4 = "";
    char *s4c = "";
    char *s5 = "\t\n";
    char *s5c = "\t\n";
    CU_ASSERT(0 != stringEquals((void*)s1, (void*)s1c));
    CU_ASSERT(0 == stringEquals((void*)s1, (void*)s2));
    CU_ASSERT(0 == stringEquals((void*)s1, (void*)s3));
    CU_ASSERT(0 != stringEquals((void*)s4, (void*)s4c));
    CU_ASSERT(0 == stringEquals((void*)s4, (void*)s5));
    CU_ASSERT(0 != stringEquals((void*)s5, (void*)s5c));
}

/** Hashes should be deterministic and (generally) distinct */
void test_stringHash() {
    char *s1 = "thisclassisCS61C";
    char *s2 = "thisClassisCS61C";
    char *s3 = "someotherstring";
    CU_ASSERT(stringHash((void*)s1) == stringHash((void*)s1));
    CU_ASSERT(stringHash((void*)s1) != stringHash((void*)s2));
    CU_ASSERT(stringHash((void*)s1) != stringHash((void*)s3));
}

// Task 3: Dictionary
// Test suite setup/teardown
int task3_setup_teardown() {
    if (dictionary != NULL) {
        free(dictionary); // todo proper free? leaks memory
        dictionary = NULL;
    }
    remove("unittest.dict");
    return 0;
}

// Individual test setup/teardown
int task3_test_setup() {
    dictionary = createHashTable(0x61c, &stringHash, &stringEquals);
    if (dictionary == NULL) {
        return -1;
    }
    return 0;
}

int task3_test_teardown() {
    free(dictionary); // todo proper free? leaks memory
    dictionary = NULL;
    remove("unittest.dict"); // Delete the test dictionary
    return 0;
}


int task3_helper_write(char* s) {
    FILE *outFile = fopen("unittest.dict", "w");
    int r = fputs(s, outFile);
    fclose(outFile);
    return r;
}

void task3_test_empty() {
    CU_ASSERT(task3_test_setup() == 0);

    char* dictStr = "";
    CU_ASSERT(task3_helper_write(dictStr) >= 0)

    readDictionary("unittest.dict");
    for (int i = 0; i < dictionary->size; i++) {
        CU_ASSERT(dictionary->buckets[i] == NULL);
    }

    CU_ASSERT(task3_test_teardown() == 0);
}

void task3_test_simple() {
    CU_ASSERT(task3_test_setup() == 0);

    char* dictStr = "a b\n";
    CU_ASSERT(task3_helper_write(dictStr) >= 0)

    readDictionary("unittest.dict");

    char* key = "a";
    char* value = "b";
    char* foundData = findData(dictionary, key);
    CU_ASSERT(foundData != NULL);
    CU_ASSERT(strcmp(foundData, value) == 0);

    CU_ASSERT(task3_test_teardown() == 0);
}

void task3_test_simple_no_newline() {
    CU_ASSERT(task3_test_setup() == 0);

    char* dictStr = "a b";
    CU_ASSERT(task3_helper_write(dictStr) >= 0)

    readDictionary("unittest.dict");

    char* key = "a";
    char* value = "b";
    char* foundData = findData(dictionary, key);
    CU_ASSERT(foundData != NULL);
    CU_ASSERT(strcmp(foundData, value) == 0);

    CU_ASSERT(task3_test_teardown() == 0);
}

void task3_test_alphanum() {
    CU_ASSERT(task3_test_setup() == 0);
    
    char* dictStr = "abcABC123 b\n";
    CU_ASSERT(task3_helper_write(dictStr) >= 0)

    readDictionary("unittest.dict");

    char* key = "abcABC123";
    char* value = "b";
    char* foundData = findData(dictionary, key);
    CU_ASSERT(foundData != NULL);
    CU_ASSERT(strcmp(foundData, value) == 0);

    CU_ASSERT(task3_test_teardown() == 0);
}

void task3_test_multiline() {
    CU_ASSERT(task3_test_setup() == 0);

    char* dictStr = "a b\nc d\ne f\ng h\n";
    CU_ASSERT(task3_helper_write(dictStr) >= 0)

    readDictionary("unittest.dict");

    char* key = "a";
    char* value = "b";
    char* foundData = findData(dictionary, key);
    CU_ASSERT(foundData != NULL);
    CU_ASSERT(strcmp(foundData, value) == 0);

    key = "c";
    value = "d";
    foundData = findData(dictionary, key);
    CU_ASSERT(foundData != NULL);
    CU_ASSERT(strcmp(foundData, value) == 0);

    key = "e";
    value = "f";
    foundData = findData(dictionary, key);
    CU_ASSERT(foundData != NULL);
    CU_ASSERT(strcmp(foundData, value) == 0);

    key = "g";
    value = "h";
    foundData = findData(dictionary, key);
    CU_ASSERT(foundData != NULL);
    CU_ASSERT(strcmp(foundData, value) == 0);

    CU_ASSERT(task3_test_teardown() == 0);
}

void task3_test_punctuation() {
    CU_ASSERT(task3_test_setup() == 0);

    char* dictStr = "a abc,def.ghi!jkl\n";
    CU_ASSERT(task3_helper_write(dictStr) >= 0)

    readDictionary("unittest.dict");

    char* key = "a";
    char* value = "abc,def.ghi!jkl";
    char* foundData = findData(dictionary, key);
    CU_ASSERT(foundData != NULL);
    CU_ASSERT(strcmp(foundData, value) == 0);

    CU_ASSERT(task3_test_teardown() == 0);
}

void task3_test_tabs() {
    CU_ASSERT(task3_test_setup() == 0);

    char* dictStr = "a\tb\nc\t\td\ne \tf\ng\t h\n";
    CU_ASSERT(task3_helper_write(dictStr) >= 0)

    readDictionary("unittest.dict");

    char* key = "a";
    char* value = "b";
    char* foundData = findData(dictionary, key);
    CU_ASSERT(foundData != NULL);
    CU_ASSERT(strcmp(foundData, value) == 0);

    key = "c";
    value = "d";
    foundData = findData(dictionary, key);
    CU_ASSERT(foundData != NULL);
    CU_ASSERT(strcmp(foundData, value) == 0);

    key = "e";
    value = "f";
    foundData = findData(dictionary, key);
    CU_ASSERT(foundData != NULL);
    CU_ASSERT(strcmp(foundData, value) == 0);

    key = "g";
    value = "h";
    foundData = findData(dictionary, key);
    CU_ASSERT(foundData != NULL);
    CU_ASSERT(strcmp(foundData, value) == 0);

    CU_ASSERT(task3_test_teardown() == 0);
}


int main() {
    CU_pSuite pSuite;
    
    // init CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    pSuite = CU_add_suite("HashTable", init_hashtb, clean_hashtb);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite, "HashTable Insert & Get", test_InsertGet) == NULL) 
            || (CU_add_test(pSuite, "HashTable Get", test_badGet) == NULL )
            || (CU_add_test(pSuite, "stringEquals", test_stringEq) == NULL )
            || (CU_add_test(pSuite, "stringHash", test_stringHash) == NULL )
            ) {
        
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Task 3
    CU_pSuite task3Suite = CU_add_suite("Task 3", task3_setup_teardown, task3_setup_teardown);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(task3Suite, "Empty dictionary", task3_test_empty) == NULL) ||
        (CU_add_test(task3Suite, "Simple", task3_test_simple) == NULL) ||       
        (CU_add_test(task3Suite, "Simple without newline", task3_test_simple_no_newline) == NULL) ||       
        (CU_add_test(task3Suite, "Alphanumeric key", task3_test_alphanum) == NULL) ||       
        (CU_add_test(task3Suite, "Multiple entries", task3_test_multiline) == NULL) ||       
        (CU_add_test(task3Suite, "Non-alphanumeric value", task3_test_punctuation) == NULL) ||       
        (CU_add_test(task3Suite, "Tabs and spaces", task3_test_tabs) == NULL)
       ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
