#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculaGrauVertice(char *linha) {
    int grau = 0;
    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == '1') {
            grau++;
        }
    }
    return grau;
}

int verticeIsolado(char *linha) {
    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == '1') {
            return 0;
        }
    }
    return 1;
}

void primeiroUltimoConectados(char *primeiraLinha) 
{
    if (primeiraLinha[4225] == "1"){
        printf(O primeir e u)
    }
}



int main(void) 
{
    FILE *fp;
    char str[4230];
    char primeiraLinha[4230];
    int maiorGrau = 0;
    int numeroVerticeMaiorGrau = 0;
    int contadorLinha = 0;
    int quantidadeVerticesIsolados = 0;

    fp = fopen("dados_matriz.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(str, sizeof(str), fp) != NULL) {
        if (contadorLinha == 0) {
            contadorLinha++;
            continue;
        }

        if (contadorLinha == 1) {
            strcpy(primeiraLinha, str);
        }
        if (contadorLinha == 2114) {
            strcpy(ultimaLinha, str);
        }

        if (verticeIsolado(str) == 1) {
            quantidadeVerticesIsolados++;
        }
        int grau = calculaGrauVertice(str);
        if (grau > maiorGrau) {
            maiorGrau = grau;
            numeroVerticeMaiorGrau = contadorLinha;
        }
        contadorLinha++;
    }
    printf("Primeira linha: %s", primeiraLinha);
    printf("Última linha: %s", ultimaLinha);
    //primeiroUltimoConectados(primeiraLinha, ultimaLinha);

    fclose(fp);

    //printf("Vértice de Maior Grau: d(V%d) = %d.\n", numeroVerticeMaiorGrau, maiorGrau);
    //printf("Total de vértices isolados: %d.\n", quantidadeVerticesIsolados);

    return 0;
}


