#include "Funcoes.h"

// Funcao que converte o arquivo para binario
void converte_to_bin(char* arquivo) {

    printf("\nWARNING: Convertendo para arquivo binario...\n");

    DADOS *d = NULL;

    FILE* arq = fopen(arquivo, "r");
    if (arq == NULL) {
        printf("ERRO: falha ao abrir arquivo %s\n", arquivo);
        fclose(arq);
        return;
    }

    char *arquivo_dat = "ArquivoBin.dat";

    FILE* arqdat = fopen(arquivo_dat, "wb");
    if (arqdat == NULL) {
        printf("ERRO: Falha ao criar arquivo binario\n");
        fclose(arq);
        return;
    }

    DADOS temp;

    do {
        fscanf(arq, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]%*c", temp.measure, temp.quantile, temp.area, temp.sex, temp.age, temp.geography, temp.ethnic, temp.value);
        fwrite(&temp, sizeof(DADOS), 1, arqdat);
    } while(!feof(arq));

    fclose(arq);
    fclose(arqdat);

    system("clear");

}

// funcao que imprimi os registros
void imprimir_registros(char* arquivo) {

    system("clear");

    int escolha, tamanho = contline(arquivo);
    
    do {
        printf("Tamanho: %d...\n", tamanho);
        printf("Imprimir:\n[1] Tudo\n[2] De uma posicao a outra\n\n-> ");
        scanf(" %d", &escolha);
    } while(escolha != 1 && escolha != 2);

    if (escolha == 1) {
        FILE* arq = fopen(arquivo, "rb");
        DADOS leitura;

        do {
            fread(&leitura, sizeof(DADOS), 1, arq);
            menu_registro(leitura);
        } while(!feof(arq));

        int a;

        printf("\nPrecione enter para voltar...");
        while((a = getchar()) != '\n' && a != EOF);
        getchar();

        return;
    }

    system("clear");
    printf("Tamanho: %d...\n", tamanho);
    int inicio, fim;
    printf("\nImprimir de: ");
    scanf("%d", &inicio);
    printf("Imprimir de %d ate: ", inicio);
    scanf("%d", &fim);

    if (inicio > fim) {
        system("clear");
        printf("ERRO: Inicio nao pode ser maior que o fim");
        return;
    }
    if (inicio > tamanho || fim > tamanho) {
        printf("ERRO: Posicao invalida\n");
        return;
    }

    FILE* arq = fopen(arquivo, "rb");

    DADOS leitura;

    fseek(arq, inicio * sizeof(DADOS), SEEK_SET);

    for (int i = inicio; i < fim; i++) {
        fread(&leitura, sizeof(DADOS), 1, arq);
        menu_registro(leitura);
    }

    int a;
    printf("\nPrecione enter para voltar...");

    while((a = getchar()) != '\n' && a != EOF);
    getchar();
    
    fclose(arq);
    system("clear"); 

}

// Funcao que edita um registro de posiçao x
void mudar_registro(char* arquivo) {

    int posicao, tamanho = contline(arquivo);
    printf("\nMudar registro da posicao: ");
    scanf("%d", &posicao);

    if (posicao == 0 || posicao == 1)
        posicao = 2;
    if (posicao < 0 || posicao > tamanho) {
        printf("\nERRO: Possicao invalida\n");
        return;
    }

    FILE* arq = fopen(arquivo, "rb+");
    DADOS novalinha = ler_registro(novalinha);

    fseek(arq, posicao * sizeof(DADOS), SEEK_SET);
    fwrite(&novalinha, sizeof(DADOS), 1, arq);

    fclose(arq);
    system("clear");

}

// Funcao que adiciona registros
void add_registro(char* arquivo) {

    FILE* arq = fopen(arquivo, "ab");

    DADOS novalinha = ler_registro(novalinha);

    fwrite(&novalinha, sizeof(DADOS), 1, arq);
    fclose(arq);

    int totl = contline(arquivo);

    printf("Nova linha adicionada na posicao %d...\n", totl);

    voltar();
    system("clear");

}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

int contline(char* arquivo) {

    int linhas = 0;

    FILE* arq = fopen(arquivo, "rb");

    fseek(arq, 0, SEEK_END);
    long tamanho = ftell(arq);

    if (linhas > 0)
        linhas = tamanho / sizeof(DADOS);

    fclose(arq);
    return linhas;

}

DADOS ler_registro(DADOS r) {

    printf("\n========================================\n");
    printf("measure  : ");
    scanf("%s", r.measure);
    getchar();
    printf("quantile : ");
    scanf("%s", r.quantile);
    getchar();
    printf("area     : ");
    fgets(r.area, sizeof(r.area), stdin);
    printf("sex      : ");
    fgets(r.sex, sizeof(r.sex), stdin);
    printf("age      : ");
    fgets(r.age, sizeof(r.age), stdin);
    printf("geography: ");
    fgets(r.geography, sizeof(r.geography), stdin);
    printf("ethnic   : ");
    fgets(r.ethnic, sizeof(r.ethnic), stdin);
    printf("value    : ");
    fgets(r.value, sizeof(r.value), stdin);
    printf("========================================\n");

    r.area[strlen(r.area) - 1] = '\0';
    r.sex[strlen(r.sex) - 1] = '\0';
    r.age[strlen(r.age) - 1] = '\0';
    r.geography[strlen(r.geography) - 1] = '\0';
    r.ethnic[strlen(r.ethnic) - 1] = '\0';
    r.value[strlen(r.value) - 1] = '\0';

    return r;

}

void menu_registro(DADOS leitura) {

    printf("========================================\n");
    printf("measure  : %s\n", leitura.measure);
    printf("quantile : %s\n", leitura.quantile);
    printf("area     : %s\n", leitura.area);
    printf("sex      : %s\n", leitura.sex);
    printf("age      : %s\n", leitura.age);
    printf("geography: %s\n", leitura.geography);
    printf("ethnic   : %s\n", leitura.ethnic);
    printf("value    : %s\n", leitura.value);
    printf("========================================\n\n");

}

void voltar() {

    int a;
    printf("Precione enter para voltar...");
    while((a = getchar()) != '\n' && a != EOF);

    return;

}
