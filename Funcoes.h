#ifndef declaracoes
#define declaracoes
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ARQUIVO {
    FILE* arq;
    int pos, MAXIMO, *buffer;
} ARQUIVO;


typedef struct DADOS {
    char measure[256];
    char quantile[256];
    char area[256];
    char sex[256];
    char age[256];
    char geography[256];
    char ethnic[256];
    char value[256];
} DADOS;

void converte_to_bin(char* arquivo);
void imprimir_registros(char* arquivo);
void mudar_registro(char* arquivo);
void add_registro(char* arquivo);
int contline(char* arquivo);
void menu_registro(DADOS leitura);
DADOS ler_registro(DADOS r);
void voltar();


#endif