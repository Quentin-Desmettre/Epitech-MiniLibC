/*
** EPITECH PROJECT, 2022
** ASM
** File description:
** tests.h
*/

#pragma once

#include <stddef.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>

#define BOLD_ON "\033[1m"
#define BOLD_OFF "\033[22m"
#define RED_ON "\033[31m"
#define GREEN_ON "\033[32m"
#define ORANGE_ON "\033[38;5;208m"
#define COLOR_OFF "\033[0m"

typedef void *(*func_ptr)();
typedef void (*func_tester)(func_ptr, int *, int *);
typedef int (*func_int_ptr)();
typedef size_t (*func_size_t_ptr)();
typedef char *(*func_char_ptr)();

void test_strlen(func_size_t_ptr func, int *passed, int *totalTested);
void test_strchr(func_char_ptr func, int *passed, int *totalTested);
void test_memset(func_ptr func, int *passed, int *totalTested);
void test_memcpy(func_ptr func, int *passed, int *totalTested);
void test_memmove(func_ptr func, int *passed, int *totalTested);
void test_strcmp(func_int_ptr func, int *passed, int *totalTested);
void test_strncmp(func_int_ptr func, int *passed, int *totalTested);
void test_strcasecmp(func_int_ptr func, int *passed, int *totalTested);
void test_strrchr(func_char_ptr func, int *passed, int *totalTested);
void test_strstr(func_char_ptr func, int *passed, int *totalTested);
void test_strpbrk(func_char_ptr func, int *passed, int *totalTested);
void test_strcspn(func_size_t_ptr func, int *passed, int *totalTested);
void test_memfrob(func_ptr m_memfrob, int *passed, int *totalTested);
void test_index(func_char_ptr m_index, int *passed, int *totalTested);
void test_rindex(func_char_ptr m_rindex, int *passed, int *totalTested);
void test_ffs(func_int_ptr m_ffs, int *passed, int *totalTested);
