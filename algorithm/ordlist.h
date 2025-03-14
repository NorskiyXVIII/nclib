#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef NCLIB__ORDLIST__H__
#define NCLIB__ORDLIST__H__
typedef enum {
    _INIT_ELEM, // LIST CREATED
    _DECIMAL_ELEM,
    _REAL_ELEM,
    _STRING_ELEM,
} vtype_list_t;

typedef union {
    int64_t decimal;
    double  real;
    uint8_t* str;
} value_list_t;

typedef struct List {
    vtype_list_t type;
    value_list_t value;
    struct List* next;  
} List;

// List* list = new_list("drs", 555, 1.23, "hello, world!");
extern List* new_list(uint8_t* format, ...);
extern void free_list(List* list);

extern List* push_list(List* list, uint8_t* format, ...);
extern List* pop_list(List* list);

extern void print_list(List* list);

extern List* new_list(uint8_t* format, ...) {
    List* list = (List*)malloc(sizeof(List)); // first elem address
    List* list_ptr = list; // end elem
    list->type = _INIT_ELEM;
    list->next = NULL;
    
    value_list_t value;
    va_list factor;
    va_start(factor, format);
    while(*format) {
        switch(*format) {
            case 'd': // decimal
            case 'i':
                value.decimal = va_arg(factor, int64_t);
                list_ptr = push_list(list_ptr, "d", value.decimal);
                break;
            case 'r': // real
            case 'f':
                value.real = va_arg(factor, double);
                list_ptr = push_list(list_ptr, "r", value.real);
                break;
            case 's': // string
                value.str = va_arg(factor, uint8_t*);
                list_ptr = push_list(list_ptr, "s", value.str);
                break;
        };
        ++format;
    }
    va_end(factor);
    return list;
}

extern List* push_list(List* list, uint8_t* format, ...) {
    if (list == NULL) {
        fprintf(stderr, "%s\n", "list is null");
        return NULL;
    }
    while(list->next != NULL) {
        list = list->next;
    }
    value_list_t value;
    va_list factor;
    va_start(factor, format);
    while(*format) {
        switch(*format) {
            case 'd': // decimal
            case 'i':
                    value.decimal = va_arg(factor, int64_t);
                    list->next = (List*)malloc(sizeof(List));
                    list = list->next;
                    list->type = _DECIMAL_ELEM;
                    list->value.decimal = value.decimal;
                    list->next = NULL;
                break;
            case 'r': // real
            case 'f':
                    value.real = va_arg(factor, double);
                    list->next = (List*)malloc(sizeof(List));
                    list = list->next;
                    list->type = _REAL_ELEM;
                    list->value.real = value.real;
                    list->next = NULL;
                break;
            case 's': // string
                    value.str = va_arg(factor, uint8_t*);
                    list->next = (List*)malloc(sizeof(List));
                    list = list->next;
                    list->type = _STRING_ELEM;
                    list->value.str = value.str;
                    list->next = NULL;
                break;
        };
        ++format;
    }
    va_end(factor);
    return list;
}

extern List* pop_list(List* list) {
    if (list == NULL) {
        fprintf(stderr, "%s\n", "list is null");
        return NULL;
    }
    if (list->next == NULL) {
        return list;
    }
    
    List* prev_list = list;
    List* past_list = list->next;
    while(past_list->next != NULL) {
        prev_list = past_list;
        past_list = past_list->next;
    }
    
    prev_list->next = NULL;
    return past_list;
}

extern void print_list(List* list) {
    printf("[ ");
    while(list != NULL) {
        switch (list->type) {
            case _DECIMAL_ELEM:
                printf("%ld ", list->value.decimal);
                break;
            case _REAL_ELEM:
                printf("%g ", list->value.real);
                break;
            case _STRING_ELEM:
                printf("'%s' ", list->value.str);
                break;
        }
        list = list->next;
    }
    printf("]\n");
}

extern void free_list(List* list) {
    List* list_ptr;
    while(list != NULL) {
        list_ptr = list->next; // next elem
        free(list);
        list = list_ptr;
    }
}
#endif