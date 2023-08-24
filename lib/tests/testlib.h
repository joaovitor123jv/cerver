#ifndef CERVER_TEST_LIB_H
#define CERVER_TEST_LIB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TEST_NAME_SIZE      100

/* Test macros */
unsigned int passed_conditions = 0;
unsigned int failed_conditions = 0;
char ongoing_test_has_errors = 0;

#define ENSURE(condition)       if(!(condition)) { fprintf(stdout, " ! Test failed on %s:%d\n", __FILE__, __LINE__); failed_conditions++; ongoing_test_has_errors = 1; } else { passed_conditions++; }

unsigned int test_number = 0;
unsigned int test_ok = 0;

void start_test(const char *test_name)
{
    int iterator = 0;
    char *test_description = (char *)malloc(MAX_TEST_NAME_SIZE * sizeof(char));
    assert(test_description != NULL);
    memset(test_description, '\0', MAX_TEST_NAME_SIZE);
    test_number++;

    /* Generates test description */
    snprintf(test_description, MAX_TEST_NAME_SIZE, "Starting test %d: %s ", test_number, test_name);

    iterator = strlen(test_description);
    if(iterator >= MAX_TEST_NAME_SIZE)
    {
        fprintf(stdout, "Critical failure: Cannot render text of this size. MAX_TEST_NAME_SIZE reached\n");
        fprintf(stdout, "- Aborting on %s\n", __func__);
        exit(1);
    }

    /* Add dots on the end of the test name until fill the MAX_TEST_NAME_SIZE */
    for (; iterator < (MAX_TEST_NAME_SIZE - 1); iterator++)
        test_description[iterator] = '.';

    fputs(test_description, stdout);
    free(test_description);
    test_description = NULL;
}

void test_done()
{
    if(ongoing_test_has_errors == 0) 
    {
        fputs(" DONE\n", stdout);
        test_ok++;
    }
    else ongoing_test_has_errors = 0;
}

void print_results()
{
    printf("Tests finished.\n");
    printf("Amount of tests made: %d\n", test_number);
    printf("Amount of tests failed: %d\n", test_number - test_ok);
    printf("Amount of tests succeeded: %d\n", test_ok);
    printf("Success rate: %.2f%%\n", (float)test_ok / (float)test_number * 100.0f);
    printf("Amount of conditions passed: %d\n", passed_conditions);
    printf("Amount of conditions failed: %d\n", failed_conditions);
    printf("Success rate (conditions): %.2f%%\n", (float)passed_conditions / (float)(passed_conditions + failed_conditions) * 100.0f);
}


#endif /* CERVER_TEST_LIB_H */
