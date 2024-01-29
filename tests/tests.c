/*
** EPITECH PROJECT, 2022
** ASM
** File description:
** tests.c
*/

#include "tests.h"
#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

static int nb_tested = 0;
static char *func_name = 0;
static int has_function_failed = 0;
static FILE *reports = 0;

#define START_TEST_SUITE(func) func_name = func; reports = (reports ? reports : fopen("reports.txt", "w+")); has_function_failed = 0; nb_tested = 1
#define TRY(boolean) (try_increase((boolean), passed, totalTested))

static void try_increase(bool hasPassed, int *passed, int *totalTested)
{
    if (hasPassed)
        *passed += 1;
    else {
        if (!has_function_failed) {
            fprintf(reports, "%s:\n", func_name);
            has_function_failed = 1;
        }
        fprintf(reports, "Failed test n°%d.\n", nb_tested);
    }
    *totalTested += 1;
    nb_tested++;
}

void test_strlen(func_size_t_ptr m_strlen, int *passed, int *totalTested)
{
    START_TEST_SUITE("strlen");

    TRY(m_strlen("abc") == 3);
    TRY(m_strlen("a") == 1);
    TRY(m_strlen("") == 0);
    TRY(m_strlen("\1\2\3hsvrfsdbv678") == 15);
}

void test_strchr(func_char_ptr m_strchr, int *passed, int *totalTested)
{
    START_TEST_SUITE("strchr");

    TRY(m_strchr("abc", 'a') == (char *)"abc");
    TRY(m_strchr("abc", 'b') == "abc" + 1);
    TRY(m_strchr("abc", 'c') == "abc" + 2);
    TRY(m_strchr("abc", 'd') == NULL);
    TRY(m_strchr("abc", '\0') && (*(char *)m_strchr("abc", '\0')) == 0);
    TRY(m_strchr("abc", '\1') == NULL);
    TRY(m_strchr("", 'a') == NULL);
    TRY(m_strchr("", '\0') && (*(char *)m_strchr("", '\0')) == 0);
}

void test_memset(func_ptr m_memset, int *passed, int *totalTested)
{
    START_TEST_SUITE("memset");

    char buf[] = "abc";

    m_memset(buf, 'a', 0);
    TRY(buf[0] == 'a' && buf[1] == 'b' && buf[2] == 'c');

    m_memset(buf, 'z', 1);
    TRY(buf[0] == 'z' && buf[1] == 'b' && buf[2] == 'c');

    m_memset(buf, 'z', 2);
    TRY(buf[0] == 'z' && buf[1] == 'z' && buf[2] == 'c');

    m_memset(buf, '0', 3);
    TRY(buf[0] == '0' && buf[1] == '0' && buf[2] == '0');
}

void test_memcpy(func_ptr m_memcpy, int *passed, int *totalTested)
{
    START_TEST_SUITE("memcpy");

    char buf[5] = "abc";
    m_memcpy(buf, "def", 3);
    TRY(buf[0] == 'd' && buf[1] == 'e' && buf[2] == 'f' && buf[3] == 0);

    m_memcpy(buf, "zzz", 0);
    TRY(buf[0] == 'd' && buf[1] == 'e' && buf[2] == 'f' && buf[3] == 0);

    m_memcpy(buf, "zzzzzzz", 1);
    TRY(buf[0] == 'z' && buf[1] == 'e' && buf[2] == 'f' && buf[3] == 0);

    buf[3] = 'u';
    buf[4] = 'v';
    m_memcpy(buf, "\0\0\0\0z", 4);
    TRY(buf[0] == 0 && buf[1] == 0 && buf[2] == 0 && buf[3] == 0 && buf[4] == 'v');
}

void test_memmove(func_ptr m_memmove, int *passed, int *totalTested)
{
    START_TEST_SUITE("memmove");

    // Test memcpy
    char buf[5] = "abc";
    m_memmove(buf, "def", 3);
    TRY(buf[0] == 'd' && buf[1] == 'e' && buf[2] == 'f' && buf[3] == 0);

    m_memmove(buf, "zzz", 0);
    TRY(buf[0] == 'd' && buf[1] == 'e' && buf[2] == 'f' && buf[3] == 0);

    m_memmove(buf, "zzzzzzz", 1);
    TRY(buf[0] == 'z' && buf[1] == 'e' && buf[2] == 'f' && buf[3] == 0);

    buf[3] = 'u';
    buf[4] = 'v';
    m_memmove(buf, "\0\0\0\0z", 4);
    TRY(buf[0] == 0 && buf[1] == 0 && buf[2] == 0 && buf[3] == 0 && buf[4] == 'v');

    // Test overlap 1
    int *arr_src = malloc(sizeof(int) * 14);
    int *arr_dest = arr_src + 5;

    for (int i = 0; i < 9; i++)
        arr_src[i] = i;
    m_memmove(arr_dest, arr_src, sizeof(int) * 9);
    TRY(arr_dest[0] == 0 && arr_dest[1] == 1 && arr_dest[2] == 2 && arr_dest[3] == 3 && arr_dest[4] == 4 && arr_dest[5] == 5 && arr_dest[6] == 6 && arr_dest[7] == 7 && arr_dest[8] == 8);
    free(arr_src);

    // Test overlap, in the other way
    arr_dest = malloc(sizeof(int) * 14);
    arr_src = arr_dest + 5;
    for (int i = 0; i < 9; i++)
        arr_src[i] = i;
    m_memmove(arr_dest, arr_src, sizeof(int) * 9);
    TRY(arr_dest[0] == 0 && arr_dest[1] == 1 && arr_dest[2] == 2 && arr_dest[3] == 3 && arr_dest[4] == 4 && arr_dest[5] == 5 && arr_dest[6] == 6 && arr_dest[7] == 7 && arr_dest[8] == 8);
    free(arr_dest);
}

void test_strcmp(func_int_ptr m_strcmp, int *passed, int *totalTested)
{
    START_TEST_SUITE("strchr");

    TRY(m_strcmp("abc", "abc") == 0);
    TRY(m_strcmp("abc", "abd") < 0);
    TRY(m_strcmp("abc", "abb") > 0);
    TRY(m_strcmp("abc", "abcd") < 0);
    TRY(m_strcmp("abcd", "abc") > 0);
    TRY(m_strcmp("abc", "ab") > 0);
    TRY(m_strcmp("ab", "abc") < 0);
    TRY(m_strcmp("abc", "a") > 0);
    TRY(m_strcmp("a", "abc") < 0);
    TRY(m_strcmp("abc", "") > 0);
    TRY(m_strcmp("", "abc") < 0);
    TRY(m_strcmp("", "") == 0);
}

void test_strncmp(func_int_ptr m_strncmp, int *passed, int *totalTested)
{
    START_TEST_SUITE("strncmp");

    // Same as strcmp
    TRY(m_strncmp("abc", "abc", 4) == 0);
    TRY(m_strncmp("abc", "abd", 4) < 0);
    TRY(m_strncmp("abc", "abb", 4) > 0);
    TRY(m_strncmp("abc", "abcd", 4) < 0);
    TRY(m_strncmp("abcd", "abc", 4) > 0);
    TRY(m_strncmp("abc", "ab", 4) > 0);
    TRY(m_strncmp("ab", "abc", 4) < 0);
    TRY(m_strncmp("abc", "a", 4) > 0);
    TRY(m_strncmp("a", "abc", 4) < 0);
    TRY(m_strncmp("abc", "", 4) > 0);
    TRY(m_strncmp("", "abc", 4) < 0);
    TRY(m_strncmp("", "", 4) == 0);

    // Strncmp
    TRY(m_strncmp("abc", "abz", 2) == 0);
    TRY(m_strncmp("Hello world", "Hello world", 0) == 0);
    TRY(m_strncmp("Hello world", "Hello world", 1) == 0);
    TRY(m_strncmp("Hello world", "Hello world", 11) == 0);
    TRY(m_strncmp("Hello world", "Hello world", 12) == 0);
    TRY(m_strncmp("Hello world", "Hello world", 13) == 0);
    TRY(m_strncmp("Hello world", "abcd", 0) == 0);
    TRY(m_strncmp("Hello world", "Hello world", 32456) == 0);
}

void test_strcasecmp(func_int_ptr m_strcasecmp, int *passed, int *totalTested)
{
    START_TEST_SUITE("strcasecmp");

    // Same as strcmp
    TRY(m_strcasecmp("abc", "abc") == 0);
    TRY(m_strcasecmp("abc", "abd") < 0);
    TRY(m_strcasecmp("abc", "abb") > 0);
    TRY(m_strcasecmp("abc", "abcd") < 0);
    TRY(m_strcasecmp("abcd", "abc") > 0);
    TRY(m_strcasecmp("abc", "ab") > 0);
    TRY(m_strcasecmp("ab", "abc") < 0);
    TRY(m_strcasecmp("abc", "a") > 0);
    TRY(m_strcasecmp("a", "abc") < 0);
    TRY(m_strcasecmp("abc", "") > 0);
    TRY(m_strcasecmp("", "abc") < 0);
    TRY(m_strcasecmp("", "") == 0);

    // Strcasecmp: same tests, with random upper/lower case
    TRY(m_strcasecmp("abc", "abc") == 0);
    TRY(m_strcasecmp("Abc", "aBC") == 0);
    TRY(m_strcasecmp("aBC", "Abc") == 0);
    TRY(m_strcasecmp("AbC", "ABc") == 0);

    TRY(m_strcasecmp("A", "A") == 0);
    TRY(m_strcasecmp("abC", "abc") == 0);
    TRY(m_strcasecmp("ZeLlO, wOrLd %d%d ! ;)AAA", "zello, world %d%d ! ;)aaa") == 0);
    TRY(m_strcasecmp("zello, world %d%d ! ;)", "ZeLlO, wOrLd %d%d") > 0);
}

void test_strrchr(func_char_ptr m_rindex, int *passed, int *totalTested)
{
    START_TEST_SUITE("rindex");

    // Classic
    TRY(m_rindex("abc", 'a') == (char *)"abc");
    TRY(m_rindex("abca", 'b') == "abca" + 1);
    TRY(m_rindex("abca", 'c') == "abca" + 2);
    TRY(m_rindex("abca", 'd') == NULL);

    TRY(m_rindex("abaca", 'a') == "abaca" + 4);
    TRY(m_rindex("abbca", 'b') == "abbca" + 2);
    TRY(m_rindex("abcca", 'c') == "abcca" + 3);
    TRY(m_rindex("", 'd') == NULL);
    TRY(m_rindex("", 0) == (char *)"");
    TRY(m_rindex("aaaa", 0) == "aaaa" + 4);
    TRY(m_rindex("\0aaaa", 0) == (char *)"\0aaaa");
}

void test_strstr(func_char_ptr m_strstr, int *passed, int *totalTested)
{
    START_TEST_SUITE("strstr");

    TRY(m_strstr("abc", "a") == (char *)"abc");
    TRY(m_strstr("abca", "b") == "abca" + 1);
    TRY(m_strstr("abca", "c") == "abca" + 2);
    TRY(m_strstr("abca", "d") == NULL);
    TRY(m_strstr("Hello world", "lo wo") == (char *)"Hello world" + 3);
    TRY(m_strstr("Hello world", "Hello world") == (char *)"Hello world");
    TRY(m_strstr("Hello world", "Hello worlddd") == NULL);
    TRY(m_strstr("Hello hello world", "lo w") == "Hello hello world" + 9);
    TRY(m_strstr("abcd", "") == (char *)"abcd");
    TRY(m_strstr("", "abcd") == NULL);

}

void test_strpbrk(func_char_ptr m_strpbrk, int *passed, int *totalTested)
{
    START_TEST_SUITE("strpbrk");

    // Same as strchr
    TRY(m_strpbrk("abc", "a") == (char *)"abc");
    TRY(m_strpbrk("abc", "b") == "abc" + 1);
    TRY(m_strpbrk("abc", "c") == "abc" + 2);
    TRY(m_strpbrk("abc", "d") == NULL);
    TRY(m_strpbrk("abc", "") == 0);
    TRY(m_strpbrk("abc", "\1") == NULL);
    TRY(m_strpbrk("", "a") == NULL);
    TRY(m_strpbrk("", "") == 0);

    // Trickier
    TRY(m_strpbrk("Hello world", "zzzzzzzzzzzzzzzzzzzH") == (char *)"Hello world");
    TRY(m_strpbrk("Hello world", "zzzzzzzzzzzzzzzdzzzz") == (char *)"Hello world" + 10);
    TRY(m_strpbrk("Hello world", "zzzzzzzzzzzzzzzzzzz") == NULL);
    TRY(m_strpbrk("Hello world", "zzzzzzzzzz zzzzzzzzz") == (char *)"Hello world" + 5);
    TRY(m_strpbrk("Hello world", "zzzzzzzzzzzzzzzdezzzz") == (char *)"Hello world" + 1);
}

void test_strcspn(func_size_t_ptr m_strcspn, int *passed, int *totalTested)
{
    START_TEST_SUITE("strcspn");

    TRY(m_strcspn("abc", "a") == 0);
    TRY(m_strcspn("abc", "b") == 1);
    TRY(m_strcspn("abc", "c") == 2);
    TRY(m_strcspn("abc", "d") == 3);
    TRY(m_strcspn("abc", "") == 3);

    TRY(m_strcspn("Hello world", "zzzzzzzzzzzzzzzzzzzH") == 0);
    TRY(m_strcspn("Hello world", "zzzzzzzzzzzzzzzdzzzz") == 10);
    TRY(m_strcspn("Hello world", "zzzzzzzzzzzzzzzdzezz") == 1);
    TRY(m_strcspn("Hello world", "zzzzzzzzzzzzzzzzzzz") == 11);
}

void test_memfrob(func_ptr m_memfrob, int *passed, int *totalTested)
{
    START_TEST_SUITE("memfrob");

    {
    char str[] = "Hello world";
    char str2[] = "Hello world";
    memfrob(str2, 11);
    TRY(m_memfrob(str, 11) == str);
    TRY(memcmp(str, str2, 11) == 0);
    TRY(m_memfrob(str, 11) == str);
    TRY(memcmp(str, "Hello world", 11) == 0);
    }
    {
    char str[] = "";
    char str2[] = "";
    memfrob(str2, 1);
    TRY(m_memfrob(str, 1) == str);
    TRY(memcmp(str, str2, 1) == 0);
    TRY(m_memfrob(str, 1) == str);
    TRY(memcmp(str, "", 1) == 0);
    }
    {
    char str[] = "\42";
    char str2[] = "\42";
    memfrob(str2, 2);
    TRY(m_memfrob(str, 2) == str);
    TRY(memcmp(str, str2, 2) == 0);
    TRY(m_memfrob(str, 2) == str);
    TRY(memcmp(str, "\42", 2) == 0);
    }
    {
    char str[] = "";
    char str2[] = "";
    memfrob(str2, 0);
    TRY(m_memfrob(str, 0) == str);
    TRY(memcmp(str, str2, 1) == 0);
    TRY(m_memfrob(str, 0) == str);
    TRY(memcmp(str, "", 1) == 0);
    }
}

void test_index(func_char_ptr m_index, int *passed, int *totalTested)
{
    START_TEST_SUITE("index");

    test_strchr(m_index, passed, totalTested);
}

void test_rindex(func_char_ptr m_rindex, int *passed, int *totalTested)
{
    START_TEST_SUITE("rindex");

    test_strrchr(m_rindex, passed, totalTested);
}

void test_ffs(func_int_ptr m_ffs, int *passed, int *totalTested)
{
    START_TEST_SUITE("ffs");
    for (int i = 0; i < 10000000; i++) {
        TRY(m_ffs(i) == ffs(i));
    }
    for (int i = -10000000; i < 0; i++) {
        TRY(m_ffs(i) == ffs(i));
    }
    TRY(m_ffs(-1) == ffs(-1));
}
