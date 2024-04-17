#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <libprg/libprg.h>

typedef struct no{
    int dado;
    struct no * proximo_t;
} no_t;

typedef struct lista_ordenada {
    bool ordenada;
    struct no no_t;
}lista_ord;


