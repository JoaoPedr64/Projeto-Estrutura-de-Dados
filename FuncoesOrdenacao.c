#include "Funcoes.h"
#define MAX 50000

void MergeSortExterno(char* arquivo) {

    char novo[20];


}

int CriarArquivoOrdenado(char* arquivo) {

    DADOS v[MAX];
    int cont = 0, total = 0;
    char novo[20];

    FILE* arq = fopen(arquivo, "rb");

    while(!feof(arq)) {
        fread(v, sizeof(DADOS), MAX, arq);
        total += MAX;
        
        if (total >= MAX) {
            cont++;
            sprintf(novo, "temp%d.dat", cont);
            sort(v, total, sizeof(DADOS));
            salvarArquivo(novo, v, total);
            total = 0;
        }
    }

    if (total > 0) {
        cont++;
        sprintf(novo, "temp%d.dat", cont);
        sort(v, total, sizeof(DADOS));
        salvarArquivo(novo, v, total);
    }

    fclose(arq);
    return cont;

}

void salvarArquivo(char* arquivo, DADOS* v, int tot) {

    FILE* arq = fopen(arquivo, "ab");

    for (int i = 0; i < tot - 1; i++)
        fwrite(v, sizeof(DADOS), 1, arq);

}

void merge(char* arquivo, int Narq, int k) {

    char nome[20];
    int *buffer = malloc(k * sizeof(int));

    ARQUIVO* f = malloc(Narq * sizeof(ARQUIVO));

    for (int i = 0; i < Narq; i++) {
        sprintf(nome, "Temp%d.dat", i + 1);
        f[i].arq = fopen(nome, "rb");
        f[i].MAXIMO = 0;
        f[i].pos = 0;
        f[i].buffer = malloc(k * sizeof(int));
        PreenchearBuffer(&f[i], k);
    }

    int menor, qBuffer = 0;

    while (ProcurandoMenor(f, Narq, k, &menor) == 1) {
        buffer[qBuffer] = menor;
        qBuffer++;
        if (qBuffer == k) {
            salvarArquivo(nome, buffer, k);
            qBuffer = 0;
        }
    }

    if (qBuffer != 0) 
        salvarArquivo(nome, buffer, k);
    
    for (int i = 0; i < Narq; i++) 
        free(f[i].buffer);

    free(f);
    free(buffer);

}

int ProcurandoMenor(ARQUIVO* f, int Narq, int k, int* menor) {

    int index = -1;
    for (int i = 0; i < Narq; i++) {
        if (f[i].pos < f[i].MAXIMO) {
            if (index == -1)
                index = i;
            else {
                if (f[i].buffer[f[i].pos] < f[index].buffer[f[index].pos]) {
                    index = i;
                }
            }
        }
    }

    if (index != -1) {
        *menor = f[index].buffer[f[index]. pos];
        f[index].pos++;
        if (f[index].pos == f[index].MAXIMO)
            PreenchearBuffer(&f, k);
        return 1;
    }

    return 0;

}
