/*
** EPITECH PROJECT, 2022
** ASM
** File description:
** main.c
*/

#include "tests.h"

size_t (*my_strlen)(const char *);
char *(*my_strchr)(const char *, int );
char *(*my_strrchr)(const char *, int);
char *(*my_index)(const char *, int);
char *(*my_rindex)(const char *, int);

void *(*my_memset)(void *, int, size_t);
void *(*my_memfrob)(void *, int, size_t);
void *(*my_memcpy)(void *, const void *, size_t);
void *(*my_memmove)(void *, const void *, size_t);

int (*my_strcmp)(const char *, const char *);
int (*my_strncmp)(const char *, const char *, size_t);
int (*my_strcasecmp)(const char *, const char *);
int (*my_ffs)(int);

char *(*my_strstr)(const char *, const char *);
char *(*my_strpbrk)(const char *, const char *);
size_t (*my_strcspn)(const char *, const char *);

const char *functions_name[] = {
    "strlen",
    "strchr",
    "memset",
    "memcpy",
    "memmove",
    "strcmp",
    "strncmp",
    "strcasecmp",
    "strrchr",
    "strstr",
    "strpbrk",
    "strcspn",
    "memfrob",
    "index",
    "rindex",
    "ffs",
    NULL
};
func_ptr *functions[] = {
    (func_ptr*)&my_strlen,
    (func_ptr*)&my_strchr,
    (func_ptr*)&my_memset,
    (func_ptr*)&my_memcpy,
    (func_ptr*)&my_memmove,
    (func_ptr*)&my_strcmp,
    (func_ptr*)&my_strncmp,
    (func_ptr*)&my_strcasecmp,
    (func_ptr*)&my_strrchr,
    (func_ptr*)&my_strstr,
    (func_ptr*)&my_strpbrk,
    (func_ptr*)&my_strcspn,
    (func_ptr*)&my_memfrob,
    (func_ptr*)&my_index,
    (func_ptr*)&my_rindex,
    (func_ptr*)&my_ffs,
    NULL
};
func_tester testers[] = {
    (func_tester)test_strlen,
    (func_tester)test_strchr,
    (func_tester)test_memset,
    (func_tester)test_memcpy,
    (func_tester)test_memmove,
    (func_tester)test_strcmp,
    (func_tester)test_strncmp,
    (func_tester)test_strcasecmp,
    (func_tester)test_strrchr,
    (func_tester)test_strstr,
    (func_tester)test_strpbrk,
    (func_tester)test_strcspn,
    (func_tester)test_memfrob,
    (func_tester)test_index,
    (func_tester)test_rindex,
    (func_tester)test_ffs,
    NULL
};

void print_passed(int passed, int totalTested)
{
    if (passed == totalTested)
        printf("Passed "GREEN_ON BOLD_ON"%d/%d"COLOR_OFF BOLD_OFF" tests.\n", passed, totalTested);
    else if (passed > 0)
        printf("Passed "ORANGE_ON BOLD_ON"%d/%d"COLOR_OFF BOLD_OFF" tests.\n", passed, totalTested);
    else
        printf("Passed "RED_ON BOLD_ON"%d/%d"COLOR_OFF BOLD_OFF" tests.\n", passed, totalTested);
}

void print_final(int functions_passed, int functions_tested)
{
    if (functions_passed == functions_tested && functions_tested > 0)
        printf(GREEN_ON BOLD_ON"Passed all tests!"COLOR_OFF BOLD_OFF"\n");
    else if (functions_passed > 0)
        printf(ORANGE_ON BOLD_ON"Passed %d/%d tests."BOLD_OFF" See reports.txt for informations on non-passed tests.\n"COLOR_OFF, functions_passed, functions_tested);
    else if (functions_tested > 0)
        printf(RED_ON BOLD_ON"Passed %d/%d tests."BOLD_OFF" See reports.txt for informations on non-passed tests.\n"COLOR_OFF, functions_passed, functions_tested);
    else
        printf(RED_ON BOLD_ON"Could not test any function."COLOR_OFF BOLD_OFF"\n");
}

int main()
{
    // Open the library
    void *my_lib = dlopen("../libasm.so", RTLD_LAZY);
    if (!my_lib) {
        printf(RED_ON BOLD_ON"Could not load the library."COLOR_OFF BOLD_OFF"\n");
        return 84;
    }

    // Load the functions: strlen -> my_strlen, etc...
    for (size_t i = 0; functions_name[i] != NULL; i++) {
        *(functions[i]) = dlsym(my_lib, functions_name[i]);
    }

    // Test the functions
    int functions_tested = 0, functions_passed = 0;
    for (size_t i = 0; testers[i] != NULL; i++) {
        printf(BOLD_ON"%-11s"BOLD_OFF": ", functions_name[i]);
        if (!(*functions[i])) {// Could not be loaded
            printf(RED_ON BOLD_ON"Skipped"COLOR_OFF BOLD_OFF" (could not be loaded).\n");
            continue;
        }
        // Actual test
        int passed = 0, totalTested = 0;
        testers[i](*functions[i], &passed, &totalTested);
        print_passed(passed, totalTested);
        functions_tested++;
        if (passed == totalTested)
            functions_passed++;
    }
    print_final(functions_passed, functions_tested);
    dlclose(my_lib);
    return (functions_passed == functions_tested && functions_tested > 0 ? 0 : 84);
}
