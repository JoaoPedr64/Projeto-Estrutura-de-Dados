#include "Funcoes.h"

int main() {

    system("clear");

    FILE* A = fopen("ArquivoBin.dat", "rb");
    if (A == NULL) {
        printf("WARNING: Arquivo binario nao existe\n");
        converte_to_bin("Subnational-period-life-tables-2017-2019-CSV.csv");
    }

    int answer;

    do {
    
        printf("==============menu==============\n");
        printf("[0] Sair\n[1] Buscar por uma posicao\n[2] Alterar registro\n[3] Adicionar novo registro\n-> ");
        scanf("%d", &answer);

        switch (answer) {
        case 1:
            imprimir_registros("ArquivoBin.dat");
            break;
        case 2:
            mudar_registro("ArquivoBin.dat");
            break;
        case 3:
            add_registro("ArquivoBin.dat");
        default:
            system("clear");
            break;
        }

    } while (answer != 0);

}